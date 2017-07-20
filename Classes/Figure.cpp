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
        case 0:
            //horizontal line figure
            blocks =  {block, Point(block.x, block.y + 1),
                Point(block.x, block.y + 2), Point(block.x, block.y + 3),
                Point(block.x, block.y + 4)};
            pivot = &blocks[2];
            break;
        case 1:
            // L figure
            blocks =  {block, Point(block.x, block.y + 1),
                Point(block.x + 1, block.y), Point(block.x + 2, block.y)};
            pivot = &blocks[2];
            break;
        case 2:
            // T-like figure
            blocks =  {block, Point(block.x, block.y + 1),
                Point(block.x, block.y + 2), Point(block.x + 1, block.y + 1)};
            pivot = &blocks[1];
            break;
        case 3:
            // square figure
            blocks =  {block, Point(block.x, block.y + 1),
                Point(block.x + 1, block.y), Point(block.x + 1, block.y + 1)};
            pivot = NULL;
            break;
        case 4:
            //Z-like figure left
            blocks =  {block, Point(block.x, block.y + 1),
                Point(block.x + 1, block.y), Point(block.x + 1, block.y - 1)};
            pivot = &blocks[2];
            break;
        case 5:
            //Z-like figure right
            blocks =  {block, Point(block.x, block.y + 1),
                Point(block.x + 1, block.y + 1), Point(block.x + 1, block.y + 2)};
            pivot = &blocks[2];
            break;
        case 10:
            //Custom figure
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

bool Figure::moveDown(Container *container)
{
    bool reset = false;
    vector<Point> initialBlocks = blocks;
    
    for(int i = 0; i < blocks.size(); ++i) {
        if(blocks[i].x - 1 < container->getContainerSize().width &&
           !isInside(initialBlocks, Point(blocks[i].x - 1, blocks[i].y)) &&
           container->getContainerElements(blocks[i].x - 1, blocks[i].y)->getType() != DEFAULT_STYLE)
        {
            blocks = initialBlocks;
            reset  = true;
            break;
        }
        blocks[i].x --;
        if(blocks[i].x == 0 && !reset) {
            reset = true;
        }
    }
    
    if(reset) {
        return true;
    }
    else {
        return false;
    }
}

void Figure::reset(Size containerSize)
{
    
    blocks = style1(Point(containerSize.width,
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

bool Figure::isInside(vector<Point> blocks, Point block)
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

void Figure::rotate(int direction, Container *container)
{
    int delta_row, delta_column;
    int deltaRow, deltaColumn;
    int control = 0;
    
    vector<Point> initialBlocks = blocks;
    
    
    for(int i = 0; i < blocks.size(); i++) {
        
        if(&blocks[i] == pivot || pivot == NULL) {
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
        
        if(blocks[i].x < 0 || blocks[i].y < 0 || blocks[i].x >= container->getContainerSize().width
           || blocks[i].y >= container->getContainerSize().height ||
           (find(initialBlocks.begin(), initialBlocks.end(), blocks[i]) == initialBlocks.end() &&
            container->getContainerElements(blocks[i].x, blocks[i].y)->getType() == ACTIVE_STYLE))
        {
            blocks = initialBlocks;
            break;
        }
    }
}

void Figure::showPosition()
{
    for(int i = 0; i < blocks.size(); i++) {
         CCLOG("Element %d Row %f Columns %f \n", i, blocks[i].x, blocks[i].y);
    }
    CCLOG("\n");
}

void Figure::moveUp(Container *container)
{
    for(int i = 0; i < blocks.size(); ++i) {
        blocks[i].x ++;
    }
}

Point Figure::getBlock(int i)
{
    return blocks[i];
}

void Figure::setBlocks(vector<Point> blocks)
{
    this->blocks = blocks;
}

void Figure::moveLeft(Container *container)
{
    vector<Point> initialBlocks = blocks;
    showPosition();
    container->showActiveElements();
    for(int i = 0; i < blocks.size(); ++i) {
        CCLOG("IsInside element %d = %d",i, isInside(Point(blocks[i].x, blocks[i].y - 1)));
        if(blocks[i].y - 1 >= 0 && !isInside(Point(blocks[i].x, blocks[i].y - 1)) &&
           container->getContainerElements(blocks[i].x, blocks[i].y - 1)->getType() != DEFAULT_STYLE)
        {
            blocks = initialBlocks;
            break;
        }
        blocks[i].y --;
    }
}
