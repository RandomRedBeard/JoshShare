/**
 * @file point.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-07-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <cstdlib>
#include <algorithm>
#include <cmath>

#include <serializable.h>

namespace DR {
    struct Point : public Serializable {
        int x, y;
        Point(int x, int y);
        Point();
        Point(const Point& pt);
        Point(Point&& pt);
        virtual ~Point();

        /**
         * @brief Straight line distance
         *
         * @param pt
         * @return double
         */
        double dist(const Point pt) const noexcept;

        struct DoublePoint unit_vector(const Point pt) const noexcept;

        /**
         * @brief Taxi-Cab distance
         *
         * @param pt
         * @return int
         */
        int l1dist(const Point pt) const noexcept;

        /**
         * @brief C-Style index of point on 1d with a supposed width
         *
         * @param width
         * @return int
         */
        int index(int width) const noexcept;

        json_t* to_json(json_t* o) const noexcept;
        void from_json(const json_t* o);

        bool operator==(const Point& pt) const noexcept;
        bool operator!=(const Point& pt) const noexcept;
        Point operator=(const Point& pt) noexcept;
        Point operator=(Point&& pt) noexcept;

        /**
         * @brief Random point with given bounds
         *
         * @param x_upper
         * @param y_upper
         * @return Point
         */
        static Point rand(int x_upper, int y_upper);

        /**
         * @brief
         *
         * @param index
         * @param width
         * @return Point
         */
        static Point index(int index, int width);

        static int index(int x, int y, int width) { return Point(x, y).index(width); }
    };

    struct DoublePoint {
        double x, y;
        DoublePoint(double x, double y);
        DoublePoint();
        DoublePoint(const DoublePoint& pt);
        DoublePoint(DoublePoint&& pt);

        /**
         * @brief Straight line distance
         *
         * @param pt
         * @return double
         */
        double dist(const DoublePoint pt) const noexcept;

        /**
         * @brief Straight line distance
         *
         * @param pt
         * @return double
         */
        double dist(const Point pt) const noexcept;

        DoublePoint unit_vector(const DoublePoint pt) const noexcept;

        DoublePoint unit_vector(const Point pt) const noexcept;

        bool operator==(const DoublePoint& pt) const noexcept;
        bool operator!=(const DoublePoint& pt) const noexcept;
        DoublePoint operator=(const DoublePoint& pt) noexcept;
        DoublePoint operator=(DoublePoint&& pt) noexcept;
    };
} // namespace DR