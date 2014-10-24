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
	//�ж������Ƿ���ײ���ϰ���ڷ�����
	bool isJumping;

	//�����ײ�ĵ�ͼ��
	TMXLayer* meta;

	//����������ת��Ϊ��ͼ��������
	Point titleCoordForPosition(Point pos);
};


#endif