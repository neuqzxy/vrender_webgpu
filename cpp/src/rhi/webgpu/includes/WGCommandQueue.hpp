#pragma once

#include <emscripten/html5_webgpu.h>
#include "WGDevice.hpp"
#include <memory>

class WGCommandQueue {
public:
    WGCommandQueue(): mQueue{nullptr} {}
    int Initialize(WGPUInstance instance, const std::shared_ptr<WGDevice> &device);
    void Finalize();

    [[nodiscard]] WGPUQueue GetNativeQueue() const {
        return mQueue;
    }

protected:
    WGPUQueue mQueue;
};
