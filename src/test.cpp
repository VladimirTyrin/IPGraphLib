#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

#include "GraphLib.h"

using std::vector;

enum EXIT_STATUS : int
{
  OK = 0,
  ERROR = 1
};

static Display *display;
static Window window;
static GC gc;


EXIT_STATUS initDisplay(int XRES, int YRES)
{
  display = XOpenDisplay( NULL );
  if (! display)
    return ERROR;

  int screen = DefaultScreen(display);
  unsigned int white = WhitePixel(display, screen);
  unsigned int black = BlackPixel(display, screen);

  window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, XRES, YRES, 0, black, white);

  Atom wmDelete=XInternAtom(display, "WM_DELETE_WINDOW", True);
  XSetWMProtocols(display, window, &wmDelete, 1);

  gc = XCreateGC(display, window, 0, NULL);

  XSetForeground(display, gc, black);
  XMapWindow(display, window);
  XFlush(display);
  return OK;
}


int finishDisplay()
{
  XDestroyWindow(display, window);
  XCloseDisplay(display);
  return OK;
}


int main()
{
  vector<IPShape *> shapeVector;
  IPShape shape;
  IPTriangle triangle({IPPoint(100, 100), IPPoint(100, 200), IPPoint(200, 200)});
  IPQuadrangle square;
  IPPolygon<5> pentagon;
  IPCircle circle;

  shapeVector.push_back(&shape);
  shapeVector.push_back(&triangle);
  shapeVector.push_back(&square);
  shapeVector.push_back(&pentagon);
  shapeVector.push_back(&circle);

  for (auto element: shapeVector)
    element->printInfo();

  if (initDisplay(500, 500) != OK)
    return 1;
  for (auto element: shapeVector)
    element->draw();
  sleep(5);
  finishDisplay();

  return 0;
}