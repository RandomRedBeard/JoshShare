/**
 * @file room.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-07-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <serializable.h>
#include <point.h>
#include <rect.h>

namespace DR {
    class Room : public Rect {
        bool lit;

        // Hallway doors
        Point no, so, ea, we;
    public:
        Room();
        Room(const Rect& r);
        Room(const Room& r);
        Room(Room&& r);

        bool isLit() const noexcept { return lit; };

        void setNo(Point pt) { no = pt; }
        void setSo(Point pt) { so = pt; }
        void setEa(Point pt) { ea = pt; }
        void setWe(Point pt) { we = pt; }

        Point getNo() const noexcept { return no; };
        Point getSo() const noexcept { return so; };
        Point getEa() const noexcept { return ea; };
        Point getWe() const noexcept { return we; }

        json_t* to_json(json_t* o) const noexcept;
        void from_json(const json_t* o);

        bool operator==(const Room& r) const noexcept;
        bool operator!=(const Room& r) const noexcept;
        Room operator=(const Room& r) noexcept;
        Room operator=(Room&& pt) noexcept;
    };
} // namespace DR 