#ifndef GRAPHLIB_H
#define GRAPHLIB_H

#include <cstdint>
#include <cstdio>
#include <vector>
#include <stdexcept>

using std::vector;
using std::invalid_argument;

typedef double glNumber;

/////////////////////////////////////////////

/* Not an actual shape, used for vertices */
class GLPoint
{
public:
  glNumber X;
  glNumber Y;

  GLPoint():
    X(0), Y(0)
  { }
  GLPoint(glNumber x, glNumber y) :
    X(x), Y(y)
  { }
  GLPoint(const GLPoint& rhs) :
    X(rhs.X), Y(rhs.Y)
  { }

  GLPoint& operator=(const GLPoint& rhs)
  {
    X = rhs.X;
    Y = rhs.Y;
    return *this;
  }
};

/////////////////////////////////////////////

class GLShape
{
public:
  explicit GLShape() { }

  /* We want to have copy constructor, but cannot have unused parameters */
  GLShape(const GLShape& rhs)
  {
    (void) rhs;   
  }

  virtual ~GLShape() { }

  /* We want to have assignment operator, but cannot have unused parameters */
  GLShape& operator=(const GLShape& rhs)
  {
    (void) rhs;
    return *this;
  }

  virtual void draw() const
  {

  }

  virtual void printInfo() const
  {
    printf("GLShape\n");
  }
};

/////////////////////////////////////////////

template <uint32_t vertexCount>
class GLPolygon : public GLShape
{
private:
  GLPoint vertices[vertexCount];

public:
  explicit GLPolygon() :
    GLShape()
  { }

  GLPolygon(const GLPolygon<vertexCount>& rhs) :
    GLShape()
  {
    for (uint32_t i = 0; i < vertexCount; ++i)
      vertices[i] = rhs.vertices[i];
  }

  GLPolygon(vector<GLPoint> verticesArg) :
    GLShape()
  {
    if (verticesArg.size() != vertexCount)
      throw invalid_argument("Bad vertex number!");
    for (uint32_t i = 0; i < vertexCount; ++i)
      vertices[i] = verticesArg[i];
  }

  ~GLPolygon() { }

  GLPolygon<vertexCount>& operator=(const GLPolygon<vertexCount>& rhs)
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
    printf("GLPolygon with %d vertices:\n", vertexCount);
    for (auto vertex: vertices)
      printf("\tGLPoint(%.3lf, %.3lf)\n", vertex.X, vertex.Y);
  }
};

/////////////////////////////////////////////

class GLCircle : public GLShape
{
private:
  GLPoint center;
  glNumber radius;
public:
  explicit GLCircle():
    GLShape(), radius(0)
  { }

  GLCircle(const GLCircle& rhs) :
    GLShape(), center(rhs.center)
  {
    radius = rhs.radius;
  }

  GLCircle(GLPoint centerArg, glNumber radiusArg):
    GLShape(), center(centerArg), radius(radiusArg)
  { }

  ~GLCircle() { }

  GLCircle& operator=(const GLCircle rhs)
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
    printf("GLCircle with radius = %.3lf and center in:\n", radius);
    printf("\tGLPoint(%.3lf, %.3lf)\n", center.X, center.Y);
  }
};

/////////////////////////////////////////////

typedef GLPolygon<3> GLTriangle;
typedef GLPolygon<4> GLQuadrangle;

#endif