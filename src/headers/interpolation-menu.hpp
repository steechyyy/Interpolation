#ifndef INTERPOLATIONMENU_H
#define INTERPOLATIONMENU_H

#include <common.hpp>
using namespace geode::prelude;

class InterpolationMenu : public geode::Popup<Spline*, GameObject*, GameObject*> {
protected:
	CCMenu* m_btnMenu = nullptr;

	bool setup(Spline*, GameObject* left, GameObject* right) override;

public:

	static InterpolationMenu* create(Spline* s, GameObject* left, GameObject* right);
	void on_button(CCObject* sender);
};


#endif
