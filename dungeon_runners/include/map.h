/**
 * @file map.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-07-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

// unique_ptr include
#include <memory>
#include <map>

#include <util.h>
#include <serializable.h>
#include <room.h>
#include <hallway.h>
#include <pathfinder.h>

namespace DR {
    class Map : public Serializable {
        // Phys-map attrs
        unsigned int width, height;
        // Room dims
        unsigned int rcols, rrows;
        std::map<int, Room> rooms;
        std::vector<Hallway> halls;

        // Valid move checking
        std::unique_ptr<char[]> layout_bitmap;

        // Pathfinder
        Pathfinder pathfinder;

        void build_layout_bitmap();
        void build_pathfinder();
        Hallway build_hallway(Point pt1, Point pt2);
        void connect_rooms();
        void build_map();
    public:
        Map();
        Map(unsigned int width, unsigned int height, unsigned int rcols, unsigned int rrows);
        ~Map();

        unsigned int get_height() { return height; }
        unsigned int get_width() { return width; }

        unsigned int get_rrows() { return rrows; }
        unsigned int get_rcols() { return rcols; }

        const std::map<int, Room> get_rooms() { return rooms; }
        std::map<int, Room>::const_iterator find_room(int index) { return rooms.find(index); }
        const std::vector<Hallway> get_halls() { return halls; }

        const Pathfinder get_pathfinder() { return pathfinder; }

        json_t* to_json(json_t* o) const noexcept;
        void from_json(const json_t* o);
    };
} // namespace DR
