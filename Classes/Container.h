//
//  Container.h
//  TestProject
//
//  Created by Hackintosh on 7/6/17.
//
//

#ifndef Container_h
#define Container_h

#include "GridElement.h"

class Container : public cocos2d::Sprite
{
public:
    Container(cocos2d::Size matrixSize, cocos2d::Size shapeSize, cocos2d::Size cellSize);
    Container(float error);
    GridElement ***getContainerElements();
    GridElement *getContainerElements(int row, int column);
    cocos2d::Size getContainerSize();
    cocos2d::Size getCellSize();
    
private:
    GridElement ***elements;
    GridElement *redSquare;
    cocos2d::Size containerSize;
    cocos2d::Size cellSize;
};

#endif /* Container_h */
