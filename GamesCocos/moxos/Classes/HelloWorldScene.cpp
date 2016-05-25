#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

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

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto mySprite = Sprite::create("bear1.png");
    mySprite->setPosition(Point((visibleSize.width/6)+origin.x, (visibleSize.height/5)+origin.y));
    mySprite->setScale(0.2);

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
    Animation* animation = Animation::createWithSpriteFrames(animFrames,0.021f );
    Animate* animate = Animate::create(animation);
    // run it and repeat it forever


    this->addChild(mySprite);
    mySprite->runAction(RepeatForever::create(animate));

    auto jump = JumpBy::create(0.5, Vec2(0, 0), 300, 1);
    mySprite->runAction(jump);


    auto eventListener = EventListenerKeyboard::create();



    eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event){

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
                event->getCurrentTarget()->setPosition(loc.x,++loc.y);
                break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            case EventKeyboard::KeyCode::KEY_S:
                event->getCurrentTarget()->setPosition(loc.x,--loc.y);
                break;
            default:

              break;

        }
    };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,mySrite);



    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    // auto sprite = Sprite::create("HelloWorld.png");
    //
    // // position the sprite on the center of the screen
    // sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    //
    // // add the sprite as a child to this layer
    // this->addChild(sprite, 0);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
