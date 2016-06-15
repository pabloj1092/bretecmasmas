//
//  GameOverScene.hpp
//  moxos
//
//  Created by Francisco Molina Castro on 11/6/16.
//
//


#ifndef GameOverScene_h
#define GameOverScene_h

#include "cocos2d.h"

class GameOverLayer : public cocos2d::CCLayerColor
{
public:
    GameOverLayer():_label(NULL) {};
    virtual ~GameOverLayer();
    bool init();
    CREATEFUNC(GameOverLayer);
    
    void gameOverDone();
    
    CC_SYNTHESIZE_READONLY(cocos2d::CCLabelTTF*, _label, Label);
    
};

class GameOverScene : public cocos2d::CCScene
{
public:
    GameOverScene():_layer(NULL) {};
    ~GameOverScene();
    bool init();
    CREATEFUNC(GameOverScene);
    
    CC_SYNTHESIZE_READONLY(GameOverLayer*, _layer, Layer);
    
};

#endif // GameOverScene_h