#pragma once

#include <emscripten/html5_webgpu.h>
#include "WebGPUDevice.hpp"
#include <memory>

class WebGPUCommandQueue {
    WebGPUCommandQueue(): mQueue{nullptr} {}
    int Initialize(WGPUInstance instance, const std::shared_ptr<WebGPUDevice> &device);
    void Finalize();

protected:
    WGPUQueue mQueue;
};
