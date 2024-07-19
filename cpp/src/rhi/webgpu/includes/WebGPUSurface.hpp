#pragma once

#include <emscripten/html5_webgpu.h>
#include <string>

class WebGPUSurface {
public:
    WebGPUSurface(): mSurface{nullptr} {}
    int Initialize(WGPUInstance instance, const std::string &id);
    void Finalize();

protected:
    WGPUSurface mSurface;
};