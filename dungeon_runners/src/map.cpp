/**
 * @file map.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-07-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "map.h"

DR::Map::Map() {}

DR::Map::Map(unsigned int width, unsigned int height, unsigned int rcols, unsigned int rrows) : width(width), height(height), rcols(rcols), rrows(rrows) {
    build_map();
    connect_rooms();
    build_layout_bitmap();
    build_pathfinder();
}

DR::Map::~Map() {
}

void DR::Map::build_layout_bitmap() {
    unsigned int len = ((width * height) / 8) + 1;
    layout_bitmap = std::make_unique<char[]>(len);

    for (std::pair<int, Room> p : rooms) {
        Room r = p.second;
        for (int i = 1; i < r.w - 1; i++) {
            for (int j = 1; j < r.h - 1; j++) {
                bit_flip(layout_bitmap.get(), Point::index(i + r.x, j + r.y, width));
            }
        }

        if (r.getEa().x > 0) {
            bit_flip(layout_bitmap.get(), r.getEa().index(width));
        }

        if (r.getSo().x > 0) {
            bit_flip(layout_bitmap.get(), r.getSo().index(width));
        }

        if (r.getWe().x > 0) {
            bit_flip(layout_bitmap.get(), r.getWe().index(width));
        }

        if (r.getNo().x > 0) {
            bit_flip(layout_bitmap.get(), r.getNo().index(width));
        }
    }

    for (Hallway h : halls) {
        for (Point p : h.get_points()) {
            bit_flip(layout_bitmap.get(), p.index(width));
        }
    }
}

void DR::Map::build_pathfinder() {
    // Build pathfinder map
    unsigned int len = width * height;
    std::map<int, std::vector<int>> nodes;

    for (unsigned int i = 0; i < len; i++) {
        if (!is_bit_flipped(layout_bitmap.get(), i)) {
            continue;
        }

        std::vector<int> neighbors;

        // Up
        if (i - width >= 0 && is_bit_flipped(layout_bitmap.get(), i - width)) {
            neighbors.push_back(i - width);
        }

        if (i + width < len && is_bit_flipped(layout_bitmap.get(), i + width)) {
            neighbors.push_back(i + width);
        }

        if (i % width != 0 && is_bit_flipped(layout_bitmap.get(), i - 1)) {
            neighbors.push_back(i - 1);
        }

        if (i % width != width - 1 && is_bit_flipped(layout_bitmap.get(), i + 1)) {
            neighbors.push_back(i + 1);
        }

        if (!neighbors.empty()) {
            nodes[i] = neighbors;
        }
    }

    pathfinder = Pathfinder(nodes);
}


DR::Hallway DR::Map::build_hallway(Point pt1, Point pt2) {
    int xleft = std::abs(pt1.x - pt2.x), yleft = std::abs(pt1.y - pt2.y);
    int xdir = 0, ydir = 0, dir;
    Point index = pt1;
    Hallway h;

    if (pt1.x < pt2.x) {
        xdir = 1;
    }
    else if (pt1.x > pt2.x) {
        xdir = -1;
    }

    if (pt1.y < pt2.y) {
        ydir = 1;
    }
    else if (pt1.y > pt2.y) {
        ydir = -1;
    }

    while (index != pt2) {
        h.add_point(index);

        if (xleft > std::rand() % (yleft + 1)) {
            dir = 0;
        }
        else {
            dir = 1;
        }

        if (dir == 0) {
            index.x += xdir;
            xleft--;
        }
        else if (dir == 1) {
            index.y += ydir;
            yleft--;
        }
    }

    h.add_point(index);
    return h;
}

void DR::Map::connect_rooms() {
    // Iter by ref
    for (std::pair<const int, DR::Room>& r : rooms) {
        int index = r.first;
        // Reference
        Room& src = r.second;
        /**
         * @brief Check to the right
         *
         */
        for (unsigned int i = 1; i < rcols - (index % rcols); i++) {
            int search_index = index + i;
            std::map<int, Room>::iterator iter = rooms.find(search_index);
            // Room not found
            if (iter == rooms.end()) {
                continue;
            }

            // Grab ref
            Room& dest = iter->second;

            // Set entrances
            src.setEa({ src.x + src.w - 1, src.y + 1 + std::rand() % (src.h - 2) });
            dest.setWe({ dest.x, dest.y + 1 + std::rand() % (dest.h - 2) });

            // Build hallway
            Point ea = src.getEa(), we = dest.getWe();
            Hallway h = build_hallway({ ea.x + 1, ea.y }, { we.x - 1, we.y });
            halls.push_back(h);

            break;
        }

        /**
         * @brief Check below
         *
         */
        for (unsigned int i = 1; i < rrows - (index / rcols); i++) {
            int search_index = index + (i * rcols);
            std::map<int, Room>::iterator iter = rooms.find(search_index);
            // Room not found
            if (iter == rooms.end()) {
                continue;
            }

            // Grab ref
            Room& dest = iter->second;

            // Set entrances
            src.setSo({ src.x + 1 + std::rand() % (src.w - 2), src.y + src.h - 1 });
            dest.setNo({ dest.x + 1 + std::rand() % (dest.w - 2), dest.y });

            // Build hallway
            Point so = src.getSo(), no = dest.getNo();
            Hallway h = build_hallway({ so.x, so.y + 1 }, { no.x, no.y - 1 });
            halls.push_back(h);

            break;
        }
    }
}

