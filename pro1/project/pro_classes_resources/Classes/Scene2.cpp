#include "Scene2.h"

USING_NS_CC;

Scene* Scene2::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = Scene2::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Scene2::init()
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
										   CC_CALLBACK_1(Scene2::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
	Label* lb1 = Label::createWithSystemFont("scene two", "Arial", 24);
	lb1->setPosition(Point(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - 50));
	this->addChild(lb1, 1);


	// 创建精灵对象
	Sprite* sp = Sprite::create("bird.png");
	sp->setPosition(Point(50, visibleSize.height / 2));
	this->addChild(sp);

	// 创建贝塞尔曲线
	ccBezierConfig bezier;
	bezier.controlPoint_1 = Point(100, 0);  // 波谷偏向值
	bezier.controlPoint_2 = Point(200, 250); // 波峰偏向值 
	bezier.endPosition = Point(300, 50); // 动作终点

	// 创建动作
	BezierTo* bezierTo = BezierTo::create(4.0f, bezier);

	// 执行动作
	sp->runAction(bezierTo);


	//允许接收触摸事件  
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

		Point locInView = touch->getLocationInView(); // UI坐标 左上角为坐标原点，与手机UI类似
		Point loc = Director::getInstance()->convertToGL(locInView);  // opengl 坐标, 左下角为坐标原点
		Point tarPos = touch->getLocation(); // = loc
		
		// 移动到某个点的动作
		MoveTo *movBy = MoveTo::create(3.2f, tarPos);
		Action* actions = Spawn::create(movBy, movBy, NULL);
		sp->runAction(actions);
	
	};
	eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);
	
    return true;
}

void Scene2::menuCloseCallback(Ref* pSender)
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
