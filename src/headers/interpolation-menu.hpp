#ifndef INTERPOLATIONMENU_H
#define INTERPOLATIONMENU_H

#include <common.hpp>
using namespace geode::prelude;

class InterpolationMenu : public geode::Popup<std::string const&> {
protected:

	bool setup(std::string const& value) override;

public:

	static InterpolationMenu* create(std::string const& text);
};


#endif
