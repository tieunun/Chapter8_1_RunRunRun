#include "ThreeDirectionController.h"

bool ThreeDirectionController::init()
{
	this->m_iXSpeed = 0;
	this->m_iYSpeed = 0;

	//注册屏幕触摸事件
	registerTouchEvent();

	this->scheduleUpdate();
	return true;
}

void ThreeDirectionController::update(float dt)
{
	if (m_controllerListener == NULL)
	{
		return ;
	}

	//让移动对象在X和y方向上增加坐标
	Point cunPos = m_controllerListener->getTagPosition();
	cunPos.x += m_iXSpeed;
	m_controllerListener->setTagPosition(cunPos.x + m_iXSpeed, cunPos.y + m_iYSpeed);
}


void ThreeDirectionController::setiXSpeed(int iSpeed)
{
	this->m_iXSpeed = iSpeed;
}

void ThreeDirectionController::setiYSpeed(int iSpeed)
{
	this->m_iYSpeed = iSpeed;
}


void ThreeDirectionController::registerTouchEvent()
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [](Touch* touch, Event* event)
	{
		return true;
	};

	listener->onTouchMoved = [&](Touch* touch, Event* event)
	{
		//获取单击坐标，基于cocos2d-x
		Point touchPos = Director::getInstance()->convertToGL(touch->getPreviousLocationInView());

		//被控制对象的坐标
		Point pos = m_controllerListener->getTagPosition();

		//判断是向上移动还是向下移动
		int iSpeed = 0;
		if (touchPos.y > pos.y)
		{
			iSpeed = 1;
		}
		else
		{
			iSpeed = -1;
		}

		setiYSpeed(iSpeed);

	};

	listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
      //停止Y坐标上的移动
		setiYSpeed(0);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}