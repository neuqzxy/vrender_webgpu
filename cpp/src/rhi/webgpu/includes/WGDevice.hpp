#pragma once

#include <emscripten/html5_webgpu.h>

class WGDevice {
public:
    WGDevice(): mDevice{nullptr}, mAdapter{nullptr} {}
    int Initialize(WGPUInstance instance);
    void Finalize();
    [[nodiscard]] WGPUDevice GetNativeDevice() const {
        return mDevice;
    }
    [[nodiscard]] WGPUAdapter GetNativeAdapter() const {
        return mAdapter;
    }

    WGPUQueue GetQueue();
protected:
    WGPUAdapter RequestAdapter(WGPUInstance instance, WGPURequestAdapterOptions const *options);
    WGPUDevice RequestDevice(WGPUAdapter adapter, WGPUDeviceDescriptor const * descriptor);
    WGPUDevice mDevice;
    WGPUAdapter mAdapter;
};
