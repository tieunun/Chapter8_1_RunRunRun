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
	Entity::setTagPosition(x,y);

	//������Ϊ�����ƶ���ͼ
	setViewPointByPlayer();
}