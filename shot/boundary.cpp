#include "boundary.h"

bool beforecls;



Vecbool boundary::isCollid(boundary& bound, int j, int k)
{
    Vecbool tmp;
    tmp.iscollid = false;
    tmp.collsitu = false;
    tmp.point = { 0,0 };

    float b1value1 = a * bound.Points[0].x + b * bound.Points[0].y + c;
    float b1value2 = a * bound.Points[1].x + b * bound.Points[1].y + c;
    float b2value1 = bound.a * Points[0].x + bound.b * Points[0].y + bound.c;
    float b2value2 = bound.a * Points[1].x + bound.b * Points[1].y + bound.c;

    int i = j * 2;
    int a = k * 2;

    if ((b1value1*b1value2 < 0) && (b2value1*b2value2 < 0)) {
        tmp.iscollid = true;

        if (b2value1 * bsaves[i] < 0) { 
            ps[j] = 0;
            tmp.collsitu = true;
           
            //std::cout << "i" << std::endl;
        }
        else if (b2value2 * bsaves[i + 1] < 0) { 
            ps[j] = 1;
            tmp.collsitu = true;
            
            //std::cout << "i" << std::endl;
        }
        else if (b1value1 * bound.bsaves[a] < 0) {
            bound.ps[k] = 0;
           
            
            //std::cout << "j0 : " << k << "," << j << std::endl;
        }
        else if (b1value2 * bound.bsaves[a + 1] < 0) {
            bound.ps[k] = 1;
            
            
            //std::cout << "j1 : " << k << "," << j << std::endl;
        }
        else {
            //std::cout << "o" << k << "," << j << std::endl;
            tmp.collsitu = beforecls; 
           
        }
        beforecls = tmp.collsitu;
        
    }else {
        bsaves[i] = b2value1;
        bsaves[i + 1] = b2value2;
        bound.bsaves[a] = b1value1;
        bound.bsaves[a + 1] = b1value2;
    }
     
    if (tmp.collsitu) { tmp.point = Points[ps[j]]; }
    else { tmp.point = bound.Points[bound.ps[k]]; }
    return tmp;
}

Vecbool isboundmeet(boundary bound1, boundary bound2)
{
    Vecbool tmp;
    tmp.iscollid = false;
    tmp.collsitu = false;
    tmp.point = { 0,0 };

    float b1value1 = bound1.a * bound2.Points[0].x + bound1.b * bound2.Points[0].y + bound1.c;
    float b1value2 = bound1.a * bound2.Points[1].x + bound1.b * bound2.Points[1].y + bound1.c;
    float b2value1 = bound2.a * bound1.Points[0].x + bound2.b * bound1.Points[0].y + bound2.c;
    float b2value2 = bound2.a * bound1.Points[1].x + bound2.b * bound1.Points[1].y + bound2.c;

    if ((b1value1 * b1value2 < 0) && (b2value1 * b2value2 < 0)) {
        tmp.iscollid = true;
        tmp.point.x = (b1value1 * bound2.Points[0].x - b1value2 * bound2.Points[1].x) / (b1value1 - b1value2);
        tmp.point.y = (b1value1 * bound2.Points[0].y - b1value2 * bound2.Points[1].y) / (b1value1 - b1value2);
    }

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

void boundary::removeMemory()
{
    delete[] bsaves;
    delete[] ps;
}

void boundary::movePos(Vector2 mPos)
{
    Points[0] = { Points[0].x + mPos.x,Points[0].y + mPos.y };
    Points[1] = { Points[1].x + mPos.x,Points[1].y + mPos.y };
    a = Points[1].y - Points[0].y;
    b = Points[0].x - Points[1].x;
    c = Points[1].x * Points[0].y - Points[0].x * Points[1].y;
}
