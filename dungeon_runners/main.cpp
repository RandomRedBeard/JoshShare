
#include <iostream>

#include <map.h>
#include <pathfinder.h>
#include <c_graphics.h>

using namespace std;
using namespace DR;

int main() {

    srand(time(0));

    Map m(150, 40, 7, 5);

    unsigned int width = m.get_width();
    const Pathfinder p = m.get_pathfinder();
    Room src_room = m.get_rooms().begin()->second;
    Point src(src_room.x + 1, src_room.y + 1);

    CGraphics c;

    c.set_logger({ 0, (int)m.get_height(), (int)m.get_width() , 20 });
    c.addwin("map", { 0, 0, (int)m.get_width(), (int)m.get_height() });

    for (std::pair<int, Room> r : m.get_rooms()) {
        c.put_room("map", r.second, CGraphicsRoomConfig());
    }

    for (Hallway h : m.get_halls()) {
        c.put_hallway("map", h, '#');
    }

    int ch = c.cgetch("map");
    if (ch != KEY_MOUSE) {
        printw("Not mouse %d", ch);
        getch();
        return -1;
    }

    MEVENT event;
    if (getmouse(&event) != OK) {
        printw("Failed to get mouse");
        getch();
        return -1;
    }

    Point dest(event.x, event.y);

    vector<int> rpath = p.find_path(src.index(width), dest.index(width));

    c.put("map", src, 'S');
    c.put("map", dest, 'D');

    for (int i : rpath) {
        if (i == src.index(width) || i == dest.index(width)) {
            continue;
        }
        c.put("map", Point::index(i, width), '*');
    }

    getch();

    return 0;
}