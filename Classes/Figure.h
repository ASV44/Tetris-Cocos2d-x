//
//  Figure.hpp
//  TestProject
//
//  Created by Hackintosh on 7/12/17.
//
//

#ifndef Figure_h
#define Figure_h

using namespace std;

#include <vector>
#include <ctime>
#include "Container.h"

USING_NS_CC;

//namespace FigureStyle {
//    vector<cocos2d::Point> style1(cocos2d::Point block);
//}

class Figure
{
public:
    Figure(int type, cocos2d::Point block);
    Figure(Point block);
    vector<cocos2d::Point> getBlocks();
    Point getBlock(int i);
    int getBlockRow(int block);
    int getBlockColumn(int block);
    bool moveDown(Container *container);
    void moveUp(Container *container);
    void reset(Size containerSize);
    bool isInside(Point block);
    void rotate(int direction, Container *container);
    void showPosition();
    void setBlocks(vector<Point> blocks);
    void moveLeft(Container *container);
    void moveRight(Container *container);
    bool isInside(vector<Point> blocks, Point block);
    int getRandomStyle();
    void changeToRandomFigure();
    
private:
    int styleType;
    vector<cocos2d::Point> blocks;
    vector<cocos2d::Point> style1(cocos2d::Point block, int type);
    cocos2d::Point *pivot;
    Point startingPoint;
    
};

#endif /* Figure_h */
