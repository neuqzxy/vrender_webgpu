#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include "Shader.hpp"
#include "Output.hpp"

class PipelineStateManager {
public:
    PipelineStateManager() = default;
    virtual ~PipelineStateManager() = 0;
    virtual int Initialize() = 0;
    virtual void Finalize() = 0;
};
