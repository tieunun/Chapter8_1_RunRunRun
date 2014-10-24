#ifndef _SIMPLEMOVECONTROLLER_H_
#define _SIMPLEMOVECONTROLLER_H_

#include "Controller.h"
#include "cocos2d.h"

using namespace cocos2d;

class SimpleMoveController :public Controller
{
public:
	CREATE_FUNC(SimpleMoveController);

	virtual bool init();
	virtual void update(float dt);

	//设置移动速度
	void setiSpeed(int iSpeed);

private:
	int m_iSpeed;
};



#endif