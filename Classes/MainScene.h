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



class MainScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void update(float delta);
    
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
private:
    Container *container;
    float time;
    Figure *figures;
    EventListenerTouchOneByOne *listener;
};

#endif /* MainScene_h */
