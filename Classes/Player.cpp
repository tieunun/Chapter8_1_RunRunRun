#include "Player.h"
#include "AnimationUtil.h"


bool Player::init()
{
	isJumping = false;
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

	this->meta = m_map->getLayer("meta");
	this->meta->setVisible(true);
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
	
	//判断前面是否不可通行
    //取主角前方的坐标
	Size spriteSize = m_sprite->getContentSize();

	Point dstPos = Point(x + spriteSize.width / 2,y);

	//获取当前主角前方坐标在地图中的格子位置
	Point tiledPos = titleCoordForPosition(Point(dstPos.x, dstPos.y));

	//获取地图格子的唯一标识
	int titledGid = meta->getTileGIDAt(tiledPos);

	//不为0，代表存在这个格子
	if (titledGid != 0)
	{
		Value properties = m_map->getPropertiesForGID(titledGid);

		ValueMap propertiesMap = properties.asValueMap();

		if (propertiesMap.find("Collidable") != propertiesMap.end())
		{

			Value prop = propertiesMap.at("Collidable");

			if (prop.asString().compare("true") == 0 && isJumping == false)
			{
				isJumping = true;

				auto jumpBy = JumpBy::create(0.5f,Point(-100,0),80,1);
				CallFunc* callfunc = CallFunc::create([&](){
					isJumping = false;
				});

				auto acitons = Sequence::create(jumpBy,callfunc,NULL);
				this->runAction(acitons);
			}


		
		}

		if (propertiesMap.find("food") != propertiesMap.end())
		{
			Value prop = properties.asValueMap().at("food");
			if (prop.asString().compare("true") == 0)
			{
				TMXLayer* barrier = m_map->getLayer("barrier");
				barrier->removeTileAt(tiledPos);
			}
		}



	}





	Entity::setTagPosition(x,y);

	//以主角为中心移动地图
	setViewPointByPlayer();
}


Point Player::titleCoordForPosition(Point pos)
{
	Size mapTiledNum = m_map->getMapSize();

	Size titledSize = m_map->getTileSize();

	int x = pos.x / titledSize.width;

	//cocoss2d-x 的默认Y坐标是由下至上的，所以要做一个相减的操作
	int y = (700 - pos.y) / titledSize.height;

	//格子坐标从零开始计算
	if (x > 0)
	{
		x -= 1;
	}
	if (y > 0)
	{
		y -= 0;
	}

	return Point(x, y);
}