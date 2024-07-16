#pragma once

#include "PipelineStateManager.hpp"

class WebGPUPipelineStateManager: public PipelineStateManager {
public:
    int Initialize() override;
    void Finalize() override;
    ~WebGPUPipelineStateManager() override = default;
};
