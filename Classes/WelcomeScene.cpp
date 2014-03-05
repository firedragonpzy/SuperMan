#include "WelcomeScene.h"
#include "GameScene.h"
#include "plane.h"

USING_NS_CC;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern void showAds(bool show);
#endif

Scene* WelcomeScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WelcomeLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool WelcomeLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto bgSprite = Sprite::create("index_bg.jpg");
    bgSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bgSprite, 0);

	auto titleSprite= Sprite::create("LOGO.png");
	titleSprite->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - titleSprite->getContentSize().height / 2 - 160));
	this->addChild(titleSprite);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("resources.plist");

	auto planeSprite = Plane::create();
	planeSprite->setScale(2.0f);
	planeSprite->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + titleSprite->getPositionY() - titleSprite->getContentSize().height - planeSprite->getContentSize().height / 2 - 100));
	this->addChild(planeSprite);

	auto startBtnItem = MenuItemImage::create("", "", [](Object *sender) {
				Scene *scene = GameScene::scene();
				Director::getInstance()->replaceScene(CCTransitionCrossFade::create(1.2f,scene));
		});
	auto btnSprite = Sprite::createWithSpriteFrameName("btn_yellow.png");
	startBtnItem->setNormalSpriteFrame(btnSprite->getDisplayFrame());
	startBtnItem->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + startBtnItem->getContentSize().height / 2 + 100));
	auto startMenu = Menu::create(startBtnItem, NULL);
	startMenu->setPosition(Point::ZERO);
	this->addChild(startMenu);

	auto startBtnText = Sprite::createWithSpriteFrameName("start_game_text.png");
	startBtnText->setPosition(startBtnItem->getPosition());
	this->addChild(startBtnText);

	//auto snowSprite2 = Sprite::create("snow.png");
	//snowSprite2->setPosition(startBtnItem->getPosition());
	//snowSprite2->runAction(RepeatForever::create(Sequence::create(FadeIn::create(1.0f), FadeOut::create(0.5f), NULL)));
	//this->addChild(snowSprite2);

	auto btnParticleEmitter = ParticleSystemQuad::create("btn_snow.plist");
	btnParticleEmitter->setPosition(Point(startBtnItem->getPositionX(), startBtnItem->getPositionY() - startBtnItem->getContentSize().height / 2 + 20));
	auto btnParticleBatch = ParticleBatchNode::createWithTexture(btnParticleEmitter->getTexture());
	btnParticleBatch->addChild(btnParticleEmitter);
	this->addChild(btnParticleBatch, 5);

	//auto particleSprite = Sprite::create("snow.png");
	//this->addChild(particleSprite);

	auto particleEmitter = ParticleSystemQuad::create("snow.plist");
	particleEmitter->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height + 5));
	auto particleBatch = ParticleBatchNode::createWithTexture(particleEmitter->getTexture());
	particleBatch->addChild(particleEmitter);
	this->addChild(particleBatch, 5);

	//auto sunParticle = ParticleSun::createWithTotalParticles(20);
 //   sunParticle->setTexture( Director::getInstance()->getTextureCache()->addImage("fire.png") );
	//sunParticle->setPosition(Point(planeSprite->getPositionX(), planeSprite->getPositionY() - planeSprite->getContentSize().height / 2 - 30));
	//this->addChild(sunParticle, 10);

	auto starSprite = Sprite::create("star.png");
	starSprite->setScale(0.4f);
	starSprite->setPosition(Point(startBtnItem->getPosition().x - startBtnItem->getContentSize().width / 2, startBtnItem->getPosition().y - startBtnItem->getContentSize().height / 2));	
	this->addChild(starSprite, 10);

	auto _emitter = particleInit();
	_emitter->setPosition(Point(startBtnItem->getPosition().x - startBtnItem->getContentSize().width / 2 - 2, startBtnItem->getPosition().y  - startBtnItem->getContentSize().height / 2 + 3));

	float X = 2;
	auto path = MyPathFun(X, startBtnItem->getContentSize().height, startBtnItem->getContentSize().width - 2 * X, true);

	starSprite->runAction(path);
	_emitter->runAction(path->clone());

	auto starSprite2 = Sprite::create("star.png");
	starSprite2->setScale(0.4f);
	starSprite2->setPosition(Point(startBtnItem->getPosition().x + startBtnItem->getContentSize().width / 2, startBtnItem->getPosition().y + startBtnItem->getContentSize().height / 2));	
	this->addChild(starSprite2, 10);

	auto _emitter2 = particleInit();
	_emitter2->setPosition(Point(startBtnItem->getPosition().x + startBtnItem->getContentSize().width / 2 - 2, startBtnItem->getPosition().y  + startBtnItem->getContentSize().height / 2 + 3));
	auto path2 = MyPathFun(X, startBtnItem->getContentSize().height, startBtnItem->getContentSize().width - 2 * X, false);

	starSprite2->runAction(path2);
	_emitter2->runAction(path2->clone());


	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		showAds(true);
	#endif

    return true;
}


