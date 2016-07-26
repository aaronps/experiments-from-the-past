/* 
 * File:   main.cpp
 * Author: krom
 *
 * Created on January 12, 2013, 9:54 PM
 */

//#include <cstdlib>
#include <iostream>

using namespace std;

class PSRect
{
public:
    int x;
    int y;
    int width;
    int height;
    
    PSRect(int x, int y, int w, int h) : x(x), y(y), width(w), height(h) {}
    
    void log()
    {
        cout << "PSRect from " << x << ',' << y
             << " to " << (x+width) << ',' << (y+height)
             << " size " << width << 'x' << height
             << " area " << area()
             <<  endl;
    }
    
    int getWidth()  { return width; }
    int getHeight() { return height; }
    
    bool xcontains(int x, int y)
    {
        return ( x >= this->x ) && ( x <= (this->x+width) )
            && ( y >= this->y ) && ( y <= (this->y+height) );
    }
    
    bool contains(int x, int y)
    {
        int xp = x - this->x ;
        int yp = y - this->y ;
        
        cout << "after it " << xp << "," << yp << endl;
        
        return ( x >= this->x ) && ( x <= (this->x+width) )
            && ( y >= this->y ) && ( y <= (this->y+height) );
    }
    
    void translate(int x, int y)
    {
        this->x += x;
        this->y += y;
    }
    
    void resize(int w, int h)
    {
        width = w;
        height = h;
    }
    
    int area()
    {
        return width * height;
    }
    
};

class MMRect
{
public:
    int min_x;
    int min_y;
    int max_x;
    int max_y;
    
    MMRect(int x1, int y1, int x2, int y2) : min_x(x1), min_y(y1), max_x(x2), max_y(y2) {}
    
    void log()
    {
        cout << "MMRect from " << min_x << ',' << min_y
             << " to " << max_x << ',' << max_y
             << " size " << getWidth() << 'x' << getHeight()
             << " area " << area()
             <<  endl;
    }
    
    int getWidth()  { return max_x - min_x; }
    int getHeight() { return max_y - min_y; }
    
    bool contains(int x, int y)
    {
        return ( x >= min_x ) && ( x <= max_x )
            && ( y >= min_y ) && ( y <= max_y );
    }
    
    void translate(int x, int y)
    {
        min_x += x;
        max_x += x;
        min_y += y;
        max_y += y;
    }
    
    void resize(int w, int h)
    {
        max_x = min_x + w;
        max_y = min_y + h;
    }
    
    int area()
    {
        return getWidth() * getHeight();
    }
    
};

/*
 * 
 */
int main(int argc, char** argv)
{
    cout << "Hello\n" << endl;
    
    PSRect p(1,1,5,5);
    MMRect m(1,1,6,6);
    
    p.log();
    m.log();
    
#define TESTPOS(x,y,v) cout << #v " contains " #x "," #y " " << (v.contains(x,y)?"true":"false") << "\n"
    
    TESTPOS(0,0,p);
    TESTPOS(0,1,p);
    TESTPOS(1,1,p);
    TESTPOS(5,5,p);
    TESTPOS(5,6,p);
    TESTPOS(6,5,p);
    TESTPOS(6,6,p);
    TESTPOS(6,7,p);
    TESTPOS(7,6,p);
    TESTPOS(7,7,p);
    cout << "--------\n";
    TESTPOS(0,0,m);
    TESTPOS(0,1,m);
    TESTPOS(1,1,m);
    TESTPOS(5,5,m);
    TESTPOS(5,6,m);
    TESTPOS(6,5,m);
    TESTPOS(6,6,m);
    TESTPOS(6,7,m);
    TESTPOS(7,6,m);
    TESTPOS(7,7,m);
    
    
    
    
    
    return 0;
}

