#pragma once

#include <vector>
#include <emscripten/html5_webgpu.h>
#include "WebGPUDevice.hpp"

class WebGPUCommandBuffer {
public:
    WebGPUCommandBuffer(): mCurrentCommandEncoder{nullptr}, mCurrentRenderPassEncoder{nullptr}, mCommandBuffers{} {}
    int Initialize(WGPUInstance instance);
    void Finalize();

    void Reset();
    void Begin(const std::shared_ptr<WebGPUDevice> &device);
    void End();

    void BeginRendering(const WGPURenderPassDescriptor *descriptor);
    void EndRendering();
protected:
    WGPUCommandEncoder mCurrentCommandEncoder;
    WGPURenderPassEncoder mCurrentRenderPassEncoder;
    std::vector<WGPUCommandBuffer> mCommandBuffers;
};
