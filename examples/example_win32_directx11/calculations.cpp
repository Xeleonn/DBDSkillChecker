#include <d3d11.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cmath>
#include <vector>
#include <list>
#include <cstdint>

struct Point
{
    int a;
    int b;
};

struct RGBColor
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

// uses <cmath>
Point GetPxAtAngle(Point origin, float radius, float angle)
{
    float f_AngleRadians = angle * 3.14159 / 180.0f;
    Point p_NewPoint;
    p_NewPoint.a = origin.a + (radius * std::sin(f_AngleRadians));
    p_NewPoint.b = origin.b + (radius * std::cos(f_AngleRadians));

    return p_NewPoint;
}

// uses <vector>
std::vector<Point> GetNPointsInCircle(Point origin, float radius, int n)
{
    std::vector<Point> v_Points;

    for (int i = 0; i < n; i++)
    {
        float f_Angle = (360.0f / n) * i;
        v_Points.push_back(GetPxAtAngle(origin, radius, f_Angle));
    }

    return v_Points;
}

static RGBColor GetColorAtPos(int x, int y)
{
    static HDC dc = GetDC(NULL);
    COLORREF c_Pixel = GetPixel(dc, x, y);

    return RGBColor{ (uint8_t)GetRValue(c_Pixel), (uint8_t)GetGValue(c_Pixel), (uint8_t)GetBValue(c_Pixel) };
}

bool ColorExceedsValue(RGBColor a, RGBColor b)
{
    return ((a.r > b.r) && (a.g > b.g) && (a.b > b.b));
}

int NormalizeVectorIdx(int n, int idx)
{
    if ((idx > 0) && (idx < n)) return idx;
    if (idx < 0) return (n + idx);
    else return (idx - n);
}

static Point GetCenterOfArc(std::vector<Point> Points)
{
    // find target points who have two appropriate neighbors
    std::vector<Point> v_TargetPoints;
    for (int i = 0; i < Points.size(); i++)
    {
        RGBColor c_PColor = GetColorAtPos(Points.at(i).a, Points.at(i).b);
        if (ColorExceedsValue(c_PColor, RGBColor{ 250, 250, 250 }))
        {
            // get idx - 1 neighbor color
            RGBColor c_N1Color = GetColorAtPos(Points.at(NormalizeVectorIdx(Points.size(), i - 1)).a, Points.at(NormalizeVectorIdx(Points.size(), i - 1)).b);
            // get idx + 1 neighbor color
            RGBColor c_N2Color = GetColorAtPos(Points.at(NormalizeVectorIdx(Points.size(), i + 1)).a, Points.at(NormalizeVectorIdx(Points.size(), i + 1)).b);
            if (ColorExceedsValue(c_N1Color, RGBColor{ 250, 250, 250 }) && ColorExceedsValue(c_N2Color, RGBColor{ 250, 250, 250 }))
            {
                v_TargetPoints.push_back(Points.at(i));
            }
        }
    }

    // find the most suitable point to use
    Point p_CenterPoint{ 0, 0 };
    if (v_TargetPoints.size()) p_CenterPoint = v_TargetPoints.at(v_TargetPoints.size() / 2);

    return p_CenterPoint;
}
