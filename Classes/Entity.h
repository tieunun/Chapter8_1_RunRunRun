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


	//���ÿ�����
	void setController(Controller* controller);



	//ʵ��SimpleMoveListener�ӿڷ���
	virtual void setTagPosition(int x, int y);
	virtual Point getTagPosition();

protected:
	Sprite* m_sprite;
	Controller* m_controller;
};

#endif