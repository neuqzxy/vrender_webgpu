#pragma once

#include "Vector.hpp"
#include <string>

struct WindowConf {
    uint32_t width;
    uint32_t height;
    std::string title;
};

typedef Vec2f Point;

template <typename T>
struct UniformItem {
    std::string name;
    T data;
};