void WelcomeLayer::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void WelcomeLayer::menuNewCallback(Object* pSender)
{

}


ParticleSystem* WelcomeLayer::particleInit(){
	auto _emitter = new ParticleSystemQuad();
	_emitter->initWithTotalParticles(100);
	addChild(_emitter, 10);
	_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("star.png"));
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
	_emitter->setLife(1.0);
	_emitter->setLifeVar(0);

	// spin of particles
	_emitter->setStartSpin(0);
	_emitter->setStartSpinVar(0);
	_emitter->setEndSpin(0);
	_emitter->setEndSpinVar(0);

	// color of particles
	Color4F startColor(1.0f, 1.0f, 0.9f, 1.0f);
	_emitter->setStartColor(startColor);

	Color4F startColorVar(0, 0, 0, 1.0f);
	_emitter->setStartColorVar(startColorVar);

	Color4F endColor(1.0f, 1.0f, 1.0f, 0.1f);
	_emitter->setEndColor(endColor);

	Color4F endColorVar(0, 0, 0, 0.1f);
	_emitter->setEndColorVar(endColorVar);
	//Color4F setStartColor(Color4F(Color4B(50, 50, 50, 50)));
	//Color4F setEndColor(Color4F(Color4B(0, 0, 0, 0)));
	// size, in pixels
	_emitter->setStartSize(15);
	_emitter->setStartSizeVar(1);
	_emitter->setEndSize(0);

	// emits per second
	_emitter->setEmissionRate(_emitter->getTotalParticles() / _emitter->getLife());

	// additive
	_emitter->setBlendAdditive(false);

	return _emitter;
}

RepeatForever* WelcomeLayer::MyPathFun(float controlX, float controlY, float w,  bool isClockwise)
{
	ccBezierConfig bezier1;
	if(isClockwise) {
		bezier1.controlPoint_1 = Point(-controlX, 0);
		bezier1.controlPoint_2 = Point(-controlX, controlY);
		bezier1.endPosition = Point(0, controlY);
	} else {
			bezier1.controlPoint_1 = Point(controlX, 0);
			bezier1.controlPoint_2 = Point(controlX, -controlY);
			bezier1.endPosition = Point(0, -controlY);
	}

	auto bezierBy1 = BezierBy::create(0.8f, bezier1);

	float t_w = w;
	if(!isClockwise) {
		t_w = -w;
	}
	auto move1 = MoveBy::create(1.0f, Point(t_w, 0));

	ccBezierConfig bezier2;
	if(isClockwise) {
			bezier2.controlPoint_1 = Point(controlX, 0);
	bezier2.controlPoint_2 = Point(controlX, -controlY);
	bezier2.endPosition = Point(0, -controlY);
	}else {
					bezier2.controlPoint_1 = Point(-controlX, 0);
	bezier2.controlPoint_2 = Point(-controlX, controlY);
	bezier2.endPosition = Point(0, controlY);
	}

	auto bezierBy2 = BezierBy::create(0.8f, bezier2);
	auto move2 = MoveBy::create(1.0f, Point(-t_w, 0));
	auto path = RepeatForever::create(Sequence::create(bezierBy1, move1, bezierBy2, move2, NULL));
	return path;
}

