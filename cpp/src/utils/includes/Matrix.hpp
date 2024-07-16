#pragma once

#include "Vector.hpp"

class Matrix2D {
public:
    Matrix2D(): mMatrix{1.f} {};
    const Mat4f& Translate(const glm::vec2 &pos);
    const Mat4f& Translate(float x, float y);
    const Mat4f& Rotate(float angle);
    const Mat4f& Rotate(float angle, const glm::vec3 &rotateCenter);
    const Mat4f& Scale(const glm::vec2 &scale);
    const Mat4f& Scale(float x, float y);
    const Mat4f& Transform(const glm::vec2 &pos, const glm::vec2 &scale, const float &angle, const glm::vec2 &rotateCenter);
    const Mat4f& Copy(const Matrix2D &matrix2D);
    const Mat4f& Copy(Mat4f &matrix);
    bool WithOutScaleAndRotate() const;

    [[nodiscard]] inline const Mat4f& GetMatrix() const { return mMatrix; }
    [[nodiscard]] inline Mat4f& GetWritableMatrix() { return mMatrix; }
private:
    Mat4f mMatrix;
};
