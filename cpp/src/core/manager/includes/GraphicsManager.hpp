#pragma once

class GraphicsManager {
public:
    GraphicsManager() = default;
    virtual ~GraphicsManager() = 0;
    virtual int Initialize();
    virtual void Finalize();
};
