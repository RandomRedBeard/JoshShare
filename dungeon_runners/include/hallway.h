/**
 * @file hallway.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-07-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <vector>

#include <serializable.h>
#include <point.h>

namespace DR {
    class Hallway : public Serializable {
        std::vector<Point> points;
    public:
        Hallway();
        Hallway(const Hallway& h);
        Hallway(Hallway&& h);
        virtual ~Hallway();

        void add_point(Point pt) { points.push_back(pt); }
        const std::vector<Point> get_points() const noexcept { return points; }

        json_t* to_json(json_t* o) const noexcept;
        void from_json(const json_t* o);

        bool operator==(const Hallway& h) const noexcept;
        bool operator!=(const Hallway& h) const noexcept;
        Hallway operator=(const Hallway& h) noexcept;
        Hallway operator=(Hallway&& h) noexcept;
    };
}