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
    int Initialize() override {
        EmscriptenWebGLContextAttributes attrs{};
        emscripten_webgl_init_context_attributes(&attrs);
        attrs.explicitSwapControl = false;
        attrs.depth = true;
        attrs.stencil = true;
        attrs.antialias = true;
        attrs.majorVersion = 2;
        attrs.minorVersion = 0;

        mContext = emscripten_webgl_create_context(("#"+mWindow->GetCanvasId()).c_str(), &attrs);
        if (mContext == 0) {
            ERROR_PRINT("获取context发生错误");
            return 1;
        }
        emscripten_webgl_make_context_current(mContext);

        const auto& clearColor = mWindow->GetClearColor();
        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
        glClear(GL_COLOR_BUFFER_BIT);

        return 0;
    };
    void Finalize() override {

    };
    ~OpenGLGraphicsManager() override = default;

protected:
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE mContext;

    void SwapFrame() override {
        const auto& clearColor = mWindow->GetClearColor();
        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
        glClear(GL_COLOR_BUFFER_BIT);
    };
};
