#include "WebGPUSurface.hpp"
#include "Output.hpp"

int WebGPUSurface::Initialize(WGPUInstance instance, const std::string &id) {
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
    return 0;
}

void WebGPUSurface::Finalize() {
    if (mSurface != nullptr) {
        wgpuSurfaceRelease(mSurface);
    }
}
