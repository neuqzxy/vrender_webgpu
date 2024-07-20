#include "WGTexture.hpp"
#include "Output.hpp"

int WGTexture::Initialize(WGPUTexture texture) {
    if (texture == nullptr) {
        ERROR_PRINT("参数texture为nullptr");
        return 1;
    }
    mTexture = texture;

    return 0;
}

void WGTexture::Finalize() {}

WGPUTextureView WGTexture::GetTextureView() {
    WGPUTextureViewDescriptor viewDescriptor;
    viewDescriptor.nextInChain = nullptr;
    viewDescriptor.label = "Surface texture view";
    viewDescriptor.format = wgpuTextureGetFormat(mTexture);
    viewDescriptor.dimension = WGPUTextureViewDimension_2D;
    viewDescriptor.baseMipLevel = 0;
    viewDescriptor.mipLevelCount = 1;
    viewDescriptor.baseArrayLayer = 0;
    viewDescriptor.arrayLayerCount = 1;
    viewDescriptor.aspect = WGPUTextureAspect_All;
    WGPUTextureView targetView = wgpuTextureCreateView(mTexture, &viewDescriptor);
    return targetView;
}
