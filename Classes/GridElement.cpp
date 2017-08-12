//
//  GridElement.cpp
//  TestProject
//
//  Created by Hackintosh on 7/6/17.
//
//

#include "GridElement.h"



GridElement::GridElement(string name, Size size)
{
    this->initWithFile(name);
    this->size = size;
    this->setType(DEFAULT_STYLE);
}

void GridElement::setType(int type)
{
    CCLOG("Grid Element Type:%d", type);
    this->_type = type;
    
    switch (_type) {
        case DEFAULT_STYLE:
            this->setTexture("square.png");
            break;
            
        case ACTIVE_STYLE:
            this->setTexture("redSquare.png");
            break;
            
        default:
            break;
    }
    this->setContentSize(size);
}

int GridElement::getType()
{
    return this->_type;
}
