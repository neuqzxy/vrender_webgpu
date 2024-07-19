#pragma once

#include <emscripten/html5_webgpu.h>
#include "WebGPUDevice.hpp"
#include "WebGPUSurface.hpp"
#include "IWindow.hpp"
#include "GraphicsManager.hpp"

//class WebGPUGraphicsManager: public GraphicsManager {
//public:
//    explicit WebGPUGraphicsManager(IWindow *w): GraphicsManager(std::shared_ptr<IWindow>{w}), mContext{0} {}
//    int Initialize() override;
//    void Finalize() override;
//    ~WebGPUGraphicsManager() override = default;
//
//protected:
//    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE mContext;
//
//    void SwapFrame() override {
//        const auto& clearColor = mWindow->GetClearColor();
//        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
//        glClear(GL_COLOR_BUFFER_BIT);
//    };
//};

class WebGPUGraphicsManager: public GraphicsManager {
public:
    explicit WebGPUGraphicsManager(IWindow *w): GraphicsManager{std::shared_ptr<IWindow>{w}}, mInstance{},
        mDevice{std::make_shared<WebGPUDevice>()}, mSurface{std::make_shared<WebGPUSurface>()} {}
    int Initialize() override;
    void Finalize() override;
    ~WebGPUGraphicsManager() override = default;

protected:
    WGPUInstance mInstance;
    std::shared_ptr<WebGPUDevice> mDevice;
    std::shared_ptr<WebGPUSurface> mSurface;
    int InitInstance();
    int InitContext();
    void ReleaseInstance();

    void SwapFrame() override {
        const auto& clearColor = mWindow->GetClearColor();
    };
};
