#include <vector>

#include "GraphLib.h"

using std::vector;


int main()
{
  vector<GLShape *> shapeVector;
  GLShape shape;
  GLTriangle triangle({GLPoint(100, 100), GLPoint(100, 200), GLPoint(200, 200)});
  GLQuadrangle square;
  GLPolygon<5> pentagon;
  GLCircle circle;

  shapeVector.push_back(&shape);
  shapeVector.push_back(&triangle);
  shapeVector.push_back(&square);
  shapeVector.push_back(&pentagon);
  shapeVector.push_back(&circle);

  for (auto element: shapeVector)
    element->printInfo();

  for (auto element: shapeVector)
    element->draw();

  return 0;
}