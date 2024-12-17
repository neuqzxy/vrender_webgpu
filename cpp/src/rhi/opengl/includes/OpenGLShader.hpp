#pragma once

#include "Shader.hpp"

class OpenGLShader final : public Shader {
    [[maybe_unused]] void Compile(const char *vertexSource, const char *fragmentSource) override;
    [[maybe_unused]] void Compile(const char *computedSource) override;
    Shader& Use() override;
    Shader& UnUse() override;

    void Dispose() override;

    // uniform工具函数
    // 设置shader中texture的uniform值
    void InitTextureUniform(int num) override;
    void SetInt(const char *name, int value, bool useShader) override;
    void SetBool(const char *name, bool value, bool useShader) override;
    void SetFloat(const char *name, float value, bool useShader) override;
    void SetVector2f(const char *name, float x, float y, bool useShader) override;
    void SetVector2f(const char *name, const Vec2f &value, bool useShader) override;
    void SetVector2i(const char *name, const Vec2i &value, bool useShader) override;
    void SetVector2i(const char *name, int x, int y, bool useShader) override;
    void SetVector3f(const char *name, float x, float y, float z, bool useShader) override;
    void SetVector3f(const char *name, const Vec3f &value, bool useShader) override;
    void SetVector4f(const char *name, float x, float y, float z, float w, bool useShader) override;
    void SetVector4f(const char *name, const Vec4f &value, bool useShader) override;
    void SetMatrix4(const char *name, const Mat4f &value, bool useShader) override;
    void SetFloatVector(const char *name, const std::vector<float> &value, bool useShader) override;

};