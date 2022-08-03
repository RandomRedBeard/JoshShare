/**
 * @file pathfinder.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

// unique_ptr include
#include <memory>
#include <map>
#include <vector>
#include <queue>

#include <util.h>

namespace DR {
    class Pathfinder {
        using T = std::map<int, std::vector<int>>;
        T nodes;
    public:
        Pathfinder();
        Pathfinder(const T& nodes);
        Pathfinder(const Pathfinder& p);

        std::vector<int> find_path(int src, int dest) const noexcept;
    };
}