#pragma once

#include "PipelineStateManager.hpp"

class OpenGLPipelineStateManager: public PipelineStateManager {
public:
    int Initialize() override;
    void Finalize() override;
    ~OpenGLPipelineStateManager() override = default;
};
