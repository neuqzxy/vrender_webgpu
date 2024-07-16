#include "Bounds.hpp"
#include "Tools.hpp"

void Bound2D::Calc(float x, float y, float w, float h, const Mat4f &matrix) {
    float &minX = mBound.x, &minY = mBound.y, &maxX = mBound.z, &maxY = mBound.w;
    minX = minY = std::numeric_limits<float>::max();
    maxX = maxY = -std::numeric_limits<float>::max();
    auto data = matrix * Vec4f{x, y, 0, 1};
    GetMinMax(minX, minY, maxX, maxY, data);
    data = matrix * Vec4f{x+w, y, 0, 1};
    GetMinMax(minX, minY, maxX, maxY, data);
    data = matrix * Vec4f{x, y+h, 0, 1};
    GetMinMax(minX, minY, maxX, maxY, data);
    data = matrix * Vec4f{x+w, y+h, 0, 1};
    GetMinMax(minX, minY, maxX, maxY, data);
}

void Bound2D::Calc(const Vec2f &pos, float w, float h, const Mat4f &matrix) {
    float &minX = mBound.x, &minY = mBound.y, &maxX = mBound.z, &maxY = mBound.w;
    minX = minY = std::numeric_limits<float>::max();
    maxX = maxY = -std::numeric_limits<float>::max();

    Vec2f nextPos{pos.x, pos.y};
    Multiple(nextPos, nextPos, matrix);
    GetMinMax(minX, minY, maxX, maxY, nextPos);
    nextPos.x = pos.x+w; nextPos.y = pos.y;
    Multiple(nextPos, nextPos, matrix);
    GetMinMax(minX, minY, maxX, maxY, nextPos);
    nextPos.x = pos.x; nextPos.y = pos.y + h;
    Multiple(nextPos, nextPos, matrix);
    GetMinMax(minX, minY, maxX, maxY, nextPos);
    nextPos.x = pos.x+w; nextPos.y = pos.y + h;
    Multiple(nextPos, nextPos, matrix);
    GetMinMax(minX, minY, maxX, maxY, nextPos);
}


void Bound2D::GetMinMax(float &minX, float &minY, float &maxX, float &maxY, const Vec4f &data) {
    if (data.x < minX) {
        minX = data.x;
    } else if (data.x > maxX) {
        maxX = data.x;
    }
    if (data.y < minY) {
        minY = data.y;
    } else if (data.y > maxY) {
        maxY = data.y;
    }
}

void Bound2D::GetMinMax(float &minX, float &minY, float &maxX, float &maxY, const Vec2f &data) {
    if (data.x < minX) {
        minX = data.x;
    } else if (data.x > maxX) {
        maxX = data.x;
    }
    if (data.y < minY) {
        minY = data.y;
    } else if (data.y > maxY) {
        maxY = data.y;
    }
}