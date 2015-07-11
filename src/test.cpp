#include <vector>

#include "GraphLib.h"

using std::vector;


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

  for (auto element: shapeVector)
    element->draw();

  return 0;
}