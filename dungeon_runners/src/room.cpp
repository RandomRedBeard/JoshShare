/**
 * @file room.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-07-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "room.h"

DR::Room::Room() : Rect() {
    lit = false;
}

DR::Room::Room(const Rect& r) : Rect(r) {}

DR::Room::Room(const Room& r) : Rect(r) {
    lit = r.lit;

    no = r.no;
    so = r.so;
    ea = r.ea;
    we = r.we;
}

DR::Room::Room(Room&& r) : Rect(r) {
    lit = r.lit;

    no = r.no;
    so = r.so;
    ea = r.ea;
    we = r.we;
}

json_t* DR::Room::to_json(json_t* o) const noexcept {
    Rect::to_json(o);

    json_object_set(o, "lit", json_boolean(lit));

    json_object_set_new(o, "no", no.new_json());
    json_object_set_new(o, "so", so.new_json());
    json_object_set_new(o, "ea", ea.new_json());
    json_object_set_new(o, "we", we.new_json());

    return o;
}

void DR::Room::from_json(const json_t* o) {
    Rect::from_json(o);

    json_t* json_lit = json_object_get(o, "lit");

    json_t* json_no = json_object_get(o, "no");
    json_t* json_so = json_object_get(o, "so");
    json_t* json_ea = json_object_get(o, "ea");
    json_t* json_we = json_object_get(o, "we");

    if (json_lit) {
        lit = json_boolean_value(json_lit);
    }

    if (json_no) {
        no.from_json(json_no);
    }

    if (json_so) {
        so.from_json(json_so);
    }

    if (json_ea) {
        ea.from_json(json_ea);
    }

    if (json_we) {
        we.from_json(json_we);
    }

}

bool DR::Room::operator==(const Room& r) const noexcept {
    return Rect::operator==(r) && lit == r.lit && no == r.no && so == r.so && ea == r.ea && we == r.we;
}

bool DR::Room::operator!=(const Room& r) const noexcept {
    return !(this->operator==(r));
}

DR::Room DR::Room::operator=(const Room& r) noexcept {
    Rect::operator=(r);
    lit = r.lit;
    no = r.no;
    so = r.so;
    ea = r.ea;
    we = r.we;
    return *this;
}

DR::Room DR::Room::operator=(Room&& r) noexcept {
    Rect::operator=(r);
    lit = r.lit;
    no = r.no;
    so = r.so;
    ea = r.ea;
    we = r.we;
    return *this;
}