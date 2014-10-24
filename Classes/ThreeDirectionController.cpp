#include "ThreeDirectionController.h"

bool ThreeDirectionController::init()
{
	this->m_iXSpeed = 0;
	this->m_iYSpeed = 0;

	//ע����Ļ�����¼�
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

	//���ƶ�������X��y��������������
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
		//��ȡ�������꣬����cocos2d-x
		Point touchPos = Director::getInstance()->convertToGL(touch->getPreviousLocationInView());

		//�����ƶ��������
		Point pos = m_controllerListener->getTagPosition();

		//�ж��������ƶ����������ƶ�
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
      //ֹͣY�����ϵ��ƶ�
		setiYSpeed(0);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}