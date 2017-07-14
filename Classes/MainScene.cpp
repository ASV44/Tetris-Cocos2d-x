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
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
//    Size matrixSize = Size(5,5);
//    
//    Size cellStep = Size(25,25);
//    
//    Size shapeSize = Size(15,15);

    //container = new Container(matrixSize, shapeSize, cellStep);
    
    gameState = ACTIVE;
    
    container = new Container(0.09);
    
    this->addChild(container);
    
    figures = new Figure(0, Point(container->getContainerSize().width - 1,
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
    
    foreground = DrawNode::create();
    Vec2 vertices[] =
    {
        Vec2(origin.x,origin.y + visibleSize.height),//Vec2(0,100),
        Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height),
        Vec2(origin.x + visibleSize.width,origin.y),
        origin
    };
    foreground->drawPolygon(vertices, 4, Color4F(0.5f,0.5f,0.5f,0.6f), 0, Color4F(0.2f,0.2f,0.2f,1));
    addChild(foreground);
    foreground->setVisible(false);
    
    auto label = Label::createWithTTF("Game Over", "fonts/good_time.ttf", 18);
    
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height / 2 + label->getContentSize().height));

    foreground->addChild(label);
    
    auto button = cocos2d::ui::Button::create("restart.png");
    
    
    button->setPosition(Vec2(origin.x + visibleSize.width / 2,
                             origin.y + visibleSize.height / 2 - button->getContentSize().height));
    
    button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                log("Restart Click");
                this->restart();
                break;
            default:
                break;
        }
    });
    
    foreground->addChild(button);
    
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
    int rendered = 0;
    
    time += delta;
    if(time > 0.3 && gameState == ACTIVE) {
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
                   container->getContainerElements(row - 1,column)->getType() != DEFAULT_STYLE)
                {
                    
                    colision = true;
                }
                
                if(row == 0) { bottomReached = true; }
                
                rendered ++;
            }
            
        }
        
        if(colision == true && rendered < figures->getBlocks().size())
        {
            gameState = GAME_OVER;
            gameOver();
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

void MainScene::gameOver()
{
    foreground->setVisible(true);
}

void MainScene::restart()
{
    Size containerSize;
    
    foreground->setVisible(false);
    gameState = ACTIVE;
    
    containerSize = container->getContainerSize();
    
    for(int i = 0; i < containerSize.width; ++i) {
        for(int j = 0; j < containerSize.height; ++j) {
            if(container->getContainerElements(i, j)->getType() != DEFAULT_STYLE) {
                container->getContainerElements(i, j)->setType(DEFAULT_STYLE);
            };
        }
    }
    
    figures->reset(container->getContainerSize());
}