void DR::Map::build_map() {
    unsigned int maxrw = width / rcols;
    unsigned int maxrh = height / rrows;
    unsigned int rcount = rrows * rcols;

    int numberOfAllowed = ((rrows - 1) * (rcols - 1)) + 2;
    int numberAllowedFalse = rcount - numberOfAllowed;

    /**
     * @brief Build rooms
     *
     */
    for (unsigned int i = 0; i < rrows; i++) {
        for (unsigned int j = 0; j < rcols; j++) {
            int index = i * rcols + j;
            if (prob(numberAllowedFalse / (rcount * 1.0))) {
                numberAllowedFalse--;
                continue;
            }

            Point p(4 + std::rand() % (maxrw - 6), 4 + std::rand() % (maxrh - 6));

            int tmidptw = maxrw * j;
            int tmidpth = maxrh * i;
            int wdel = maxrw - p.x;
            int hdel = maxrh - p.y;

            Point tl(tmidptw + (1 + std::rand() % (wdel - 2)), tmidpth + (1 + std::rand() % (hdel - 2)));

            Room r({ tl.x, tl.y, p.x, p.y });
            rooms.insert({ index, r });
        }
    }
}

json_t* DR::Map::to_json(json_t* o) const noexcept {
    json_t* json_rooms = json_array();

    for (std::pair<int, Room> r : rooms) {
        json_t* json_r = json_object();
        json_object_set_new(json_r, "index", json_integer(r.first));
        json_object_set_new(json_r, "room", r.second.new_json());
        json_array_append_new(json_rooms, json_r);
    }

    json_object_set_new(o, "rooms", json_rooms);

    json_t* json_halls = json_array();

    for (Hallway h : halls) {
        json_array_append_new(json_halls, h.new_json());
    }

    json_object_set_new(o, "halls", json_halls);

    json_object_set_new(o, "width", json_integer(width));
    json_object_set_new(o, "height", json_integer(height));
    json_object_set_new(o, "rcols", json_integer(rcols));
    json_object_set_new(o, "rrows", json_integer(rrows));

    return o;
}

void DR::Map::from_json(const json_t* o) {
    json_t* json_rooms = json_object_get(o, "rooms");

    size_t index;
    json_t* value;
    json_array_foreach(json_rooms, index, value) {
        json_t* json_index = json_object_get(value, "index");
        json_t* json_room = json_object_get(value, "room");

        rooms.insert({ json_integer_value(json_index), Serializable::from_json<Room>(json_room) });
    }

    json_t* json_halls = json_object_get(o, "halls");

    json_array_foreach(json_halls, index, value) {
        halls.push_back(Serializable::from_json<Hallway>(value));
    }

    json_t* json_width = json_object_get(o, "width");
    json_t* json_height = json_object_get(o, "height");
    json_t* json_rcols = json_object_get(o, "rcols");
    json_t* json_rrows = json_object_get(o, "rrows");

    if (json_width) {
        width = json_integer_value(json_width);
    }

    if (json_height) {
        height = json_integer_value(json_height);
    }

    if (json_rcols) {
        rcols = json_integer_value(json_rcols);
    }

    if (json_rrows) {
        rrows = json_integer_value(json_rrows);
    }
}