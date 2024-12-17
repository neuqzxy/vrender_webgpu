#pragma once

#include <string>
#include <vector>
#include "Vector.hpp"
#include "Struct.hpp"

class Shader {
public:
    enum ShaderType: int {
        Render = 0,
        Computed
    };
    explicit Shader(std::string name, ShaderType type): mId{sId++}, mName{std::move(name)}, mLastCommonUniformUpdateStamp{0}, mType{type} {}

    [[maybe_unused]] virtual void Compile(const char *vertexSource, const char *fragmentSource) = 0;
    [[maybe_unused]] virtual void Compile(const char *computedSource) = 0;
    virtual Shader& Use() = 0;
    virtual Shader& UnUse() = 0;

    virtual void Dispose() = 0;

    // uniform工具函数
    // 设置shader中texture的uniform值
    virtual void InitTextureUniform(int num) = 0;
    virtual void SetInt(const char *name, int value, bool useShader) = 0;
    virtual void SetBool(const char *name, bool value, bool useShader) = 0;
    virtual void SetFloat(const char *name, float value, bool useShader) = 0;
    virtual void SetVector2f(const char *name, float x, float y, bool useShader) = 0;
    virtual void SetVector2f(const char *name, const Vec2f &value, bool useShader) = 0;
    virtual void SetVector2i(const char *name, const Vec2i &value, bool useShader) = 0;
    virtual void SetVector2i(const char *name, int x, int y, bool useShader) = 0;
    virtual void SetVector3f(const char *name, float x, float y, float z, bool useShader) = 0;
    virtual void SetVector3f(const char *name, const Vec3f &value, bool useShader) = 0;
    virtual void SetVector4f(const char *name, float x, float y, float z, float w, bool useShader) = 0;
    virtual void SetVector4f(const char *name, const Vec4f &value, bool useShader) = 0;
    virtual void SetMatrix4(const char *name, const Mat4f &value, bool useShader) = 0;
    virtual void SetFloatVector(const char *name, const std::vector<float> &value, bool useShader) = 0;

    [[nodiscard]] bool NeedUpdateCommonUniform(size_t stamp) const { return stamp >= mLastCommonUniformUpdateStamp; }
    void ResetLastCommonUniformUpdateStamp(size_t stamp) { mLastCommonUniformUpdateStamp = stamp; }

    template<typename T>
    void SetUniform(UniformItem<T> &uniformItem, bool use = true) {
        if (use) {
            Use();
        }
        if constexpr (std::is_same<T, glm::vec2>::value) {
            SetVector2f(uniformItem.name.c_str(), uniformItem.data);
        }
        if constexpr (std::is_same<T, glm::vec3>::value) {
            SetVector3f(uniformItem.name.c_str(), uniformItem.data);
        }
        if constexpr (std::is_same<T, glm::vec4>::value) {
            SetVector4f(uniformItem.name.c_str(), uniformItem.data);
        }
        if constexpr (std::is_same<T, float>::value) {
            SetFloat(uniformItem.name.c_str(), uniformItem.data);
        }
        if constexpr (std::is_same<T, int>::value) {
            SetInt(uniformItem.name.c_str(), uniformItem.data);
        }
        if constexpr (std::is_same<T, glm::vec<2, int>>::value) {
            SetVector2i(uniformItem.name.c_str(), uniformItem.data);
        }
        if constexpr (std::is_same<T, std::vector<float>>::value) {
            SetFloatVector(uniformItem.name.c_str(), uniformItem.data);
        }
        if constexpr (std::is_same<T, glm::mat4>::value) {
            SetMatrix4(uniformItem.name.c_str(), uniformItem.data);
        }
    }

    unsigned int mId;
protected:
    static unsigned int sId;
    std::string mName;
    ShaderType mType;
    size_t mLastCommonUniformUpdateStamp; // 记录上次更新CommonUniform的stamp
};