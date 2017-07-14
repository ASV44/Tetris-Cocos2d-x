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

USING_NS_CC;

//namespace FigureStyle {
//    vector<cocos2d::Point> style1(cocos2d::Point block);
//}

class Figure
{
public:
    Figure(int type, cocos2d::Point block);
    vector<cocos2d::Point> getBlocks();
    int getBlockRow(int block);
    int getBlockColumn(int block);
    void moveDown();
    void reset(Size containerSize);
    bool isInside(Point block);
    void rotate(int direction);
    void showPosition();
    
private:
    int styleType;
    vector<cocos2d::Point> blocks;
    vector<cocos2d::Point> style1(cocos2d::Point block, int type);
    cocos2d::Point *pivot;
    
};

#endif /* Figure_h */
