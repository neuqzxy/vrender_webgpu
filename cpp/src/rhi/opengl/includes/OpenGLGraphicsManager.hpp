#pragma once

#include "GraphicsManager.hpp"

class OpenGLGraphicsManager: public GraphicsManager {
public:
    int Initialize() override;
    void Finalize() override;
    ~OpenGLGraphicsManager() override = default;
};
