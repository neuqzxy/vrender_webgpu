#pragma once

#include <emscripten/html5_webgpu.h>
#include <string>
#include "WGDevice.hpp"

class WGSurface {
public:
    explicit WGSurface(uint32_t w = 600, uint32_t h = 600): mSurface{nullptr}, mWidth{w}, mHeight{h} {}
    int Initialize(WGPUInstance instance, const std::string &id, std::shared_ptr<WGDevice> device);
    void Finalize();

    WGPUSurfaceTexture GetCurrentTexture();

    void Resize(uint32_t w, uint32_t h);

protected:
    WGPUSurface mSurface;
    uint32_t mWidth, mHeight;
};