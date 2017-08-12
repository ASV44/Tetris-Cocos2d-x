//
//  GridElememnt.h
//  TestProject
//
//  Created by Hackintosh on 7/6/17.
//
//

#ifndef GridElememnt_h
#define GridElememnt_h

#include <string>
#include "cocos2d.h"

using namespace std;

USING_NS_CC;

class GridElement : public cocos2d::Sprite
{
public:
    GridElement(string name, Size size);
    void setType(int type);
    int getType();
    enum cellStyle {DEFAULT_STYLE, ACTIVE_STYLE};

private:
    int _type;
    Size size;
};

#endif /* GridElememnt_h */
