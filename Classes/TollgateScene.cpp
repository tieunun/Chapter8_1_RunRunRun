#include "TollgateScene.h"
#include "Player.h"
#include "SimpleMoveController.h"
#include "ThreeDirectionController.h"

Scene* TollgateScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TollgateScene::create();
	scene->addChild(layer);
	return scene;
}


bool TollgateScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//��ͼ
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Animation/guangdai.plist","Animation/guangdai.png");



	//����Tiled��ͼ����ӵ�������
 	TMXTiledMap* map = TMXTiledMap::create("level01.tmx");
 
 	this->addChild(map);


	addPlayer(map);   //�������
	

	Director::getInstance()->setProjection(Director::Projection::_2D);
	
	return true;
}


void TollgateScene::addPlayer(TMXTiledMap* map)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//��������
	Sprite* playerSprite = Sprite::create("player.png");
	playerSprite->setFlippedX(true);
	//���������󶨵���Ҷ�����
	Player* pPlayer = Player::create();
	pPlayer->bindSprite(playerSprite);
	pPlayer->run();
	pPlayer->setTiledMap(map);


	//�����������
	pPlayer->setPosition(Point(100,visibleSize.height / 4));


	//�������ӵ���ͼ
	map->addChild(pPlayer);


	//���ض����
	TMXObjectGroup* objGroup = map->getObjectGroup("objects");

	//��������������
	ValueMap playPointMap = objGroup->getObject("PlayerPoint");
	float playerX= playPointMap.at("x").asFloat();
	float playerY= playPointMap.at("y").asFloat();

	pPlayer->setPosition(Point(playerX,playerY));

	



	/*	������Ҽ��ƶ������� 
	SimpleMoveController* simpleMoveController = SimpleMoveController::create();

    //�����ƶ��ٶ�
	simpleMoveController->setiSpeed(1);

	//������Ҫ��ӵ������в�����update������
	this->addChild(simpleMoveController);
	//���ÿ���������������
	pPlayer->setController(simpleMoveController);
	*/


	ThreeDirectionController* threeMoveControll = ThreeDirectionController::create();
	threeMoveControll->setiXSpeed(1);
	threeMoveControll->setiYSpeed(0);

	this->addChild(threeMoveControll);

	pPlayer->setController(threeMoveControll);





	
}