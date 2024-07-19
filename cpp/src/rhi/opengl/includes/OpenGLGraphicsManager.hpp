#pragma once

#include <memory>
#include <emscripten/html5.h>
#include <cstdio>
#include <GLES2/gl2.h>
#include "GraphicsManager.hpp"
#include "IWindow.hpp"
#include "Output.hpp"

class OpenGLGraphicsManager: public GraphicsManager {
public:
    explicit OpenGLGraphicsManager(IWindow *w): GraphicsManager(std::shared_ptr<IWindow>{w}), mContext{0} {}
    int Initialize() override;
    void Finalize() override;
    ~OpenGLGraphicsManager() override = default;

protected:
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE mContext;

    void SwapFrame() override {
        const auto& clearColor = mWindow->GetClearColor();
        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
        glClear(GL_COLOR_BUFFER_BIT);
    };
};
