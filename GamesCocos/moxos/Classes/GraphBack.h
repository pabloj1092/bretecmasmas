//
//  GraphBack.h
//  moxos
//
//  Created by Francisco Molina Castro on 7/5/16.
//
//

#ifndef GraphBack_h
#define GraphBack_h


#include "cocos2d.h"

class GraphBack : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init() override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GraphBack);
    
    void update(float) override;
    
    void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent);
    
private:
    cocos2d::Sprite* amySprite;
    cocos2d::Sprite* bgnd;
    cocos2d::Sprite* grass1;
    cocos2d::Sprite* grass2;
    cocos2d::Sprite* grass3;


};


#endif /* GraphBack_h */
