#ifndef __WORLD_SCENE_H__
#define __WORLD_SCENE_H__

#include "cocos2d.h"

class BWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void AddBear();
    void AddBack();


    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(BWorld);
    
    //void update(float) override;
    
    void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent);
    
    void update(float) override;
    
    // Keyboard interrupt
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    
private:
    cocos2d::Sprite* amySprite; // The bear
    cocos2d::Sprite* bgnd; // The pinkie pie
    cocos2d::Sprite* grass1; //Blue grass
    cocos2d::Sprite* grass2;
    cocos2d::Sprite* grass3;
};

#endif // __WORLD_SCENE_H__
