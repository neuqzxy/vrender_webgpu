#include <semaphore>
#include <emscripten.h>
#include "WebGPUDevice.hpp"
#include "Output.hpp"

int WebGPUDevice::Initialize(WGPUInstance instance) {
    WGPURequestAdapterOptions adapterOpts{
            .nextInChain = nullptr,
            .compatibleSurface = nullptr,
            .powerPreference = WGPUPowerPreference_HighPerformance,
            .backendType = WGPUBackendType_WebGPU,
            .forceFallbackAdapter = false,
            .compatibilityMode = false
    };
    mAdapter = RequestAdapter(instance, &adapterOpts);
    if (!mAdapter) {
        return 1;
    }
    SUCCESS_PRINT("获取adapter成功");

    WGPUDeviceDescriptor deviceDesc{
            .nextInChain = nullptr,
            .label = "VRender WGPU device",
            .requiredFeatureCount = 0,
            .defaultQueue = {
                    .nextInChain = nullptr,
                    .label = "VRender Default queue"
            }
    };
    mDevice = RequestDevice(mAdapter,&deviceDesc);
    if (!mDevice) {
        return 2;
    }
    SUCCESS_PRINT("获取device成功");

    return 0;
}

void WebGPUDevice::Finalize() {
    if (mAdapter != nullptr) {
        wgpuAdapterRelease(mAdapter);
    }
    if (mDevice != nullptr) {
        wgpuDeviceRelease(mDevice);
    }
}

WGPUAdapter WebGPUDevice::RequestAdapter(WGPUInstance instance, const WGPURequestAdapterOptions *options) {
    struct UserData {
        WGPUAdapter adapter = nullptr;
        bool requestEnded = false;
        std::binary_semaphore sem{0};
    };
    UserData userData;
    // Callback called by wgpuInstanceRequestAdapter when the request returns
    // This is a C++ lambda function, but could be any function defined in the
    // global scope. It must be non-capturing (the brackets [] are empty) so
    // that it behaves like a regular C function pointer, which is what
    // wgpuInstanceRequestAdapter expects (WebGPU being a C API). The workaround
    // is to convey what we want to capture through the pUserData pointer,
    // provided as the last argument of wgpuInstanceRequestAdapter and received
    // by the callback as its last argument.
    auto onAdapterRequestEnded = [](WGPURequestAdapterStatus status, WGPUAdapter adapter, char const * message, void * pUserData) {
        UserData& userData = *reinterpret_cast<UserData*>(pUserData);
        if (status == WGPURequestAdapterStatus_Success) {
            userData.adapter = adapter;
        } else {
            ERROR_PRINT("获取 WebGPU adapter 失败1");
        }
        userData.requestEnded = true;
        userData.sem.release();
    };

    // Call to the WebGPU request adapter procedure
    wgpuInstanceRequestAdapter(
            instance /* equivalent of navigator.gpu */,
            options,
            onAdapterRequestEnded,
            (void*)&userData
    );
    emscripten_sleep(100);
    userData.sem.acquire();
    if (!userData.requestEnded) {
        ERROR_PRINT("获取 WebGPU adapter 失败2");
    }

    return userData.adapter;
}

WGPUDevice WebGPUDevice::RequestDevice(WGPUAdapter adapter, const WGPUDeviceDescriptor *descriptor) {
    struct UserData {
        WGPUDevice device = nullptr;
        bool requestEnded = false;
        std::binary_semaphore sem{0};
    };
    UserData userData;

    auto onDeviceRequestEnded = [](WGPURequestDeviceStatus status, WGPUDevice device, char const * message, void * pUserData) {
        UserData& userData = *reinterpret_cast<UserData*>(pUserData);
        if (status == WGPURequestDeviceStatus_Success) {
            userData.device = device;
        } else {
            ERROR_PRINT("获取 WebGPU device 失败1");
        }
        userData.requestEnded = true;
        userData.sem.release();
    };

    wgpuAdapterRequestDevice(
            adapter,
            descriptor,
            onDeviceRequestEnded,
            (void*)&userData
    );
    emscripten_sleep(300);
    userData.sem.acquire();
    if (!userData.requestEnded) {
        ERROR_PRINT("获取 WebGPU device 失败2");
    }

    return userData.device;
}

WGPUQueue WebGPUDevice::GetQueue() {
    return wgpuDeviceGetQueue(mDevice);
}
