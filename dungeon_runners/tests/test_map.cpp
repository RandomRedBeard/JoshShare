/**
 * @file test_map.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <assert.h>

#include <map.h>

using namespace std;
using namespace DR;

void test_json() {
    srand(time(0));
    Map m(80, 25, 3, 3);
    json_t* o = m.new_json();

    Map m1 = Serializable::from_json<Map>(o);

    std::map<int, Room> m1_rooms = m1.get_rooms();

    for (std::pair<int, Room> r : m.get_rooms()) {
        std::map<int, Room>::const_iterator iter = m1.find_room(r.first);
        if (iter!= m1_rooms.end()) {
            assert(0);
        }
        assert(iter != m1_rooms.end());
        assert(r.second == iter->second);
        printf("Compared %d\n", r.first);
    }

    json_decref(o);
}

int main() {
    test_json();
    return 0;
}