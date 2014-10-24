#ifndef _TOLLGATE_SCENE_H_
#define _TOLLGATE_SCENE_H_

#include "cocos2d.h"
using namespace cocos2d;


class TollgateScene :public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	

	CREATE_FUNC(TollgateScene);

public:
	void addPlayer(TMXTiledMap* map);
};



#endif // !_TOLLGATE_SCENE_H_
