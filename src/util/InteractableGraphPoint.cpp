#include <InteractableGraphPoint.hpp>


using namespace geode::prelude;

InteractableGraphPoint::InteractableGraphPoint(Spline* s) : spline(s), _dragging(false) {};

InteractableGraphPoint* InteractableGraphPoint::create(const char* pszFileName, Spline* spline) {

	InteractableGraphPoint* ret = new InteractableGraphPoint(spline);
	if (ret && ret->initWithFile(pszFileName)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

$override
bool InteractableGraphPoint::initWithFile(const char* pszFileName) {
	if (!CCSprite::initWithFile(pszFileName)) { return false; }

	// Maybe extra stuff 4 latr
	return true;
}

$override
void InteractableGraphPoint::registerWithTouchDispatcher() {
	CCTouchDispatcher::get()->addTargetedDelegate(this, 0, true);
}

$override
bool InteractableGraphPoint::ccTouchBegan(CCTouch* touch, CCEvent* event) {
	_dragging = true;
	return true;
}

$override
void InteractableGraphPoint::ccTouchMoved(CCTouch* touch, CCEvent* event) {
	this->setPosition(touch->getLocation());
}

$override
void InteractableGraphPoint::ccTouchEnded(CCTouch* touch, CCEvent* event) {
	_dragging = false;
}

$override
void InteractableGraphPoint::ccTouchCancelled(CCTouch* touch, CCEvent* event) {
	_dragging = false;
}

// // // // // // // // // // // // // // // // // //

void InteractableGraphPoint::setTime(float t) {
	time = t;
	this->setPositionX(this->getParent()->getContentSize().width * t);
}

void InteractableGraphPoint::setValue(float v) {
	value = v;
}

void InteractableGraphPoint::setType(std::string t) {
	type = std::move(t);
}

void InteractableGraphPoint::setSpline(Spline* s) {
	spline = s;
}

bool InteractableGraphPoint::isDragging() {
	return _dragging;
}

// // // // //

float InteractableGraphPoint::getTime() const {
	return time;
}

float InteractableGraphPoint::getValue() const {
	return value;
}

const std::string& InteractableGraphPoint::getType() const {
	return type;
}

Spline* InteractableGraphPoint::getSpline() const {
	return spline;
}


