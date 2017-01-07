#include "HelloWorldScene.h"
#include "Scene2.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

	auto tiaoItem = MenuItemImage::create(
		"next.png",
		"next.png",
		CC_CALLBACK_1(HelloWorld::sceneTiao, this));

	tiaoItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2 + 50));

    // create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, tiaoItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
	Label* lb1 = Label::createWithSystemFont("scene 1: bird fly", "Arial", 24);
	lb1->setPosition(Point(origin.x + visibleSize.width / 2 ,
		origin.y + visibleSize.height - 50));
	this->addChild(lb1, 1);

	// �����������
	Sprite* sp = Sprite::create("birds_1_11/1.png");
	sp->setPosition(Point(visibleSize.width/4, visibleSize.height / 2));
	this->addChild(sp);


	//������մ����¼�  
	this->setTouchEnabled(true);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	auto listen = EventListenerTouchOneByOne::create();

	listen->onTouchBegan = [](cocos2d::Touch* touch, cocos2d::Event *event){
		CCLog("onTouchBegan");
		return true;
	};

	listen->onTouchMoved = [](cocos2d::Touch* touch, cocos2d::Event *event){
		CCLog("onTouchMoved");
	};

	listen->onTouchCancelled = [](cocos2d::Touch* touch, cocos2d::Event *event){
		CCLog("onTouchCancelled");
	};

	listen->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event *event){
		CCLog("onTouchEnded");

		Point locInView = touch->getLocationInView(); // UI���� ���Ͻ�Ϊ����ԭ�㣬���ֻ�UI����
		Point loc = Director::getInstance()->convertToGL(locInView);  // opengl ����, ���½�Ϊ����ԭ��
		Point tarPos = touch->getLocation(); // = loc
		
		// �ƶ���ĳ����Ķ���
		/*MoveTo *movBy = MoveTo::create(3.2f, tarPos);
		Action* actions = Spawn::create(movBy, movBy, NULL);
		sp->runAction(actions);*/

		auto animation = Animation::create();
		for (int i = 1; i<11; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "birds_1_11/%0d.png", i);
			animation->addSpriteFrameWithFile(szName);
		}

		// should last 3.0 seconds. And there are 11 frames. 
		animation->setDelayPerUnit(3.0f / 11.0f);
		animation->setRestoreOriginalFrame(true);
		auto action = Animate::create(animation);
		//sp->runAction(Sequence::create(action, action->reverse(), NULL));

		float xx = tarPos.x - sp->getPositionX();
		float yy = tarPos.y - sp->getPositionY();
		MoveBy* moveBy = MoveBy::create(3.0f, Point(xx, yy));
		//sp->runAction(moveBy);

		// ͬʱִ����������
		auto actions = Spawn::create(action, moveBy,NULL);
		sp->runAction(actions);
	
	};
	eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);

    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void  HelloWorld::sceneTiao(cocos2d::Ref* pSender)
{
	TransitionScene * reScene = NULL;
	Scene * s = Scene2::createScene();
	float t = 2.2f;
	//    ���ã�����һ����ҳ�Ĺ��ɶ���
	//    ����1�����ɶ���������ʱ��
	//    ����2���л���Ŀ�곡���Ķ���
	//    ����3���Ƿ�����ҳ
	reScene = TransitionPageTurn::create(t, s, false);
	Director::getInstance()->replaceScene(reScene);

}
