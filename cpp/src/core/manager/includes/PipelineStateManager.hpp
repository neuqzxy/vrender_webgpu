#pragma once

class PipelineStateManager {
public:
    PipelineStateManager() = default;
    virtual ~PipelineStateManager() = 0;
    virtual int Initialize();
    virtual void Finalize();
};
