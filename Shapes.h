#pragma once

#include "Base.h"
#include "Container.h"

#include <cmath>
#include <exception>

class Point : public Shape, public Named {
    double x;
    double y;

public:
    Point(const std::string &name, const double &x, const double &y) : Named(name), x(x), y(y) {}

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    double distance(const Point &other) const {
        double x = this->x - other.getX();
        double y = this->y - other.getY();
        return sqrt(x * x + y * y);
    }

    std::string print() const override {
        return getName() + " (" + std::to_string(x) + "; " + std::to_string(y) + ")";
    }
};


class Circle : public Shape, public Named {
    Point center;
    double radius;

public:
    class negative_radius : public std::logic_error {
    public:
        negative_radius() : logic_error("Радиус должен быть больше нуля") {}
    };

    Circle(const std::string &name, const Point &center, const double &radius) : Named(name), center(center),
                                                                                 radius(radius) {
        if (radius <= 0) {
            throw negative_radius();
        }
    }

    std::string print() const override {
        return getName() + " с центром " + center.print() + " и радиусом = " + std::to_string(radius);
    }
};


class Rect : public Shape, public Named {
    Point topLeft;
    Point bottomRight;

public:
    class incorrect_points : public std::logic_error {
    public:
        incorrect_points() : logic_error("Вывернутый прямоугольник") {}
    };

    class negative_dimension : public std::logic_error {
    public:
        negative_dimension() : logic_error("Размеры должны быть положительными") {}
    };

    Rect(const std::string &name, const Point &topLeft, const Point &bottomRight)
            : Named(name), topLeft(topLeft), bottomRight(bottomRight) {
        if (topLeft.getX() >= bottomRight.getX() or topLeft.getY() <= bottomRight.getY()) {
            throw incorrect_points();
        }
    }

    Rect(const std::string &name, const Point &topLeft, double width, double height)
            : Named(name), topLeft(topLeft),
              bottomRight(Point("Точка", topLeft.getX() + width, topLeft.getY() - height)) {
        if (width < 0 or height < 0) {
            throw negative_dimension();
        }
    };

    std::string print() const override {
        return getName() + " с точками " + topLeft.print() + " и " + bottomRight.print();
    }
};

class Square : public Shape, public Named {
    Point topLeft;
    double sideLength;

public:
    class not_positive_side_length : public std::logic_error {
    public:
        not_positive_side_length() : logic_error("Размеры должны быть положительными") {}
    };

    Square(const std::string &name, const Point &topLeft, const double &sideLength)
            : Named(name), topLeft(topLeft), sideLength(sideLength) {
        if (sideLength < 0) {
            throw not_positive_side_length();
        }
    }

    std::string print() const override {
        return getName() + " с верхней левой точкой в " + topLeft.print() + " и стороной = " +
               std::to_string(sideLength);
    }
};

class Polyline : public Shape, public Named {
    Container<Point> points;
    double length;

public:
    Polyline(const std::string &name) : Named(name) {
        this->length = length;
    }

    void addPoint(const Point &point) {
        if (!points.isEmpty()) {
            length += points.last().distance(point);
        }
        points.addEnd(point);
    }

    std::string print() const override {
        if (points.isEmpty()) {
            return "Пустой " + getName();
        }
        return getName() + ": длина = " + std::to_string(length);
    }
};

class Polygon : public Shape, public Named {
    Container<Point> points;

public:
    explicit Polygon(const std::string &name) : Named(name) {}

    void addPoint(const Point &point) {
        points.addEnd(point);
    }

    std::string print() const override {
        if (points.isEmpty()) {
            return "Пустой" + getName();
        }
        std::string str = getName() + ": " + points.first().print();
        for (auto i = ++points.cbegin(); i != points.cend(); ++i) {
            str += ", " + (*i).print();
        }
        return str;
    }
};
