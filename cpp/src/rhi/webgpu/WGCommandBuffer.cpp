#include "WGCommandBuffer.hpp"
#include "Output.hpp"

int WGCommandBuffer::Initialize(WGPUInstance instance, const std::shared_ptr<WGDevice> &device) {
    mCommandQueue->Initialize(instance, device);
    return 0;
}

void WGCommandBuffer::Finalize() {}

void WGCommandBuffer::Reset() {
    for(auto cb : mCommandBuffers){
        wgpuCommandBufferRelease(cb);
    }
    mCommandBuffers.clear();
}

void WGCommandBuffer::Begin(const std::shared_ptr<WGDevice> &device) {
    mCurrentCommandEncoder = wgpuDeviceCreateCommandEncoder(device->GetNativeDevice(), nullptr);
    if (mCurrentCommandEncoder == nullptr) {
        ERROR_PRINT("创建encoder失败");
    }
}

void WGCommandBuffer::End() {
    mCommandBuffers.push_back(wgpuCommandEncoderFinish(mCurrentCommandEncoder,nullptr));
    wgpuCommandEncoderRelease(mCurrentCommandEncoder);
}

void WGCommandBuffer::BeginRendering(const WGPURenderPassDescriptor *descriptor) {
    mCurrentRenderPassEncoder = wgpuCommandEncoderBeginRenderPass(mCurrentCommandEncoder, descriptor);
}

void WGCommandBuffer::EndRendering() {
    wgpuRenderPassEncoderEnd(mCurrentRenderPassEncoder);
}

void WGCommandBuffer::Submit() {
    wgpuQueueSubmit(mCommandQueue->GetNativeQueue(), mCommandBuffers.size(), mCommandBuffers.data());
}
