#include "area_calculation.hpp"

using namespace std;

/*
    The following code is licensed under CC BY-SA 3.0 https://creativecommons.org/licenses/by-sa/3.0/
    from *the swine* on StackOverflow https://stackoverflow.com/a/32698993

    Changes include:
     * Reformatting
     * Removing asserts
     * Removal of default arguments as those stay in .hpp
*/

float section(float h, float r) // returns the positive root of intersection of line y = h with circle centered at the origin and radius r
{
    // assert(r >= 0);                           // assume r is positive, leads to some simplifications in the formula below (can factor out r from the square root)
    return (h < r) ? sqrt(r * r - h * h) : 0; // http://www.wolframalpha.com/input/?i=r+*+sin%28acos%28x+%2F+r%29%29+%3D+h
}

float g(float x, float h, float r) // indefinite integral of circle segment
{
    return .5f * (sqrt(1 - x * x / (r * r)) * x * r + r * r * asin(x / r) - 2 * h * x); // http://www.wolframalpha.com/input/?i=r+*+sin%28acos%28x+%2F+r%29%29+-+h
}

float area(float x0, float x1, float h, float r) // area of intersection of an infinitely tall box with left edge at x0, right edge at x1, bottom edge at h and top edge at infinity, with circle centered at the origin with radius r
{
    if (x0 > x1)
        swap(x0, x1); // this must be sorted otherwise we get negative area
    float s = section(h, r);
    return g(max(-s, min(s, x1)), h, r) - g(max(-s, min(s, x0)), h, r); // integrate the area
}

float area(float x0, float x1, float y0, float y1, float r) // area of the intersection of a finite box with a circle centered at the origin with radius r
{
    if (y0 > y1)
        swap(y0, y1); // this will simplify the reasoning
    if (y0 < 0)
    {
        if (y1 < 0)
            return area(x0, x1, -y0, -y1, r); // the box is completely under, just flip it above and try again
        else
            return area(x0, x1, 0, -y0, r) + area(x0, x1, 0, y1, r); // the box is both above and below, divide it to two boxes and go again
    }
    else
    {
        // assert(y1 >= 0);                                  // y0 >= 0, which means that y1 >= 0 also (y1 >= y0) because of the swap at the beginning
        return area(x0, x1, y0, r) - area(x0, x1, y1, r); // area of the lower box minus area of the higher box
    }
}

float area(float x0, float x1, float y0, float y1, float cx, float cy, float r) // area of the intersection of a general box with a general circle
{
    x0 -= cx;
    x1 -= cx;
    y0 -= cy;
    y1 -= cy;
    // get rid of the circle center

    return area(x0, x1, y0, y1, r);
}

/*
    End of code licensed from *the swine*
*/