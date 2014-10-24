#ifndef _CONTROLLERLISTENER_H_
#define _CONTROLLERLISTENER_H_

#include "cocos2d.h"

using namespace cocos2d;

class ControllerListener 
{
public:
   //����Ŀ������
	virtual void setTagPosition(int x, int y) = 0;

	//��ȡĿ������
	virtual Point getTagPosition() = 0;

};



#endif