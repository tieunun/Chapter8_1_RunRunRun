#ifndef _THREE_DIRECTION_CONTROLLER_H_
#define _THREE_DIRECTION_CONTROLLER_H_

#include "Controller.h"
#include "cocos2d.h"

using namespace cocos2d;

class ThreeDirectionController :public Controller
{
public:
	CREATE_FUNC(ThreeDirectionController);

	virtual bool init();
	virtual void update(float dt);

	//设置X方向的移动速度
	void setiXSpeed(int iSpeed);

	//设置y方向的移动速度
	void setiYSpeed(int iSpeed);

private:
	int m_iXSpeed;
	int m_iYSpeed;

	//注册屏幕触摸事件
	void registerTouchEvent();
};



#endif