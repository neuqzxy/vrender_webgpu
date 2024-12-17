#pragma once

#include <string>
#include <utility>
#include <memory>
#include "Shader.hpp"

template<typename T, typename = std::enable_if<std::is_base_of_v<Shader, T>>>
class PipelineState {
public:
    explicit PipelineState(std::string name): mName{std::move(name)}, mVertShaderName{}, mFragShaderName{} {}

    int Initialize(const std::shared_ptr<Shader>& shader) {
        return 0;
    }
    void Finalize() {}

    std::string mName;
    union {
        struct {
            std::string mVertShaderName;
            std::string mFragShaderName;
        };
        std::string mComputedShaderName;
        std::string mRenderShaderName;
    };

protected:
    std::shared_ptr<T> mShader;
};
