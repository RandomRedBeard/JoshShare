
#include <iostream>

#include <point.h>

using namespace std;
using namespace DR;

void test_constructors() {
    Point pt;
    assert(pt.x == 0 && pt.y == 0);

    Point pt1(1, 1);
    assert(pt1.x == 1 && pt1.y == 1);

    Point pt2 = pt1;
    assert(pt2.x == 1 && pt2.y == 1);

    Point pt3 = move(pt1);
    assert(pt3.x == 1 && pt3.y == 1);
}

void test_distances() {
    Point pt1, pt2(1, 1);

    assert(pt1.l1dist(pt2) == 2);

    pt2.x = 0;
    assert(pt1.dist(pt2) == 1);
}

void test_unit_vector() {
    Point pt1(-2, -1), pt2(2, 2);

    assert(pt2.unit_vector(pt1).x - (-4 / 5) < .00001);
}

void test_equals() {
    Point pt1(1, 1), pt2(1, 1);

    assert(pt1 == pt2);

    pt1.x = 2;

    assert(pt1 != pt2);
}

void test_assignment() {
    Point pt1(1, 1), pt2;

    pt2 = pt1;
    assert(pt2.x == 1 && pt2.y == 1);

    pt1.x = 10;
    pt2 = move(pt1);

    assert(pt2.x == 10 && pt2.y == 1);
}

int main() {
    test_constructors();
    test_distances();
    test_unit_vector();
    test_equals();
    test_assignment();
    return 0;
}