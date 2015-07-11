#ifndef GRAPHLIB_H
#define GRAPHLIB_H

#include <cstdint>
#include <cstdio>
#include <vector>
#include <stdexcept>
#include <cstdlib>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

using std::vector;
using std::invalid_argument;

/* IP stands for 'interview problem' */

typedef double ipNumber;

enum IPEXITSTATUS : int
{
  IPOK = 0,
  IPERROR = 1
};

/////////////////////////////////////////////

class IPDrawer
{
public:
  Display *display;
  Window window;
  GC context;
  XEvent event;

  IPDrawer() { }

  IPEXITSTATUS initDisplay(int XRES, int YRES)
  {
    display = XOpenDisplay(NULL);
    if (! display)
      return IPERROR;

    int screen = DefaultScreen(display);
    unsigned int white = WhitePixel(display, screen);
    unsigned int black = BlackPixel(display, screen);

    window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, XRES, YRES, 0, black, black);
    XSelectInput(display, window, StructureNotifyMask);
    XMapWindow(display, window);

    Atom wmDelete=XInternAtom(display, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(display, window, &wmDelete, 1);

    context = XCreateGC(display, window, 0, NULL);

    XSetForeground(display, context, white);

    while (true)
    {
      XNextEvent(display, &event);
      if (event.type == MapNotify)
         break;
    }
    XClearWindow(display, window);
    XFlush(display);
    return IPOK;
  }

  IPEXITSTATUS finishDisplay()
  {
    XFreeGC(display, context);
    XUnmapWindow(display,window);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
    return IPOK;
  }
};

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

  virtual void draw(const IPDrawer& drawer) const
  {
    XFlush(drawer.display);
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

  void draw(const IPDrawer& drawer) const override
  {
    XPoint points[vertexCount + 1];
    for (uint32_t i = 0; i < vertexCount; ++i)
    {
      points[i].x = vertices[i].X;
      points[i].y = vertices[i].Y;
    }
    points[vertexCount].x = vertices[0].X;
    points[vertexCount].y = vertices[0].Y;
    XDrawLines(drawer.display, drawer.window, drawer.context, points, vertexCount + 1, CoordModeOrigin);
    XFlush(drawer.display);
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

  void draw(const IPDrawer& drawer) const override
  {
    XDrawArc(drawer.display, drawer.window, drawer.context, center.X - radius, center.Y - radius, radius * 2, radius * 2, 0, 360 * 64);
    XFlush(drawer.display);
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