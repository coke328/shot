#include "boundary.h"

vecbool boundary::isCollid(boundary bound, int j)
{
    vecbool tmp;
    tmp.iscollid = false;
    tmp.point = { 0,0 };
    
    float b1value1 = a * bound.Points[0].x + b * bound.Points[0].y + c;
    float b1value2 = a * bound.Points[1].x + b * bound.Points[1].y + c;
    float b2value1 = bound.a * Points[0].x + bound.b * Points[0].y + bound.c;
    float b2value2 = bound.a * Points[1].x + bound.b * Points[1].y + bound.c;

    int i = j * 2;

    if ((((b1value1 > 0) && (b1value2 < 0)) || ((b1value1 < 0) && (b1value2 > 0))) && (((b2value1 > 0) && (b2value2 < 0)) || ((b2value1 < 0) && (b2value2 > 0)))) {
        tmp.iscollid = true;
        std::cout << bsaves[i] << "," << bsaves[i + 1] << std::endl;
        if (((b2value1 > 0) && (bsaves[i] < 0)) || ((b2value1 < 0) && (bsaves[i] > 0))) { 
            //tmp.point = Points[0]; 
            p = 0;
            std::cout << 0 << std::endl; 
        }
        if (((b2value2 > 0) && (bsaves[i + 1] < 0)) || ((b2value2 < 0) && (bsaves[i + 1] > 0))) { 
            //tmp.point = Points[1]; 
            p = 1;
            std::cout << 1 << std::endl; 
        }
        //std::cout << tmp.point.x << "," << tmp.point.y << std::endl;
        
    }
    tmp.point = Points[p];
    bsaves[i] = b2value1;
    bsaves[i+1] = b2value2;
    return tmp;
}

Vector2 boundmeet(boundary bound1, boundary bound)
{
    Vector2 tmp;
    float b1value1 = bound1.a * bound.Points[0].x + bound1.b * bound.Points[0].y + bound1.c;
    float b1value2 = bound1.a * bound.Points[1].x + bound1.b * bound.Points[1].y + bound1.c;
    tmp.x = (b1value1 * bound.Points[0].x - b1value2 * bound.Points[1].x) / (b1value1 - b1value2);
    tmp.y = (b1value1 * bound.Points[0].y - b1value2 * bound.Points[1].y) / (b1value1 - b1value2);
    return tmp;
}

boundary::boundary()
{
    Points[0] = { 0,0 };
    Points[1] = { 0,0 };
    isStatic = 1;
    a = 0;
    b = 0;
    c = 0;
}

boundary::boundary(float x1, float y1, float x2, float y2, bool st) {
    Points[0] = { x1,y1 };
    Points[1] = { x2,y2 };
    isStatic = st;
    a = y2 - y1;
    b = x1 - x2;
    c = x2 * y1 - x1 * y2;
}

void boundary::boundaryInit(float x1, float y1, float x2, float y2, bool st)
{
    Points[0] = { x1,y1 };
    Points[1] = { x2,y2 };
    isStatic = st;
    a = y2 - y1;
    b = x1 - x2;
    c = x2 * y1 - x1 * y2;
}