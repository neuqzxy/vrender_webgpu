#pragma once

#include "Struct.hpp"

class IWindow {
public:
    IWindow(): mId{sId++} {}
    virtual ~IWindow() = default;
    virtual int Init(const WindowConf &conf) = 0;
    virtual void Destroy() = 0;
    virtual void Resize(const int &width, const int &height) = 0;
    virtual void GetSize(int *width, int *height) = 0;
    virtual void SwapFrame() = 0;
    virtual bool IsDestroyed() = 0;
    virtual int GetId() = 0;
    virtual void SetId(const int &id) = 0;
    virtual void SetClearColor(float r, float g, float b, float a) = 0;
    virtual float GetDpr() = 0;

protected:
    int mId;
private:
    static int sId;
};