#pragma once

#include <emscripten/html5_webgpu.h>

class WebGPUDevice {
public:
    WebGPUDevice(): mDevice{nullptr}, mAdapter{nullptr} {}
    int Initialize(WGPUInstance instance);
    void Finalize();
    [[nodiscard]] WGPUDevice GetNativeDevice() const {
        return mDevice;
    }

    void BeginRendering();
    void EndRendering();
protected:
    WGPUAdapter RequestAdapter(WGPUInstance instance, WGPURequestAdapterOptions const *options);
    WGPUDevice RequestDevice(WGPUAdapter adapter, WGPUDeviceDescriptor const * descriptor);
    WGPUDevice mDevice;
    WGPUAdapter mAdapter;
};
