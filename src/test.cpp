#include <vector>
#include <stdio.h>
#include <unistd.h>

#include "GraphLib.h"

using std::vector;

int main()
{
  vector<IPShape *> shapeVector;
  IPShape shape;
  IPTriangle triangle({IPPoint(100, 100), IPPoint(100, 200), IPPoint(200, 200)});
  IPQuadrangle square({IPPoint(220, 220), IPPoint(220, 300), IPPoint(300, 300), IPPoint(300, 220)});
  IPPolygon<5> pentagon({IPPoint(100, 400), IPPoint(100, 450), IPPoint(200, 450), IPPoint(200, 425), IPPoint(125, 375)});
  IPCircle circle(IPPoint(100, 100), 50);

  shapeVector.push_back(&shape);
  shapeVector.push_back(&triangle);
  shapeVector.push_back(&square);
  shapeVector.push_back(&pentagon);
  shapeVector.push_back(&circle);

  for (auto element: shapeVector)
    element->printInfo();

  IPDrawer drawer;
  if (drawer.initDisplay(500, 500) != IPOK)
    return 1;
  for (auto element: shapeVector)
    element->draw(drawer);
  getchar();
  drawer.finishDisplay();

  return 0;
}