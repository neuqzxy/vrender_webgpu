#pragma once

#include <emscripten/html5_webgpu.h>
#include "WGDevice.hpp"
#include "WGSurface.hpp"
#include "IWindow.hpp"
#include "GraphicsManager.hpp"
#include "WGCommandBuffer.hpp"

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
        mDevice{std::make_shared<WGDevice>()}, mSurface{std::make_shared<WGSurface>()}, mCommandBuffer{std::make_shared<WGCommandBuffer>()} {}
    int Initialize() override;
    void Finalize() override;
    ~WebGPUGraphicsManager() override = default;

protected:
    WGPUInstance mInstance;
    std::shared_ptr<WGDevice> mDevice;
    std::shared_ptr<WGSurface> mSurface;
    std::shared_ptr<WGCommandBuffer> mCommandBuffer;
    int InitInstance();
    int InitContext();
    void ReleaseInstance();

    void SwapFrame() override {
        const auto& clearColor = mWindow->GetClearColor();
    };
};
