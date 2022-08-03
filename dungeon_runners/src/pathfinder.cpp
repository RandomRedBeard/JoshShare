/**
 * @file pathfinder.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-07-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "pathfinder.h"

DR::Pathfinder::Pathfinder() {}

DR::Pathfinder::Pathfinder(const T& nodes) : nodes(nodes) {}

DR::Pathfinder::Pathfinder(const Pathfinder& p) : nodes(p.nodes) {}

std::vector<int> DR::Pathfinder::find_path(int src, int dest) const noexcept{
    // visited bit map len
    unsigned int vlen = (nodes.rbegin()->first / 8) + 1;
    // visited bit map
    std::unique_ptr<char[]> v = std::make_unique<char[]>(vlen);
    // processing queue
    std::queue<int> q;
    // Result mapping 
    std::map<int, int> rmap;
    // src to dest path
    std::vector<int> rpath;

    bool found = false;

    q.push(src);
    bit_flip(v.get(), src);

    while (!q.empty()) {
        int i = q.front();
        if (i == dest) {
            found = true;
            break;
        }

        auto iter = nodes.find(i);
        // Should never happen
        if (iter == nodes.end()) {
            printf("Bad %d\n", i);
            q.pop();
            continue;
        }

        for (int n : iter->second) {
            // Skip if node has been visited
            if (is_bit_flipped(v.get(), n)) {
                continue;
            }

            rmap[n] = i;
            bit_flip(v.get(), n);
            q.push(n);
        }

        q.pop();
    }

    if (!found) {
        return rpath;
    }

    // fill out rpath
    int i = dest;
    while (i != src) {
        rpath.insert(rpath.begin(), i);
        i = rmap[i];
    }

    return rpath;
}