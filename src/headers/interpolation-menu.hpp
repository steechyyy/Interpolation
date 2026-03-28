#pragma once


using namespace geode::prelude;

class InteractableGraphPoint;

class InterpolationMenu : public Popup {
protected:

	CCMenu* m_btnMenu = nullptr;
	CCMenu* m_splineMenu = nullptr;

	std::vector<InteractableGraphPoint*> graphDots;
	std::vector<std::unique_ptr<Spline>> loadedSplines;

	bool init(CCArray* objects);

public:

	static InterpolationMenu* create(CCArray* objects) {
		auto popup = new InterpolationMenu;
		if (popup->init(objects)) {
			popup->autorelease();
			return popup;
		}
		delete popup;
		return nullptr;
	};


	void on_button(CCObject* sender);
	void onNvm(CCObject* sender);
};
