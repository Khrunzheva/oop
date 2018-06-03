#pragma once

#include "Shapes.h"

class ShapeFactory {

    static double random_double(double a, double b) {
        double random = (double) rand() / RAND_MAX;
        return a + random * (b - a);
    }

    static int random_int(int a, int b) {
        int random = rand() % (b - a + 1) + a;
        return random;
    }

    static Point pointObject() {
        return Point("Точка", random_double(-25, 25), random_double(-25, 25));
    }

public:
    static Shape *getShape() {
        int shape_number = random_int(0, 5);
        switch (shape_number) {
            case 0:
                return getPoint();
            case 1:
                return getCircle();
            case 2:
                return getRect();
            case 3:
                return getSquare();
            case 4:
                return getPolyline();
            case 5:
                return getPolygon();
            default:
                return nullptr;
        }
    }

    static Point *getPoint() {
        return new Point("Точка", random_double(-25, 25), random_double(-25, 25));
    }

    static Circle *getCircle() {
        return new Circle("Круг", pointObject(), random_double(1, 25));
    }

    static Rect *getRect() {
        return new Rect("Прямоугольник", pointObject(), random_double(1, 25), random_double(1, 25));
    }

    static Square *getSquare() {
        return new Square("Квадрат", pointObject(), random_double(1, 25));
    }

    static Polyline *getPolyline() {
        auto *polyline = new Polyline("Ломаная");
        int n = random_int(3, 25);
        for (int i = 0; i < n; ++i) {
            polyline->addPoint(pointObject());
        }
        return polyline;
    }

    static Polygon *getPolygon() {
        auto *polygon = new Polygon("Многоугольник");
        int n = random_int(3, 25);
        for (int i = 0; i < n; ++i) {
            polygon->addPoint(pointObject());
        }
        return polygon;
    }
};