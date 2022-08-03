/**
 * @file hallway.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-07-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "hallway.h"

DR::Hallway::Hallway() {}

DR::Hallway::Hallway(const Hallway& h) : points(h.points) {}

DR::Hallway::Hallway(Hallway&& h) : points(std::move(h.points)) {}

DR::Hallway::~Hallway() {}

json_t* DR::Hallway::to_json(json_t* o) const noexcept {
    json_t* json_points = json_array();

    for (Point pt : points) {
        json_array_append_new(json_points, pt.new_json());
    }

    json_object_set_new(o, "points", json_points);
    return o;
}

void DR::Hallway::from_json(const json_t* o) {
    json_t* json_points = json_object_get(o, "points");

    if (!json_points) {
        return;
    }

    size_t index;
    json_t* value;
    json_array_foreach(json_points, index, value) {
        Point pt = Serializable::from_json<Point>(value);
        points.push_back(pt);
    }
}

bool DR::Hallway::operator==(const Hallway& h) const noexcept {
    return points == h.points;
}

bool DR::Hallway::operator!=(const Hallway& h) const noexcept {
    return !(Hallway::operator==(h));
}

DR::Hallway DR::Hallway::operator=(const Hallway& h) noexcept {
    points = h.points;
    return *this;
}

DR::Hallway DR::Hallway::operator=(Hallway&& h) noexcept {
    points = h.points;
    return *this;
}