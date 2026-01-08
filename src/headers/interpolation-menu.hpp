#ifndef INTERPOLATIONMENU_H
#define INTERPOLATIONMENU_H

#include <common.hpp>
using namespace geode::prelude;

class InterpolationMenu : public geode::Popup<Spline*> {
protected:

	bool setup(Spline* s) override;

public:

	static InterpolationMenu* create(Spline* s);
};


#endif
