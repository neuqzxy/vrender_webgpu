#include "WebGPUCommandBuffer.hpp"

int WebGPUCommandBuffer::Initialize(WGPUInstance instance) {

}

void WebGPUCommandBuffer::Finalize() {}

void WebGPUCommandBuffer::Reset() {
    for(auto cb : mCommandBuffers){
        wgpuCommandBufferRelease(cb);
    }
    mCommandBuffers.clear();
}

void WebGPUCommandBuffer::Begin(const std::shared_ptr<WebGPUDevice> &device) {
    mCurrentCommandEncoder = wgpuDeviceCreateCommandEncoder(device->GetNativeDevice(), nullptr);
}

void WebGPUCommandBuffer::End() {
    mCommandBuffers.push_back(wgpuCommandEncoderFinish(mCurrentCommandEncoder,nullptr));
    wgpuCommandEncoderRelease(mCurrentCommandEncoder);
}

void WebGPUCommandBuffer::BeginRendering(const WGPURenderPassDescriptor *descriptor) {
    mCurrentRenderPassEncoder = wgpuCommandEncoderBeginRenderPass(mCurrentCommandEncoder,descriptor);
}

void WebGPUCommandBuffer::EndRendering() {
    wgpuRenderPassEncoderRelease(mCurrentRenderPassEncoder);
}
