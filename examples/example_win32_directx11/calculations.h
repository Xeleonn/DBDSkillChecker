#include <iostream>
#include <cmath>
#include <vector>

struct Point;

struct RGBColor;

Point GetPxAtAngle(Point, float, float);

std::vector<Point> GetNPointsInCircle(Point, float, int);

static Point GetCenterOfArc(std::vector<Point>);

static RGBColor GetColorAtPos(int, int);

bool ColorExceedsValue(RGBColor, RGBColor );

int NormalizeVectorIdx(int, int);

static Point GetCenterOfArc(std::vector<Point>);
