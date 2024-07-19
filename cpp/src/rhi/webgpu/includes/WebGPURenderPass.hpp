#pragma once

#include <emscripten/html5_webgpu.h>

class WebGPURenderPass {
public:
    WebGPURenderPass() {
        WGPURenderPassColorAttachment attachment{};
        attachment.loadOp = WGPULoadOp::WGPULoadOp_Clear;
        attachment.storeOp = WGPUStoreOp::WGPUStoreOp_Store;
//        attachment.view = view;  // to be filled out when we render
//        attachment.loadOp = WGPURenderPassColorAttachment::loadOp::Clear;
//        attachment.storeOp = wgpu::StoreOp::Store;
        attachment.clearValue = {1, 0, 0, 1};

        mRenderPass = WGPURenderPassDescriptor{
            .label = "vrender webgpu render pass",
            .colorAttachmentCount = 1,
            .colorAttachments = &attachment,
        };
    }
    int Initialize(WGPUInstance instance);
    void Finalize();

    WGPURenderPassDescriptor mRenderPass{};

};