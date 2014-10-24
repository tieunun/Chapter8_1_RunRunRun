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


	//��ͼ��������
	Size mapTiledNum = m_map->getMapSize();

	//��ͼ�������Ӵ�С
	Size titledSize = m_map->getTileSize();
    
	//��ͼ��С
	Size mapSize = Size(mapTiledNum.width * titledSize.width, 
		mapTiledNum.height * titledSize.height);

	//��Ļ��С
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//��������
	Point spritePos = getPosition();


	//�����������С����Ļ��һ�룬��ȡ��Ļ�е����꣬����ȡ���ǵ�����
	float x = std::max(spritePos.x, visibleSize.width / 2);
	float y = std::max(spritePos.y, visibleSize.height / 2);

	//���x,y������������Ͻǵļ���ֵ����ȡ����ֵ�����꣨����ֵ��ָ���õ�ͼ������Ļ��ɳ��ֺڱߵļ������꣩
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);


	//Ŀ���
	Point destPos = Point(x,y);

	//��Ļ�е�
	Point centerPos =  Point(visibleSize.width / 2,visibleSize.height / 2);

	//������Ļ�е����Ҫ�ƶ���Ŀ�ĵ�֮��ľ���
	Point viewPos = centerPos - destPos;
	
	parent->setPosition(viewPos);
}


void Player::setTagPosition(int x, int y)
{
	
	//�ж�ǰ���Ƿ񲻿�ͨ��
    //ȡ����ǰ��������
	Size spriteSize = m_sprite->getContentSize();

	Point dstPos = Point(x + spriteSize.width / 2,y);

	//��ȡ��ǰ����ǰ�������ڵ�ͼ�еĸ���λ��
	Point tiledPos = titleCoordForPosition(Point(dstPos.x, dstPos.y));

	//��ȡ��ͼ���ӵ�Ψһ��ʶ
	int titledGid = meta->getTileGIDAt(tiledPos);

	//��Ϊ0����������������
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

	//������Ϊ�����ƶ���ͼ
	setViewPointByPlayer();
}


Point Player::titleCoordForPosition(Point pos)
{
	Size mapTiledNum = m_map->getMapSize();

	Size titledSize = m_map->getTileSize();

	int x = pos.x / titledSize.width;

	//cocoss2d-x ��Ĭ��Y�������������ϵģ�����Ҫ��һ������Ĳ���
	int y = (700 - pos.y) / titledSize.height;

	//����������㿪ʼ����
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