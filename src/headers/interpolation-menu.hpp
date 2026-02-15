#ifndef INTERPOLATIONMENU_H
#define INTERPOLATIONMENU_H

#include <common.hpp>
using namespace geode::prelude;

class InterpolationMenu : public geode::Popup<CCArray*> {
protected:
	CCMenu* m_btnMenu = nullptr;
	CCMenu* m_mainMenu = nullptr;


	std::vector<std::unique_ptr<Spline>> loadedSplines;

	bool setup(CCArray* objects) override;

public:

	static InterpolationMenu* create(CCArray* objects);
	void on_button(CCObject* sender);
	void onNvm(CCObject* sender);
};


#endif
