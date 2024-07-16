#pragma once

#include "GraphicsManager.hpp"

class WebGPUGraphicsManager: public GraphicsManager {
public:
    int Initialize() override;
    void Finalize() override;
    ~WebGPUGraphicsManager() override = default;
};
