#include <Geode/Geode.hpp>
#include <Geode/utils/general.hpp>


#include "SplineManager.hpp"
#include "interpolation-menu.hpp"

using namespace geode::prelude;

constexpr ccColor3B clrs[]{
    {116, 52, 235},
    {56, 163, 235},
    {235, 143, 56},
    {235, 56, 56},
    {74, 235, 56},
    {235, 56, 202}
};

bool InterpolationMenu::setup(Spline* s, GameObject* left, GameObject* right) {
    
    auto& mgr = SplineManager::get();
    m_noElasticity = false;
    
    float diff = right->getPositionX() - left->getPositionX();
    mgr.addPointToSpline(s->getId(), Point(0, .5));
    mgr.addPointToSpline(s->getId(), Point(1, .5));

    /* todo:
        -   design the system in such a way multiple splines can be shown ontop of eachother
        -   read the object id, and for every parameter entry in the json create a new spline
        -   set up each spline with its default settings (do this in the constructor)
        -   Create a button for every editable parameter, these can either be selected or deselected
        -   If button for parameter is selected, user can edit selected parameters
        -   die or something i dont know
    */
    
    log::debug("{}", diff);


    this->setTitle("INTERPOLATIOOOONN!!!");
    this->setID("interpolation-menu"_spr);

    auto label = CCLabelBMFont::create(s->getId().c_str(), "bigFont.fnt");
    label->setSkewY(7.f);
    m_mainLayer->addChildAtPosition(label, Anchor::Center);

    
    cocos2d::ccColor4F pointColor(0.f, 1.f, 1.f, 1.f);
    cocos2d::ccColor3B drawColor(0, 0, 0);
    cocos2d::CCSize st(15.f, 15.f);

    auto* draw = CCDrawNode::create();
    draw->setZOrder(-1);
    m_mainLayer->addChild(draw);
    draw->setAnchorPoint(ccp(.5f, .5f));
    draw->setContentSize(ccp(50.f, 50.f));

    draw->drawDot(ccp(2.f, 2.f), 1, ccc4f(0.f, 1.f, 1.f, .5f));


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



    

    // auto nvmSprite = ButtonSprite::create("nvm..", "bigFont.fnt", "GJ_Button_06.png");
    
    
    auto okBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("go!", "bigFont.fnt", "GJ_Button_01.png"),
        this,
        menu_selector(InterpolationMenu::on_button)
    );
    m_btnMenu->addChildAtPosition(okBtn, Anchor::BottomRight);

    

    m_mainLayer->addChildAtPosition(m_btnMenu, Anchor::BottomRight, ccp(-10, 10));
    m_btnMenu->updateLayout();
    return true;
};

InterpolationMenu* InterpolationMenu::create(Spline* s, GameObject* left, GameObject* right) {
    auto ret = new InterpolationMenu();
    if (ret->initAnchored(400.f, 270.f, s, left, right)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};

void InterpolationMenu::on_button(CCObject* sender) {
    log::debug("hi from this button");
     log::debug("hi: {}", m_fields->parameters[std::to_string(obj01->m_objectID)]["name"].asString().unwrap());
    m_fields->objDesc << "1," << obj01->m_objectID << ",2," << obj01->m_positionX << ",3," << obj01->m_positionY << ";";

    m_fields->objString = m_fields->objDesc.str();
    m_fields->objString.pop_back(); //pop back

    editorLayer->createObjectsFromString(m_fields->objString.c_str(), true, true);
    FLAlertLayer::create("Success", "successfully interpolated" , "OK")->show();

}

// class interpolationMenu

