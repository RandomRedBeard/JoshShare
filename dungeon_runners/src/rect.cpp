/**
 * @file rect.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-07-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "rect.h"

DR::Rect::Rect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

DR::Rect::Rect() : Rect(0, 0, 0, 0) {}

DR::Rect::Rect(const Rect& r) : Rect(r.x, r.y, r.w, r.h) {}

DR::Rect::Rect(Rect&& r) : Rect(r.x, r.y, r.w, r.h) {}

bool DR::Rect::contains(const Point pt) const noexcept {
    return pt.x >= x && pt.x < x + w && pt.y >= y && pt.y < y + h;
}

unsigned int DR::Rect::area() const noexcept {
    return h * w;
}

json_t* DR::Rect::to_json(json_t* o) const noexcept {
    json_object_set_new(o, "x", json_integer(x));
    json_object_set_new(o, "y", json_integer(y));
    json_object_set_new(o, "w", json_integer(w));
    json_object_set_new(o, "h", json_integer(h));
    return o;
}

void DR::Rect::from_json(const json_t* o) {
    json_t* json_x = json_object_get(o, "x");
    json_t* json_y = json_object_get(o, "y");
    json_t* json_w = json_object_get(o, "w");
    json_t* json_h = json_object_get(o, "h");

    if (json_x) {
        x = json_integer_value(json_x);
    }

    if (json_y) {
        y = json_integer_value(json_y);
    }

    if (json_w) {
        w = json_integer_value(json_w);
    }

    if (json_h) {
        h = json_integer_value(json_h);
    }
}

bool DR::Rect::operator==(const Rect& r) const noexcept {
    puts("Equal Rect");
    return x == r.x && y == r.y && w == r.w && h == r.h;
}

bool DR::Rect::operator!=(const Rect& r) const noexcept {
    return !(this->operator==(r));
}

DR::Rect DR::Rect::operator=(const Rect& r) noexcept {
    x = r.x;
    y = r.y;
    w = r.w;
    h = r.h;

    return *this;
}

DR::Rect DR::Rect::operator=(Rect&& r) noexcept {
    x = r.x;
    y = r.y;
    w = r.w;
    h = r.h;

    return *this;
}