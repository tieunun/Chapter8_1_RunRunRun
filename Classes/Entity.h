#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "cocos2d.h"
using namespace cocos2d;

#include "Controller.h"
#include "ControllerListener.h"


class Entity :public Node, public ControllerListener
{
public:
	void bindSprite(Sprite* sprite);


	//设置控制器
	void setController(Controller* controller);



	//实现SimpleMoveListener接口方法
	virtual void setTagPosition(int x, int y);
	virtual Point getTagPosition();

protected:
	Sprite* m_sprite;
	Controller* m_controller;
};

#endif