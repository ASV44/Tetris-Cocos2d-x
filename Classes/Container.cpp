//
//  Container.cpp
//  TestProject
//
//  Created by Hackintosh on 7/6/17.
//
//

#include "Container.h"
#include <ctime>

USING_NS_CC;

Container::Container(Size matrixSize, Size shapeSize, Size cellSize)
{
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    int rows = int(matrixSize.width);
    int columns = int(matrixSize.height);
    
    srand(time( 0 ));
    
    elements = new GridElement**[rows];
    
    
    for(int i = 0; i < rows; ++i) {
        elements[i] = new GridElement*[columns];
        for (int j = 0; j < columns; ++j) {
            elements[i][j] = new GridElement(std::to_string( 1 + rand() % 3) + ".png", shapeSize);
            //elements[i][j] = new GridElement("square.png");
            elements[i][j]->setPosition(Vec2(j * cellSize.width, i * cellSize.height));//(j + 1) * 10, i * 10));
            elements[i][j]->setContentSize(shapeSize);
            elements[i][j]->setAnchorPoint(Point(0,0));
            this->addChild(elements[i][j], 1);
        }
    }
    
    this->setPosition(origin.x + (visibleSize.width - ((columns - 1) * cellSize.width + shapeSize.width)) / 2,
                      origin.y + (visibleSize.height - ((rows - 1) * cellSize.height + shapeSize.height)) / 2);
    
    //this->setPosition(Vec2(origin.x, origin.y));
    
}

Container::Container(float error)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
//    float verticalDelay, horizontalDelay;
    int columns, rows;
    float width, height, tempRows;
    
//    verticalDelay = (visibleSize.width / int(visibleSize.width / shapeSize.width)) - shapeSize.width;
//    horizontalDelay = (visibleSize.height / int(visibleSize.height / shapeSize.height)) - shapeSize.height;
//    
//    if(verticalDelay < horizontalDelay) {
//        colomns = int(visibleSize.width / shapeSize.width);
//        shapeSize
//    }
    columns = 9;
    while(1) {
        width = visibleSize.width / columns;
        tempRows = visibleSize.height / width;
        if(tempRows - int(tempRows) < error) {
            rows = int(tempRows);
            break;
        }
        columns++;
    }
    
    containerSize = Size(rows, columns);
    
    elements = new GridElement**[rows];
    
    height = width;
    
    cellSize = Size(width,height);
    
    for(int i = 0; i < rows; ++i) {
        elements[i] = new GridElement*[columns];
        for (int j = 0; j < columns; ++j) {
            elements[i][j] = new GridElement("square.png", cellSize);
            elements[i][j]->setPosition(Vec2(j * width, i * height));//(j + 1) * 10, i * 10));
            elements[i][j]->setAnchorPoint(Point(0,0));
            this->addChild(elements[i][j], 1);
        }
    }

    this->setPosition(Vec2(origin.x, origin.y));
    
//    redSquare = new GridElement("redSquare.png");
//    redSquare->setAnchorPoint(Point(0,0));
//    redSquare->setContentSize(newSize);
//    redSquare->setPosition(Vec2(columns / 2 * width, (rows - 1) * height));
    
    //this->addChild(redSquare,2);

}

GridElement*** Container::getContainerElements() {
    return this->elements;
}

GridElement* Container::getContainerElements(int row, int column) {
    return this->elements[row][column];
}

Size Container::getContainerSize()
{
    return this->containerSize;
}

Size Container::getCellSize()
{
    return cellSize;
}

void Container::clearElements(vector<Point> toClear)
{
    int x, y;
    
    for(int i = 0; i < toClear.size(); ++i) {
        x = int(toClear[i].x);
        y = int(toClear[i].y);
        if( x <= containerSize.width - 1) {
            elements[x][y]->setType(GridElement::DEFAULT_STYLE);
        }
    }
}

void Container::showActiveElements()
{
    for(int i = 0; i < containerSize.width; ++i) {
        for(int j = 0; j < containerSize.height; ++j) {
            if(elements[i][j]->getType() == GridElement::ACTIVE_STYLE) {
                CCLOG("Element %d %d style Active",i,j);
            }
        }
    }
}

void Container::checkFirstRow()
{
    int actives = 0;
    
    for(int i = 0; i < containerSize.width; i++) {
        actives = 0;
        for(int j = 0; j < containerSize.height; j++) {
            if(elements[i][j]->getType() == GridElement::ACTIVE_STYLE) {
                actives ++;
            }
            else {
                break;
            }
        }
        if(actives == containerSize.height) {
            moveActivesDown(i);
        }
    }
}

void Container::moveActivesDown(int startingRow)
{
    for(int i = startingRow; i < containerSize.width; ++i) {
        for(int k = 0; k < containerSize.height; ++k) {
            if(elements[i][k]->getType() != GridElement::DEFAULT_STYLE) {
                elements[i][k]->setType(GridElement::DEFAULT_STYLE);
                if(i != startingRow) {
                    elements[i - 1][k]->setType(GridElement::ACTIVE_STYLE);
                }
            }
        }
    }
}
