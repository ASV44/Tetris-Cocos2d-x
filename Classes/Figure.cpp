//
//  Figure.cpp
//  TestProject
//
//  Created by Hackintosh on 7/12/17.
//
//

#include "Figure.h"

Figure::Figure(int type, Point block)
{
    styleType = type;
    blocks = style1(block, type);
}

vector<cocos2d::Point> Figure::style1(Point block, int type)
{
    vector<cocos2d::Point> blocks;
    
    switch(type)
    {
        case 1:
            blocks =  {block, Point(block.x, block.y + 1),
                Point(block.x + 1, block.y), Point(block.x + 2, block.y)};
            pivot = &blocks[2];
            break;
        case 2:
            blocks =  {block, Point(block.x, block.y + 1),
                Point(block.x - 1, block.y + 1), Point(block.x - 2, block.y + 1),
                Point(block.x - 2, block.y + 2), Point(block.x - 2, block.y + 3),
                Point(block.x + 1, block.y + 1), Point(block.x + 2, block.y + 1),
                Point(block.x + 2, block.y + 2), Point(block.x + 2, block.y + 3),
                Point(block.x + 1, block.y + 3), Point(block.x, block.y + 3)};
            pivot = &blocks[2];
            break;
        default:
            pivot = &blocks[0];
            blocks = {block};
            break;
            
    }
    
    return blocks;
}

vector<Point> Figure::getBlocks()
{
    return blocks;
}

int Figure::getBlockRow(int block) {
    return int(blocks[block].x);
}

int Figure::getBlockColumn(int block) {
    return int(blocks[block].y);
}

void Figure::moveDown()
{
    for(int i = 0; i < blocks.size(); ++i) {
        blocks[i].x --;
    }
}

void Figure::reset(Size containerSize)
{
    
    blocks = style1(Point(containerSize.width - 1,
                    int(containerSize.height / 2)),
                    styleType);
}

bool Figure::isInside(Point block)
{
    bool isInside = false;
    
    if(find(blocks.begin(), blocks.end(), block) != blocks.end()) {
        isInside = true;
    }
    else
    {
        isInside = false;
    }

    return isInside;
    
}

void Figure::rotate(int direction)
{
    int delta_row, delta_column;
    int deltaRow, deltaColumn;
    int control = 0;
    
    for(int i = 0; i < blocks.size(); i++) {
        
        if(&blocks[i] == pivot) {
            continue;
        }
        
        delta_row = blocks[i].x - pivot->x;
        delta_column = blocks[i].y - pivot->y;
        
        control = (delta_row == 0 ? control = 1 : control = 0);
        if(control == 0) {
            control = (delta_column == 0 ? control = 2 : control = 0);
        }
        
        switch(control)
        {
            case 0:
                if(delta_row > 0 && delta_column > 0) {
                    deltaRow = -(abs(delta_row) + abs(delta_column));
                    deltaColumn = abs(delta_row) - abs(delta_column);
                }
                else if(delta_row > 0 && delta_column < 0) {
                    deltaRow = -(abs(delta_row) - abs(delta_column));
                    deltaColumn = abs(delta_row) + abs(delta_column);
                }
                else if(delta_row < 0 && delta_column < 0) {
                    deltaRow = abs(delta_row) + abs(delta_column);
                    deltaColumn = -(abs(delta_row) - abs(delta_column));
                }
                else if(delta_row < 0 && delta_column > 0) {
                    deltaRow = abs(delta_row) - abs(delta_column);
                    deltaColumn = -(abs(delta_row) + abs(delta_column));
                }
                break;
            case 1:
                deltaColumn = deltaRow = -delta_column;
                break;
            case 2:
                deltaColumn = delta_row;
                deltaRow = -delta_row;
                break;
        }
        
        blocks[i].x += deltaRow;
        blocks[i].y += deltaColumn;
        

    }
}

void Figure::showPosition()
{
    for(int i = 0; i < blocks.size(); i++) {
         CCLOG("Element %d Row %f Columns %f \n", i, blocks[i].x, blocks[i].y);
    }
    CCLOG("\n");
}
