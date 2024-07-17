#pragma once

#include <memory>
#include "IWindow.hpp"

class GraphicsManager {
public:
    explicit GraphicsManager(std::shared_ptr<IWindow> &window): mWindow{window} {};
    virtual ~GraphicsManager() = default;
    virtual int Initialize() = 0;
    virtual void Finalize() = 0;
protected:
    virtual void SwapFrame() = 0;
    std::shared_ptr<IWindow> mWindow;
};
