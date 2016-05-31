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