#include <Geode/Geode.hpp>
#include <Geode/utils/general.hpp>


#include "SplineManager.hpp"
#include "interpolation-menu.hpp"
#include "editorstate.hpp"


using namespace geode::prelude;

constexpr ccColor3B clrs[]{
    {116, 52, 235},
    {56, 163, 235},
    {235, 143, 56},
    {235, 56, 56},
    {74, 235, 56},
    {235, 56, 202}
};

const float ratio = 21 / 5;

template<typename T>
void applyValue(const std::string_view value, std::unique_ptr<Point>& newPoint) {
    Result<T> pointVal = numFromString<T>(value);
    if (pointVal) {
        newPoint->setValue(pointVal.unwrap());
    } else {
        log::warn("{}", pointVal.unwrapErr());
    }
}

static std::string getPropertyValue(const std::string& objectString, const std::string& targetProperty) {
    std::string clean = objectString;

    if (!clean.empty() && clean.back() == ';') {
        clean.pop_back();
    }

    std::vector<std::string> parts;
    std::stringstream ss(clean);
    std::string item;

    while (std::getline(ss, item, ',')) {
        parts.push_back(item);
    }
    
    for (size_t i = 0; i + 1 < parts.size(); i += 2) {
        if (parts[i] == targetProperty) {
            return parts[i + 1];
        }
    }

    return "";
}

static std::string replaceProperty(
    const std::string& objectString,
    const std::string& targetProperty,
    const std::string& newValue
) {
    std::string clean = objectString;
    bool hadSemicolon = false;

    if (!clean.empty() && clean.back() == ';') {
        clean.pop_back();
        hadSemicolon = true;
    }


    std::vector<std::string> parts;
    std::stringstream ss(clean);
    std::string item;

    while (std::getline(ss, item, ',')) {
        parts.push_back(item);
    }

    bool found = false;
    for (size_t i = 0; i + 1 < parts.size(); i += 2) {
        if (parts[i] == targetProperty) {
            parts[i + 1] = newValue;
            found = true;
            break;
        }
    }

    if (!found) {
        parts.push_back(targetProperty);
        parts.push_back(newValue);
    }

    std::string res;
    for (size_t i = 0; i < parts.size(); ++i) {
        res += parts[i];
        if (i != parts.size() - 1) {
            res += ",";
        }
    }

    if (hadSemicolon) {
        res += ";";
    }

    return res;
}

// return the 1. leftmost and 2. rightmost object
static std::pair<GameObject*, GameObject*> getObjBounds(CCArray* objects) {
    GameObject* leftmost = nullptr;
    GameObject* rightmost = nullptr;

    CCObject* v;
    CCARRAY_FOREACH(objects, v) {
        auto obj = static_cast<GameObject*>(v);
        if (!obj) continue;

        double x = obj->m_positionX;

        if (!leftmost || x < leftmost->m_positionX)
            leftmost = obj;

        if (!rightmost || x > rightmost->m_positionX)
            rightmost = obj;
    }

    return std::make_pair(leftmost, rightmost);
}

// return the difference of xPositions of all obecjts inside a CCArray
static double getDiff(CCArray* objects) {
    std::pair<GameObject*, GameObject*> lr = getObjBounds(objects);

    return lr.second->m_positionX - lr.first->m_positionX;
}


