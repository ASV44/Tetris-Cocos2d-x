//
//  MainScene.h
//  TestProject
//
//  Created by Hackintosh on 7/6/17.
//
//

#ifndef MainScene_h
#define MainScene_h

#include "Container.h"
#include "cocos2d.h"

#include "Figure.h"

#include "ui/CocosGUI.h"



class MainScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void update(float delta);
    
    void gameOver();
    
    void restart();
    
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
private:
    Vec2 origin;
    Size visibleSize;
    Container *container;
    float time;
    Figure *figure;
    EventListenerTouchOneByOne *listener;
    DrawNode *foreground;
    enum states { ACTIVE, GAME_OVER, PAUSE };
    int gameState;
    float deltaTime;
};

#endif /* MainScene_h */
