#include "../include/coordination.h"
#include <cstdint>
#include <cstdio>

Coord::Coord(int8_t h, int8_t w) {
    this->h = h;
    this->w = w;
    index = h*8 + w;
}

Coord::Coord(char h, char w) {
    this->h = h - '1';
    this->w = w - 'a';
    index = this->h*8 + this->w;
}

Coord::Coord(int8_t index) {
    this->index = index;
    h = index / 8;
    w = index % 8;
}

Path::Path(Coord from, Coord to) {
    this->from = from;
    this->to = to;
}