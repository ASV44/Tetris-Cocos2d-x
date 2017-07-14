//
//  MainScene.cpp
//  TestProject
//
//  Created by Hackintosh on 7/6/17.
//
//

#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include <string>




USING_NS_CC;

Scene* MainScene::createScene()
{
    return MainScene::create();
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
//    Size matrixSize = Size(5,5);
//    
//    Size cellStep = Size(25,25);
//    
//    Size shapeSize = Size(15,15);

    //container = new Container(matrixSize, shapeSize, cellStep);
    
    container = new Container(0.09);
    
    this->addChild(container);
    
    figures = new Figure(2, Point(container->getContainerSize().width - 1,
                                     int(container->getContainerSize().height / 2)));
    
    this->scheduleUpdate();
    
    listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = [](Touch* touch, Event* event){
        // your code
        return true; // if you are consuming it
    };
    
    listener->onTouchEnded = [=](Touch* touch, Event* event){
        
        figures->rotate(0);
        
        return true;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}


void MainScene::update(float delta) {
    static float time = 0;
//    static int row = container->getContainerSize().width - 1;
//    static int column = int(container->getContainerSize().height) / 2;
    int row, column;
    bool colision = false;
    static vector<Point> toClear;
    static bool bottomReached = false;
    
    time += delta;
    if(time > 0.3) {
        for(int i = 0; i < toClear.size(); ++i) {
            if( toClear[i].x <= container->getContainerSize().width - 1) {
                container->getContainerElements(toClear[i].x,toClear[i].y)->setType(DEFAULT_STYLE);
                container->getContainerElements(toClear[i].x,toClear[i].y)->setContentSize(container->getCellSize());
            }
        }
        
        for(int i = 0; i < figures->getBlocks().size(); ++i)
        {
            row = figures->getBlockRow(i);
            column = figures->getBlockColumn(i);
//            if( row < container->getContainerSize().width - 1) {
////                container->getContainerElements(row + 1,column)->setTexture(DEFAULT_STYLE);
//                container->getContainerElements(row + 1,column)->setType(DEFAULT_STYLE);
//                container->getContainerElements(row + 1,column)->setContentSize(container->getCellSize());
//                
//            }
            if( row <= container->getContainerSize().width - 1 ) {
                container->getContainerElements(row,column)->setType(ACTIVE_STYLE);
                container->getContainerElements(row,column)->setContentSize(container->getCellSize());
                
                if(row > 0 && !figures->isInside(Point(row - 1, column)) &&
                   container->getContainerElements(row - 1,column)->getType() != 0)
                {
                    
                    colision = true;
                }
                
                if(row == 0) { bottomReached = true; }
            
            }
        }
        time = 0;
        
        if(bottomReached == true || colision == true) {
            figures->reset(container->getContainerSize());
            toClear.clear();
            bottomReached = false;
            colision = false;
        }
        else {
            toClear = figures->getBlocks();
            figures->moveDown();
        }

    }
    //CCLOG("Time %f", time);
}
