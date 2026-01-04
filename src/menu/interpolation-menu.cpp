#include <common.hpp>
#include <Geode/utils/general.hpp>

using namespace geode::prelude;

// specify parameters for the setup function in the Popup<...> template

bool InterpolationMenu::setup(std::string const& value) {
    m_noElasticity = false;
    this->setTitle("Hi mom!");

    auto label = CCLabelBMFont::create(value.c_str(), "bigFont.fnt");
    m_mainLayer->addChildAtPosition(label, Anchor::Center);

    return true;
};

InterpolationMenu* InterpolationMenu::create(std::string const& txt) {
    auto ret = new InterpolationMenu();
    if (ret->initAnchored(300.f, 10.f, txt)) {
        ret->autorelease();
        return ret;
    }   

    delete ret;
    return nullptr;
}


// class interpolationMenu

