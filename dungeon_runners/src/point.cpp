/**
 * @file point.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-07-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "point.h"

DR::Point::Point(int x, int y) : x(x), y(y) {}

DR::Point::Point() : Point(0, 0) {}

DR::Point::Point(const Point& pt) : Point(pt.x, pt.y) {}

DR::Point::Point(Point&& pt) : Point(pt.x, pt.y) {}

DR::Point::~Point() {}

double DR::Point::dist(const Point pt) const noexcept {
    return std::sqrt(std::pow(x - pt.x, 2) + std::pow(y - pt.y, 2));
}

DR::DoublePoint DR::Point::unit_vector(const Point pt) const noexcept {
    double mag = dist(pt);
    return DoublePoint((pt.x - x) / mag, (pt.y - y) / mag);
}

int DR::Point::l1dist(const Point pt) const noexcept {
    return std::abs(x - pt.x) + std::abs(y - pt.y);
}

int DR::Point::index(int width) const noexcept {
    return y * width + x;
}

json_t* DR::Point::to_json(json_t* root) const noexcept {
    json_object_set_new(root, "x", json_integer(x));
    json_object_set_new(root, "y", json_integer(y));
    return root;
}

void DR::Point::from_json(const json_t* o) {
    json_t* json_x = json_object_get(o, "x");
    json_t* json_y = json_object_get(o, "y");

    if (json_x) {
        x = json_integer_value(json_x);
    }

    if (json_y) {
        y = json_integer_value(json_y);
    }
}

bool DR::Point::operator==(const Point& pt) const noexcept {
    return x == pt.x && y == pt.y;
}

bool DR::Point::operator!=(const Point& pt) const noexcept {
    return !(this->operator==(pt));
}

DR::Point DR::Point::operator=(const Point& pt) noexcept {
    x = pt.x;
    y = pt.y;
    return *this;
}

DR::Point DR::Point::operator=(Point&& pt) noexcept {
    x = pt.x;
    y = pt.y;
    return *this;
}

DR::Point DR::Point::rand(int x_upper, int y_upper) {
    return Point(std::rand() % x_upper, std::rand() % y_upper);
}

DR::Point DR::Point::index(int index, int width) {
    return { index % width, index / width };
}

DR::DoublePoint::DoublePoint(double x, double y) : x(x), y(y) {}

DR::DoublePoint::DoublePoint() : DoublePoint(0, 0) {}

DR::DoublePoint::DoublePoint(const DoublePoint& pt) : DoublePoint(pt.x, pt.y) {}

DR::DoublePoint::DoublePoint(DoublePoint&& pt) : DoublePoint(pt.x, pt.y) {}

double DR::DoublePoint::dist(const DoublePoint pt) const noexcept {
    return std::sqrt(std::pow(x - pt.x, 2) + std::pow(y - pt.y, 2));
}

double DR::DoublePoint::dist(const Point pt) const noexcept {
    return std::sqrt(std::pow(x - pt.x, 2) + std::pow(y - pt.y, 2));
}

DR::DoublePoint DR::DoublePoint::unit_vector(const Point pt) const noexcept {
    double mag = dist(pt);
    return DoublePoint((pt.x - x) / mag, (pt.y - y) / mag);
}

DR::DoublePoint DR::DoublePoint::unit_vector(const DoublePoint pt) const noexcept {
    double mag = dist(pt);
    return DoublePoint((pt.x - x) / mag, (pt.y - y) / mag);
}
