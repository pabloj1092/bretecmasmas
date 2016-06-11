#include "WorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* BWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer1 = BWorld::create();
    layer1->AddBear();
    auto layer2 = BWorld::create();
    layer2->AddBack();

    
    // add layer as a child to scene
    scene->addChild(layer2);
    scene->addChild(layer1);


    // return the scene
    return scene;
}


bool BWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    this->schedule( schedule_selector(BWorld::gameLogic), 1.0 );

    
    return true;
}

void BWorld::gameLogic(float dt)
{
    this->AddMonster();
}


// on "init" you need to initialize your instance
void  BWorld::AddBear()
{
    //////////////////////////////
    // 1. super init first

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 3. add your codes below...
    
    // create and initialize a label

    
    amySprite = Sprite::create("bear1.png");
    
    amySprite->setPosition(Vec2((visibleSize.width/6)+origin.x, (visibleSize.height/5)+origin.y));
    amySprite->setScale(0.1);

    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(8);
    animFrames.pushBack(SpriteFrame::create("bear1.png", Rect(0,0,932,580)));
    animFrames.pushBack(SpriteFrame::create("bear2.png", Rect(0,0,932,580)));
    animFrames.pushBack(SpriteFrame::create("bear3.png", Rect(0,0,932,580)));
    animFrames.pushBack(SpriteFrame::create("bear4.png", Rect(0,0,932,580)));
    animFrames.pushBack(SpriteFrame::create("bear5.png", Rect(0,0,932,580)));
    animFrames.pushBack(SpriteFrame::create("bear6.png", Rect(0,0,932,580)));
    animFrames.pushBack(SpriteFrame::create("bear7.png", Rect(0,0,932,580)));
    animFrames.pushBack(SpriteFrame::create("bear8.png", Rect(0,0,932,580)));
    
    // create the animation out of the frames
    Animation* animation = Animation::createWithSpriteFrames(animFrames,0.1f );
    Animate* animate = Animate::create(animation);
    // run it and repeat it forever


    this->addChild(amySprite, 0);
    amySprite->runAction(RepeatForever::create(animate));

    auto jump = JumpBy::create(0.5, Vec2(0, 0), 300, 1);

    amySprite->runAction(jump);


    auto eventListener = EventListenerKeyboard::create();

    eventListener->onKeyPressed = CC_CALLBACK_2(BWorld::onKeyPressed, this);
    eventListener->onKeyReleased = CC_CALLBACK_2(BWorld::onKeyReleased, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

}




void BWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    auto jump = JumpBy::create(0.7, Vec2(0, 0), 200, 1);
    
    
    Vec2 loc = event->getCurrentTarget()->getPosition();
    switch(keyCode){
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_A:
            event->getCurrentTarget()->setPosition(--loc.x,loc.y);
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            event->getCurrentTarget()->setPosition(++loc.x,loc.y);
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        case EventKeyboard::KeyCode::KEY_W:
            event->getCurrentTarget()->runAction(jump);
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case EventKeyboard::KeyCode::KEY_S:
            event->getCurrentTarget()->setPosition(loc.x,--loc.y);
            break;
        default:
            log("Key with keycode %d pressed", keyCode);
            break;
            
    }
};


void BWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d pressed", keyCode);
};

void BWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}







void BWorld::AddBack()
{
    //////////////////////////////
    // 1. super init first
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(BWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
    // add a label shows "B World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hell World", "fonts/Marker Felt.ttf", 24);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                        origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add
    bgnd = Sprite::create("Pinkie_Pie.png");
    bgnd->setAnchorPoint(Vec2(0.5, 0.5));
    bgnd->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    grass1 = Sprite::create("bluegrass.png");
    grass1->setPosition(this->getBoundingBox().getMidX(), origin.y + grass1->getContentSize().height/2 );
    grass2 = Sprite::create("bluegrass.png");
    grass2->setPosition(this->getBoundingBox().getMidX() + grass1->getBoundingBox().size.width, origin.y + grass2->getContentSize().height/2 );
    grass3 = Sprite::create("bluegrass.png");
    grass3->setPosition(this->getBoundingBox().getMidX() + 2*grass2->getBoundingBox().size.width, origin.y + grass3->getContentSize().height/2 );

    this->addChild(bgnd, 0);
    this->addChild(grass1, 0);
    this->addChild(grass2, 0);
    this->addChild(grass3, 0);

    this->scheduleUpdate();
}




void BWorld::update(float delta){
    auto position = grass1->getPosition();
    position.x -= 250 * delta;
    if (position.x  < 0 - (grass1->getBoundingBox().size.width / 2))
        position.x = this->getBoundingBox().getMaxX() + grass1->getBoundingBox().size.width/2;
    grass1->setPosition(position);
    
    auto position2 = grass2->getPosition();
    position2.x -= 250 * delta;
    if (position2.x  < 0 - (grass2->getBoundingBox().size.width / 2))
        position2.x = this->getBoundingBox().getMaxX() + grass2->getBoundingBox().size.width/2;
    grass2->setPosition(position2);
    
    auto position3 = grass3->getPosition();
    position3.x -= 250 * delta;
    if (position3.x  < 0 - (grass3->getBoundingBox().size.width / 2))
        position3.x = this->getBoundingBox().getMaxX() + grass3->getBoundingBox().size.width/2;
    grass3->setPosition(position3);
    
}



void BWorld::AddMonster() {
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //monster = "queen.png"];
    //trap = "trap.png"];
    target = Sprite::create("queen.png" );
    
    // Determine where to spawn the target along the Y axis
    int minY = visibleSize.height/2;
    int maxY = visibleSize.height - target->getContentSize().height/2;
    int rangeY = maxY - minY;
    // srand( TimGetTicks() );
    int actualY = ( rand() % rangeY ) + minY;
    
    // Create the target slightly off-screen along the right edge,
    // and along a random position along the Y axis as calculated
    target->setPosition( ccp(visibleSize.width + (target->getContentSize().width/2),actualY) );
    this->addChild(target);
    
    // Determine speed of the target
    int minDuration = (int)2.0;
    int maxDuration = (int)4.0;
    int rangeDuration = maxDuration - minDuration;
    // srand( TimGetTicks() );
    int actualDuration = ( rand() % rangeDuration )
    + minDuration;
    
    // Create the actions
    CCFiniteTimeAction* actionMove = CCMoveTo::create( (float)actualDuration,
                     ccp(0 - target->getContentSize().width/2, actualY) );
    CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create( this, callfuncN_selector(BWorld::spriteMoveFinished));
    target->runAction( CCSequence::create(actionMove,
                                          actionMoveDone, NULL) );
}

// cpp with cocos2d-x
void BWorld::spriteMoveFinished(CCNode* sender)
{
    CCSprite *sprite = (CCSprite *)sender;
    this->removeChild(sprite, true);
}