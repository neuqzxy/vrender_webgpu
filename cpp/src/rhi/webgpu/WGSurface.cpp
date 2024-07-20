#include "WGSurface.hpp"
#include "Output.hpp"

int WGSurface::Initialize(WGPUInstance instance, const std::string &id, std::shared_ptr<WGDevice> device) {
    // we are expecting a CSS selector string, like "#canvas", for the value of pointer
    WGPUSurfaceDescriptorFromCanvasHTMLSelector canvasDesc{
            .chain = {
                    .next = nullptr,
                    .sType = WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector
            },
            .selector = static_cast<const char* const>(id.c_str())
    };
    WGPUSurfaceDescriptor desc{
            .nextInChain = &canvasDesc.chain,
            .label = "Surface"
    };
    mSurface = wgpuInstanceCreateSurface(instance, &desc);
    if (!mSurface) {
        ERROR_PRINT("获取webgpu context发生错误");
        return 1;
    }

    WGPUTextureFormat surfaceFormat = wgpuSurfaceGetPreferredFormat(mSurface, device->GetNativeAdapter());

    wgpuSurfaceConfigure(mSurface, new WGPUSurfaceConfiguration{
            .device = device->GetNativeDevice(),
            .format = surfaceFormat,
            .usage = WGPUTextureUsage_RenderAttachment,
            .viewFormatCount = 0,
            .viewFormats = nullptr,
            .alphaMode = WGPUCompositeAlphaMode_Auto,
            .width = 600,
            .height = 600,
            .presentMode = WGPUPresentMode_Fifo,

    });
    return 0;
}

void WGSurface::Finalize() {
    if (mSurface != nullptr) {
        wgpuSurfaceRelease(mSurface);
    }
}

WGPUSurfaceTexture WGSurface::GetCurrentTexture() {
    WGPUSurfaceTexture surfaceTexture;
    wgpuSurfaceGetCurrentTexture(mSurface, &surfaceTexture);
    if (surfaceTexture.status != WGPUSurfaceGetCurrentTextureStatus_Success) {
        ERROR_PRINT("wgpuSurfaceGetCurrentTexture 调用失败");
    }
    return surfaceTexture;
}

void WGSurface::Resize(uint32_t w, uint32_t h) {
    mWidth = w;
    mHeight = h;
}
