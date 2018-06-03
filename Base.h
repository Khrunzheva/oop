#pragma once

#include <string>
#include <ostream>

class Printable {
public:
    virtual std::string print() const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Printable &printable);
};

std::ostream &operator<<(std::ostream &os, const Printable &printable) {
    os << printable.print();
    return os;
}


class Named : virtual public Printable {
private:
    std::string name;

public:
    explicit Named(const std::string &name) {
        this->name = name;
    }

    const std::string &getName() const {
        return name;
    }

    std::string print() const override {
        return name;
    }
};

class Shape : public virtual Printable {
    static size_t count;

public:
    explicit Shape() {
        ++count;
    }

    Shape(const Shape &other) {
        ++count;
    }

    virtual ~Shape() {
        --count;
    }

    static size_t getCount() {
        return count;
    }
};

size_t Shape::count = 0;