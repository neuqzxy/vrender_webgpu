#include "includes/WebGPUGraphicsManager.hpp"
#include "Output.hpp"

int WebGPUGraphicsManager::Initialize() {
    InitInstance();
    if (mInstance) {
        SUCCESS_PRINT("初始化webgpu instance成功");
        mDevice->Initialize(mInstance);
        mSurface->Initialize(mInstance, "#" + mWindow->GetCanvasId());
    }
    return 0;
}

void WebGPUGraphicsManager::Finalize() {
}

int WebGPUGraphicsManager::InitInstance() {
    WGPUInstanceDescriptor desc {
            .nextInChain = nullptr,
    };

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
