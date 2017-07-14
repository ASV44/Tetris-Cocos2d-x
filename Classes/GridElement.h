//
//  GridElememnt.h
//  TestProject
//
//  Created by Hackintosh on 7/6/17.
//
//

#ifndef GridElememnt_h
#define GridElememnt_h

#include "CellStyle.h"
#include <string>

using namespace std;

using namespace CellStyle;

class GridElement : public cocos2d::Sprite
{
public:
    GridElement(string name);
    void setType(int type);
    int getType();
    
private:
    int _type;
};

#endif /* GridElememnt_h */
