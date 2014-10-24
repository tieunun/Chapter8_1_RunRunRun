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

	//大图
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Animation/guangdai.plist","Animation/guangdai.png");



	//加载Tiled地图，添加到场景中
 	TMXTiledMap* map = TMXTiledMap::create("level01.tmx");
 
 	this->addChild(map);


	addPlayer(map);   //加载玩家
	

	Director::getInstance()->setProjection(Director::Projection::_2D);
	
	return true;
}


void TollgateScene::addPlayer(TMXTiledMap* map)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//创建精灵
	Sprite* playerSprite = Sprite::create("player.png");
	playerSprite->setFlippedX(true);
	//将精灵对象绑定到玩家对象上
	Player* pPlayer = Player::create();
	pPlayer->bindSprite(playerSprite);
	pPlayer->run();
	pPlayer->setTiledMap(map);


	//设置玩家坐标
	pPlayer->setPosition(Point(100,visibleSize.height / 4));


	//将玩家添加到地图
	map->addChild(pPlayer);


	//加载对象层
	TMXObjectGroup* objGroup = map->getObjectGroup("objects");

	//加载玩家坐标对象
	ValueMap playPointMap = objGroup->getObject("PlayerPoint");
	float playerX= playPointMap.at("x").asFloat();
	float playerY= playPointMap.at("y").asFloat();

	pPlayer->setPosition(Point(playerX,playerY));

	



	/*	创建玩家简单移动控制器 
	SimpleMoveController* simpleMoveController = SimpleMoveController::create();

    //设置移动速度
	simpleMoveController->setiSpeed(1);

	//控制器要添加到场景中才能让update被调用
	this->addChild(simpleMoveController);
	//设置控制器到主角身上
	pPlayer->setController(simpleMoveController);
	*/


	ThreeDirectionController* threeMoveControll = ThreeDirectionController::create();
	threeMoveControll->setiXSpeed(1);
	threeMoveControll->setiYSpeed(0);

	this->addChild(threeMoveControll);

	pPlayer->setController(threeMoveControll);





	
}