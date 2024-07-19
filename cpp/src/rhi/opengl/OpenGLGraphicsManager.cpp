#include "includes/OpenGLGraphicsManager.hpp"

int OpenGLGraphicsManager::Initialize() {
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
        ERROR_PRINT("获取webgl2 context发生错误");
        return 1;
    }
    emscripten_webgl_make_context_current(mContext);

    const auto& clearColor = mWindow->GetClearColor();
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);

    return 0;
}

void OpenGLGraphicsManager::Finalize() {
}
