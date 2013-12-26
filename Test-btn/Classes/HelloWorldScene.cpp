#include "HelloWorldScene.h"

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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);


	auto layer = LayerColor::create(Color4B(0, 0, 0, 255));
	addChild(layer, -10);

	//按钮
	auto btnSprite = Sprite::create("btn.png");
	btnSprite->setPosition(Point(200, 250));
	btnSprite->setAnchorPoint(Point(0, 0));
	this->addChild(btnSprite, 1);
	
	auto starSprite = Sprite::create("star1.png");
	starSprite->setScale(0.4f);
	this->addChild(starSprite, 10);

	auto _emitter = particleInit();
	starSprite->setPosition(Point(btnSprite->getPosition().x + btnSprite->getContentSize().height / 2 - 4, btnSprite->getPosition().y));	
	

	_emitter->setPosition(Point(btnSprite->getPosition().x + btnSprite->getContentSize().height / 2 - 6, btnSprite->getPosition().y + 3));

	float X = btnSprite->getContentSize().height / 2;
	auto path = MyPathFun(X+10, btnSprite->getContentSize().height, btnSprite->getContentSize().width - X * 2 /*+ starSprite->getContentSize().width*/);

	starSprite->runAction(path);
	_emitter->runAction(path->clone());

	//按钮1
	auto btnSprite1 = Sprite::create("btn1.png");
	btnSprite1->setPosition(Point(600, 250));
	btnSprite1->setAnchorPoint(Point(0, 0));
	this->addChild(btnSprite1, 10);

	auto path1 = MyPathFun(75, btnSprite1->getContentSize().height, 80);
	auto _emitter1 = particleInit();
	auto starSprite1 = Sprite::create("star1.png");
	starSprite1->setScale(0.4f);
	this->addChild(starSprite1, 10);

	starSprite1->setPosition(Point(btnSprite1->getPosition().x + btnSprite1->getContentSize().height / 2 - 4, btnSprite1->getPosition().y));
	_emitter1->setPosition(Point(btnSprite1->getPosition().x + btnSprite1->getContentSize().height / 2 - 5, btnSprite1->getPosition().y + 3));

	starSprite1->runAction(path1);
	_emitter1->runAction(path1->clone());


	//按钮2（矩形）
	auto btnSprite2 = Sprite::create("btn0.png");
	btnSprite2->setPosition(Point(350, 150));
	btnSprite2->setAnchorPoint(Point(0, 0));
	this->addChild(btnSprite2, 10);

	auto path2 = MyPathFun(0, btnSprite2->getContentSize().height, btnSprite2->getContentSize().width );
	auto _emitter2 = particleInit();
	auto starSprite2 = Sprite::create("star1.png");
	starSprite2->setScale(0.4f);
	this->addChild(starSprite2, 10);

	starSprite2->setPosition(Point(btnSprite2->getPosition().x  - 2, btnSprite2->getPosition().y));
	_emitter2->setPosition(Point(btnSprite2->getPosition().x  - 2, btnSprite2->getPosition().y + 3));

	starSprite2->runAction(path2);
	_emitter2->runAction(path2->clone());

	return true;
}

ParticleSystem* HelloWorld::particleInit(){
	auto _emitter = new ParticleSystemQuad();
	_emitter->initWithTotalParticles(50);
	addChild(_emitter, 10);
	_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("point.png"));
	_emitter->setAnchorPoint(Point(0, 0));
	// duration
	_emitter->setDuration(ParticleSystem::DURATION_INFINITY);

	// radius mode
	_emitter->setEmitterMode(ParticleSystem::Mode::RADIUS);

	// radius mode: start and end radius in pixels
	_emitter->setStartRadius(4);
	_emitter->setStartRadiusVar(1);
	_emitter->setEndRadius(ParticleSystem::START_RADIUS_EQUAL_TO_END_RADIUS);
	_emitter->setEndRadiusVar(0);

	// radius mode: degrees per second
	_emitter->setRotatePerSecond(100);
	_emitter->setRotatePerSecondVar(0);

	// angle
	_emitter->setAngle(90);
	_emitter->setAngleVar(0);

	// emitter position
	auto size = Director::getInstance()->getWinSize();
	_emitter->setPosVar(Point::ZERO);

	// life of particles
	_emitter->setLife(0.5);
	_emitter->setLifeVar(0);

	// spin of particles
	_emitter->setStartSpin(0);
	_emitter->setStartSpinVar(0);
	_emitter->setEndSpin(0);
	_emitter->setEndSpinVar(0);

	// color of particles
	Color4F startColor(0.0f, 0.8f, 0.9f, 1.0f);
	_emitter->setStartColor(startColor);

	Color4F startColorVar(0, 0, 0, 1.0f);
	_emitter->setStartColorVar(startColorVar);

	Color4F endColor(1.0f, 1.0f, 1.0f, 0.1f);
	_emitter->setEndColor(endColor);

	Color4F endColorVar(0, 0, 0, 0.1f);
	_emitter->setEndColorVar(endColorVar);
	Color4F setStartColor(Color4F(Color4B(50, 50, 50, 50)));
	Color4F setEndColor(Color4F(Color4B(0, 0, 0, 0)));
	// size, in pixels
	_emitter->setStartSize(20);
	_emitter->setStartSizeVar(1);
	_emitter->setEndSize(0);

	// emits per second
	_emitter->setEmissionRate(_emitter->getTotalParticles() / _emitter->getLife());

	// additive
	_emitter->setBlendAdditive(false);

	return _emitter;
}

RepeatForever* HelloWorld::MyPathFun(float controlX, float controlY, float w)
{
	ccBezierConfig bezier1;
	bezier1.controlPoint_1 = Point(-controlX, 0);
	bezier1.controlPoint_2 = Point(-controlX, controlY);
	bezier1.endPosition = Point(0, controlY);
	auto bezierBy1 = BezierBy::create(0.8f, bezier1);

	auto move1 = MoveBy::create(0.8f, Point(w, 0));

	ccBezierConfig bezier2;
	bezier2.controlPoint_1 = Point(controlX, 0);
	bezier2.controlPoint_2 = Point(controlX, -controlY);
	bezier2.endPosition = Point(0, -controlY);
	auto bezierBy2 = BezierBy::create(0.8f, bezier2);
	auto move2 = MoveBy::create(0.8f, Point(-w, 0));
	auto path = RepeatForever::create(Sequence::create(bezierBy1, move1, bezierBy2, move2, NULL));
	return path;
}


void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
