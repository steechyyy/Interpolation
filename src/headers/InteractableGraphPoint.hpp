
using namespace geode::prelude;


class Spline;

class InteractableGraphPoint : public cocos2d::CCSprite, public cocos2d::CCTouchDelegate {
public:
	virtual void registerWithTouchDispatcher();

	InteractableGraphPoint(Spline* spline);

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event) override;
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event) override;
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event) override;
	virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event) override;

	virtual bool initWithFile(const char* pszFileName);

	static InteractableGraphPoint* create(const char* pszFileName, Spline* spline);

	
	void setTime(float t);
	void setValue(float v);
	void setType(std::string t);
	void setSpline(Spline* s);

	bool isDragging();

	float getTime() const;
	float getValue() const;
	const std::string& getType() const;
	Spline* getSpline() const;


private:
	float time; // internal time position
	float value;// internal value position

	std::string type; // Datatype of the value (int, float, ...)
	Spline* spline; // Parent spline
	bool _dragging; // Is the point being dragged


	void updatePoint();
};