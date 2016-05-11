//
//  GraphBack.cpp
//  moxos
//
//  Created by Francisco Molina Castro on 7/5/16.
//
//

#include "GraphBack.h"

USING_NS_CC;

Scene* GraphBack::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GraphBack::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GraphBack::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GraphBack::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hell World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    // add 
    sprite = Sprite::create("Pinkie_Pie.png");
    sprite->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMidY());
    sprite2 = Sprite::create("Pinkie_Pie.png");
    sprite2->setPosition(sprite->getBoundingBox().getMidX() + sprite->getBoundingBox().size.width, sprite->getBoundingBox().getMidY());

    this->addChild(sprite, 0);
    this->addChild(sprite2, 0);

    this->scheduleUpdate();
    
    // position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // position the sprite on the whole screen
    //sprite->setAnchorPoint(Vec2(0.5, 0.5));
    //sprite->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    
    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);
    
    return true;
}


void GraphBack::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void GraphBack::update(float delta){
    auto position = sprite->getPosition();
    position.x -= 250 * delta;
    if (position.x  < 0 - (sprite->getBoundingBox().size.width / 2))
        position.x = this->getBoundingBox().getMaxX() + sprite->getBoundingBox().size.width/2;
    sprite->setPosition(position);
    auto position2 = sprite2->getPosition();
    position2.x -= 250 * delta;
    if (position2.x  < 0 - (sprite2->getBoundingBox().size.width / 2))
        position2.x = this->getBoundingBox().getMaxX() + sprite2->getBoundingBox().size.width/2;
    sprite2->setPosition(position2);
}