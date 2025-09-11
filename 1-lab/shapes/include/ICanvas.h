#ifndef ICANVAS_H
#define ICANVAS_H
#include <string>

struct ICanvas
{
    double MoveTO(double x, double y);
    double LineTo(double x, double y);
    void SetColor(std::string color);
    void DrawEllips();
    void DrawText();

    virtual ~ICanvas(){};

};
#endif //ICANVAS_H
