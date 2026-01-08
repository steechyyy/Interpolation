#include <common.hpp>
#include <Geode/utils/general.hpp>

using namespace geode::prelude;

// specify parameters for the setup function in the Popup<...> template

bool InterpolationMenu::setup(Spline* s) {
    log::debug("hii");
    m_noElasticity = false;
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
    

    return true;
};

InterpolationMenu* InterpolationMenu::create(Spline* s) {
    auto ret = new InterpolationMenu();
    if (ret->initAnchored(400.f, 270.f, s)) {
        ret->autorelease();
        return ret;
    }   

    delete ret;
    return nullptr;
}


// class interpolationMenu

