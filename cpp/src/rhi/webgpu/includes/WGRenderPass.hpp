#pragma once

#include <emscripten/html5_webgpu.h>

class WGRenderPass {
public:
    explicit WGRenderPass(WGPUTextureView textureView) {
//        attachment.loadOp = WGPULoadOp::WGPULoadOp_Clear;
//        attachment.storeOp = WGPUStoreOp::WGPUStoreOp_Store;
////        attachment.view = view;  // to be filled out when we render
////        attachment.loadOp = WGPURenderPassColorAttachment::loadOp::Clear;
////        attachment.storeOp = wgpu::StoreOp::Store;
//        attachment.clearValue = {1, 0, 0, 1};

        mRenderPass = WGPURenderPassDescriptor{
            .nextInChain = nullptr,
            .label = "vrender webgpu render pass",
            .colorAttachmentCount = 1,
            .colorAttachments = new WGPURenderPassColorAttachment{
                    .nextInChain = nullptr,
                    .view = textureView,
                    .depthSlice = WGPU_DEPTH_SLICE_UNDEFINED,
                    .loadOp = WGPULoadOp::WGPULoadOp_Clear,
                    .storeOp = WGPUStoreOp::WGPUStoreOp_Store,
                    .clearValue = { 0.9, 0.1, 0.2, 1.0 },

            },
        };
    }
    int Initialize(WGPUInstance instance);
    void Finalize();

    WGPURenderPassDescriptor mRenderPass{};

};