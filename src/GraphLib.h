#ifndef GRAPHLIB_H
#define GRAPHLIB_H

#include <cstdint>
#include <cstdio>
#include <vector>
#include <stdexcept>

using std::vector;
using std::invalid_argument;

typedef double ipNumber;

/////////////////////////////////////////////

/* Not an actual shape, used for vertices */
class IPPoint
{
public:
  ipNumber X;
  ipNumber Y;

  IPPoint():
    X(0), Y(0)
  { }
  IPPoint(ipNumber x, ipNumber y) :
    X(x), Y(y)
  { }
  IPPoint(const IPPoint& rhs) :
    X(rhs.X), Y(rhs.Y)
  { }

  IPPoint& operator=(const IPPoint& rhs)
  {
    X = rhs.X;
    Y = rhs.Y;
    return *this;
  }
};

/////////////////////////////////////////////

class IPShape
{
public:
  explicit IPShape() { }

  /* We want to have copy constructor, but cannot have unused parameters */
  IPShape(const IPShape& rhs)
  {
    (void) rhs;   
  }

  virtual ~IPShape() { }

  /* We want to have assignment operator, but cannot have unused parameters */
  IPShape& operator=(const IPShape& rhs)
  {
    (void) rhs;
    return *this;
  }

  virtual void draw() const
  {
    /* Do nothing */
  }

  virtual void printInfo() const
  {
    printf("IPShape\n");
  }
};

/////////////////////////////////////////////

template <uint32_t vertexCount>
class IPPolygon : public IPShape
{
private:
  IPPoint vertices[vertexCount];

public:
  explicit IPPolygon() :
    IPShape()
  { }

  IPPolygon(const IPPolygon<vertexCount>& rhs) :
    IPShape()
  {
    for (uint32_t i = 0; i < vertexCount; ++i)
      vertices[i] = rhs.vertices[i];
  }

  IPPolygon(vector<IPPoint> verticesArg) :
    IPShape()
  {
    if (verticesArg.size() != vertexCount)
      throw invalid_argument("Bad vertex number!");
    for (uint32_t i = 0; i < vertexCount; ++i)
      vertices[i] = verticesArg[i];
  }

  ~IPPolygon() { }

  IPPolygon<vertexCount>& operator=(const IPPolygon<vertexCount>& rhs)
  {
    for (uint32_t i = 0; i < vertexCount; ++i)
      vertices[i] = rhs.vertices[i];
    return *this;
  }

  void draw() const override
  {
  }

  void printInfo() const override
  {
    printf("IPPolygon with %d vertices:\n", vertexCount);
    for (auto vertex: vertices)
      printf("\tIPPoint(%.3lf, %.3lf)\n", vertex.X, vertex.Y);
  }
};

/////////////////////////////////////////////

class IPCircle : public IPShape
{
private:
  IPPoint center;
  ipNumber radius;
public:
  explicit IPCircle():
    IPShape(), radius(0)
  { }

  IPCircle(const IPCircle& rhs) :
    IPShape(), center(rhs.center)
  {
    radius = rhs.radius;
  }

  IPCircle(IPPoint centerArg, ipNumber radiusArg):
    IPShape(), center(centerArg), radius(radiusArg)
  { }

  ~IPCircle() { }

  IPCircle& operator=(const IPCircle rhs)
  {
    radius = rhs.radius;
    center = rhs.center;
    return *this;
  }

  void draw() const override
  {

  }

  void printInfo() const override
  {
    printf("IPCircle with radius = %.3lf and center in:\n", radius);
    printf("\tIPPoint(%.3lf, %.3lf)\n", center.X, center.Y);
  }
};

/////////////////////////////////////////////

typedef IPPolygon<3> IPTriangle;
typedef IPPolygon<4> IPQuadrangle;

#endif