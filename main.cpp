#include <iostream>
#include "Container.h"
#include "Shapes.h"
#include "ShapeFactory.h"

using namespace std;

int main() {
    Container<Shape*> shapes;
    for (int i = 0; i < 25; ++i) {
        shapes.addEnd(ShapeFactory::getShape());
    }
    cout << "Количество фигур: " << Shape::getCount() << endl;
    for (auto i = shapes.cbegin(); i != shapes.cend(); ++i) {
        cout << **i << endl;
    }
    for (auto i = shapes.cbegin(); i != shapes.cend(); ++i) {
        delete *i;
    }
    shapes.clear();
    cout << "Количество фигур: " << Shape::getCount() << endl;
    return 0;
}
