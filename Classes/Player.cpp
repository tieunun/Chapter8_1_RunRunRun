#include "Player.h"
#include "AnimationUtil.h"


bool Player::init()
{
   return true;
}

void Player::run()
{
	Animation* animation = AnimationUtil::createWithSingleFrameName("guangdai",0.1f,-1);
	
	Animate* aciton = Animate::create(animation);
    m_sprite->runAction(aciton);
	m_sprite->setRotation(90.0f);
}

void Player::setTiledMap(TMXTiledMap* map)
{
	this->m_map = map;
}


void Player::setViewPointByPlayer()
{
	if (m_sprite == NULL)
	{
		return;
	}

	Layer* parent = (Layer*)getParent();


	//地图方块数量
	Size mapTiledNum = m_map->getMapSize();

	//地图单个格子大小
	Size titledSize = m_map->getTileSize();
    
	//地图大小
	Size mapSize = Size(mapTiledNum.width * titledSize.width, 
		mapTiledNum.height * titledSize.height);

	//屏幕大小
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//主角坐标
	Point spritePos = getPosition();


	//如果主角坐标小于屏幕的一半，则取屏幕中点坐标，否则取主角的坐标
	float x = std::max(spritePos.x, visibleSize.width / 2);
	float y = std::max(spritePos.y, visibleSize.height / 2);

	//如果x,y的坐标大于右上角的极限值，则取极限值的坐标（极限值是指不让地图超出屏幕造成出现黑边的极限坐标）
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);


	//目标点
	Point destPos = Point(x,y);

	//屏幕中点
	Point centerPos =  Point(visibleSize.width / 2,visibleSize.height / 2);

	//计算屏幕中点和所要移动的目的点之间的距离
	Point viewPos = centerPos - destPos;
	
	parent->setPosition(viewPos);
}


void Player::setTagPosition(int x, int y)
{
	Entity::setTagPosition(x,y);

	//以主角为中心移动地图
	setViewPointByPlayer();
}