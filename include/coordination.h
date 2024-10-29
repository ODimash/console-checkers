#pragma once

#include <cstdint>

struct Coord {
    int8_t h;
    int8_t w;
    int8_t index;

    Coord() = default;
    Coord(int8_t, int8_t);
    Coord(char, char);
    Coord(int8_t);
};

struct Path {
    Coord from;
    Coord to;

    Path() = default;
    Path(Coord, Coord);
};