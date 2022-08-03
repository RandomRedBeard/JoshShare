

#include <iostream>

#include <room.h>


using namespace std;
using namespace DR;

void test_json() {
    Room r = Rect({0, 0, 10, 10});

    json_t* o = r.new_json();
    char* buf = json_dumps(o, JSON_INDENT(4));

    puts(buf);
}

int main() {
    test_json();
}