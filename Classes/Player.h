#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"

class Player :public Entity
{
public:
	CREATE_FUNC(Player);
	virtual bool init();
	void run();

public:

	void setTiledMap(TMXTiledMap* map);
	void setViewPointByPlayer();
	virtual void setTagPosition(int x, int y);

private:
	TMXTiledMap* m_map;


private:
	//判断主角是否碰撞了障碍物，在反弹中
	bool isJumping;

	//检测碰撞的地图层
	TMXLayer* meta;

	//将像素坐标转化为地图格子坐标
	Point titleCoordForPosition(Point pos);
};


#endif