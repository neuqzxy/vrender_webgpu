#pragma once

#include <emscripten/html5_webgpu.h>

class WGTexture {
public:
    WGTexture(): mTexture{nullptr} {}
    int Initialize(WGPUTexture texture);
    void Finalize();

    WGPUTextureView GetTextureView();

protected:
    WGPUTexture mTexture;
};