bool InterpolationMenu::setup(CCArray* objects) {
    auto& mgr = SplineManager::get();
    auto& editorState = getEditorState();

    m_noElasticity = false;

    //
    // 1, create a new spline for every parameter our trigger has
    //

    GameObject* firstObject = static_cast<GameObject*>(objects->firstObject());
    std::string objectId = std::to_string(firstObject->m_objectID);

    if (!editorState.parameters.contains(objectId)) {
        log::error("could not find objectID {} in json!", objectId);
        return false;
    }
    auto& trig = editorState.parameters[objectId];
    
    if (!trig.contains("parameters")) {
        log::error("json does not include parameters for objectId {}", objectId);
        return false; 
    }
    auto& params = trig["parameters"];

    for (auto const& [k, val] : params) { // For every parameter:
        std::string paramId = k;
        std::string name = val["name"].asString().unwrapOr("undefined");
        std::string type = val["type"].asString().unwrapOr("undefined");

        
        auto newSpline = std::make_unique<Spline>(k);
        loadedSplines.push_back(std::move(newSpline));
        
        
        std::pair<GameObject*, GameObject*> lr = getObjBounds(objects);
        double diff = lr.second->m_positionX - lr.first->m_positionX;

        for (GameObject* thing : CCArrayExt<GameObject*>(objects)) { // For every object
            gd::string saveString = thing->getSaveString(editorState.levelEditorLayer);

            double t = 0.0;
            if (diff != 0.0) {
                t = (thing->m_positionX - lr.first->m_positionX) / diff;
            }
            else {
                log::warn("Difference between positions is zero");
            }
            log::debug("Getting property {} of {}: \"{}\"", k, objectId, getPropertyValue(saveString, k));

            auto newPoint = std::make_unique<Point>();
            newPoint->setObj(thing);
            newPoint->setTime(t);
            newPoint->setType(type);

            auto propVal = getPropertyValue(saveString, k);
            if (propVal != "") {
                if (type == "float") {
                    applyValue<float>(propVal, newPoint);
                }
                else if (type == "int") {
                    applyValue<int>(propVal, newPoint);
                }
            }
            else {
                log::info("property {} of {} is undefined!", k, objectId);
            }

            loadedSplines.back()->addPoint(std::move(newPoint));
        }
        // i learnt that ccarray_foreach is very stinky and toxic
    }





    /*
    the spline window should:
        - if multiple objects selected, automatically create points for each of them (& their values)
        - right click to create new points
        - hold left to move points (shift to move multiple?)

    requirements:
        - InterpolationMenu constructs splines from an array of GameObject*s
        - interpolationmenu should honestly own the splines why tf do i have a wrapper for splines bro
        - 

    When points have a gameobject, the associated gameobject will be modified. If not, create a
    new gameobject at the point's position!!!


    */


    /* todo:
        -   design the system in such a way multiple splines can be shown ontop of eachother
        -   read the object id, and for every parameter entry in the json create a new spline
        -   set up each spline with its default settings (do this in the constructor)
        -   Create a button for every editable parameter, these can either be selected or deselected
        -   If button for parameter is selected, user can edit selected parameters
        -   die or something i dont know
    */


    this->setTitle("INTERPOLATIOOOONN!!!");
    this->setID("interpolation-menu"_spr);

    auto label = CCLabelBMFont::create("INTERPOLATIOOOONN!!!", "bigFont.fnt");
    label->setSkewY(7.f);
    m_mainLayer->addChildAtPosition(label, Anchor::Center);


    // buton.......omgg......
    m_btnMenu = CCMenu::create();
    m_btnMenu->setContentWidth(120.f);
    m_btnMenu->setLayout(
        RowLayout::create()
        ->setAxisAlignment(AxisAlignment::End)
        ->setAxisReverse(true)
        ->setGap(15)
    );
    m_btnMenu->setAnchorPoint(ccp(1, 0));
    m_btnMenu->setID("btns_bottom"_spr);


    auto mainMenuSize = CCSize(200.f, 200.f / ratio);
    m_mainMenu = CCMenu::create();
    m_mainMenu->ignoreAnchorPointForPosition(false);
    m_mainMenu->setContentSize(mainMenuSize);
    m_mainMenu->setPosition(ccp(0, 0));
    m_mainMenu->setAnchorPoint(ccp(0, 1));
    m_mainMenu->setID("main"_spr);
    

    // auto nvmSprite = ButtonSprite::create("nvm..", "bigFont.fnt", "GJ_Button_06.png");
    
    
    auto okBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("go!", "bigFont.fnt", "GJ_Button_01.png"),
        this,
        menu_selector(InterpolationMenu::on_button)
    );
    m_btnMenu->addChildAtPosition(okBtn, Anchor::BottomRight);

    auto nvmBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("nvm..", "bigFont.fnt", "GJ_Button_06.png"),
        this,
        menu_selector(InterpolationMenu::onNvm)
    );
    m_btnMenu->addChildAtPosition(nvmBtn, Anchor::BottomRight);


    cocos2d::ccColor4F pointColor(0.f, 1.f, 1.f, 1.f);
    cocos2d::ccColor3B drawColor(0, 0, 0);
    cocos2d::CCSize st(15.f, 15.f);

    auto* draw = CCDrawNode::create();
    draw->setZOrder(-1);
    draw->setAnchorPoint(ccp(0.f, 1.f));
    draw->setContentSize(m_mainMenu->getContentSize());

    //
    // background!
    //

    draw->drawRect(
        ccp(0, 0),
        ccp(mainMenuSize.width, mainMenuSize.height),
        ccc4f(.1f, .1f, .1f, 1.f),
        0.f,
        ccc4f(0.f, 0.f, 0.f, 0.f)
    );

    draw->drawRect(
        ccp(0, 0),
        ccp(mainMenuSize.width, mainMenuSize.height / 2),
        ccc4f(.08f, .08f, .08f, 1.f),
        0.f,
        ccc4f(0.f, 0.f, 0.f, 0.f)
    );

    log::debug("{}", loadedSplines[0]->getId());
    for (const std::unique_ptr<Point>& p : loadedSplines[0]->getPoints()) {
        draw->drawDot(
            ccp(p->getTime() * mainMenuSize.width, mainMenuSize.height / 2),
            1.f,
            ccc4f(1.f, 1.f, 1.f, 1.f)
        );
    }

    m_mainMenu->addChildAtPosition(draw, Anchor::TopLeft);



    m_mainLayer->addChildAtPosition(m_btnMenu, Anchor::BottomRight, ccp(-10, 10));
    m_mainLayer->addChildAtPosition(m_mainMenu, Anchor::TopLeft, ccp(30, -45));
    m_btnMenu->updateLayout();
    return true;
};

InterpolationMenu* InterpolationMenu::create(CCArray* objects) {
    auto ret = new InterpolationMenu();
    if (ret->initAnchored(400.f, 270.f, objects)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};

void InterpolationMenu::onNvm(CCObject* sender) {
    log::debug("close");
}

void InterpolationMenu::on_button(CCObject* sender) {
    auto& ed = getEditorState();


    log::debug("hi 22");
    if (!ed.initialized) {
        FLAlertLayer::create(
            "uh oh",
            "<c>InterpolationMenu: something really bad happened. report this!</c>",
            "ok.."
        )->show();
        return;
    };
    
    std::ostringstream objDesc;
    std::string objString;

    objDesc << "1,1,2,100,3,300;";

    objString = objDesc.str();
    objString.pop_back(); //pop back

    ed.levelEditorLayer->createObjectsFromString(objString.c_str(), true, true);
    FLAlertLayer::create("Success", "successfully interpolated" , "OK")->show();

}

// class interpolationMenu

