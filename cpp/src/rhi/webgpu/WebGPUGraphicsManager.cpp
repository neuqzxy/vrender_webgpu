#include "WebGPUGraphicsManager.hpp"
#include "WGRenderPass.hpp"
#include "WGTexture.hpp"
#include "Output.hpp"

int WebGPUGraphicsManager::Initialize() {
    InitInstance();
    if (mInstance) {
        SUCCESS_PRINT("初始化webgpu instance成功");
        mDevice->Initialize(mInstance);
        mCommandBuffer->Initialize(mInstance, mDevice);
        mSurface->Initialize(mInstance, "#" + mWindow->GetCanvasId(), mDevice);

        mCommandBuffer->Begin(mDevice);
        SUCCESS_PRINT("begin");
        WGTexture texture{};
        texture.Initialize(mSurface->GetCurrentTexture().texture);
        const auto renderPass{new WGRenderPass(texture.GetTextureView())};
        renderPass->Initialize(mInstance);
        SUCCESS_PRINT("renderPass");
        mCommandBuffer->BeginRendering(&renderPass->mRenderPass);
        SUCCESS_PRINT("BeginRendering");
        mCommandBuffer->EndRendering();
        SUCCESS_PRINT("EndRendering");
        mCommandBuffer->End();
        mCommandBuffer->Submit();
    }
    return 0;
}

void WebGPUGraphicsManager::Finalize() {
}

int WebGPUGraphicsManager::InitInstance() {
//    WGPUInstanceDescriptor desc {
//            .nextInChain = nullptr,
//    };

    // see: https://github.com/emscripten-core/emscripten/issues/19349
    mInstance = wgpuCreateInstance(nullptr);
    if (!mInstance) {
        ERROR_PRINT("获取webgpu context发生错误");
        return 1;
    }
    return 0;
}

int WebGPUGraphicsManager::InitContext() {
    return 0;
}

void WebGPUGraphicsManager::ReleaseInstance() {
    if (mInstance != nullptr) {
        wgpuInstanceRelease(mInstance);
        mInstance = nullptr;
    }
}
