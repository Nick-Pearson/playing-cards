#ifndef RECT_H
#define RECT_H

struct Rect
{
public:
  Rect(float x = 0.0f, float y = 0.0f, float width = 1.0f, float height = 1.0f) :
    x1(x), y1(y), x2(x + width), y2(y + height)
  {}

  float x1, y1, x2, y2;

  bool Contains(float x, float y) const
  {
    return (x >= x1 && x <= x2) &&
            (y >= y1 && y <= y2);
  }
};

#endif
