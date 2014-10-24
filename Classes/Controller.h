#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "ControllerListener.h"
#include "cocos2d.h"

using namespace cocos2d;

class Controller :public Node
{
public:
	//…Ë÷√º‡Ã˝∂‘œÛ
	void setControllerListerer(ControllerListener* controllerListener);

protected:
    ControllerListener* m_controllerListener;	

};



#endif