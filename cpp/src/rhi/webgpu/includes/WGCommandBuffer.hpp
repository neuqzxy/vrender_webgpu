#pragma once

#include <vector>
#include <emscripten/html5_webgpu.h>
#include "WGDevice.hpp"
#include "WGCommandQueue.hpp"

class WGCommandBuffer {
public:
    WGCommandBuffer(): mCurrentCommandEncoder{nullptr}, mCurrentRenderPassEncoder{nullptr}, mCommandBuffers{},
        mCommandQueue{std::make_unique<WGCommandQueue>()} {}

    int Initialize(WGPUInstance instance, const std::shared_ptr<WGDevice> &device);
    void Finalize();

    void Reset();
    void Begin(const std::shared_ptr<WGDevice> &device);
    void End();

    void Submit();

    void BeginRendering(const WGPURenderPassDescriptor *descriptor);
    void EndRendering();
protected:
    WGPUCommandEncoder mCurrentCommandEncoder;
    WGPURenderPassEncoder mCurrentRenderPassEncoder;
    std::vector<WGPUCommandBuffer> mCommandBuffers;
    std::unique_ptr<WGCommandQueue> mCommandQueue;
};
