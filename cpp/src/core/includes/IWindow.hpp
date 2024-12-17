#pragma once

#include "Struct.hpp"
#include "Vector.hpp"
#include <string>

class IWindow {
public:
    IWindow(Vec4f clearColor, std::string canvasId, uint32_t w, uint32_t h): mId{sId++}, mClearColor{clearColor}, mCanvasId{std::move(canvasId)}, mWidth{w}, mHeight{h} {}
    virtual ~IWindow() = default;
    virtual int Init(const WindowConf &conf) = 0;
    virtual void Destroy() = 0;
    virtual void Resize(const int &width, const int &height) = 0;
    virtual void GetSize(int *width, int *height) = 0;
    virtual bool IsDestroyed() = 0;
    virtual int GetId() = 0;
    virtual void SetId(const int &id) = 0;
    virtual void SetClearColor(float r, float g, float b, float a) = 0;
    [[nodiscard]] virtual const Vec4f& GetClearColor() const = 0;
    virtual float GetDpr() = 0;
    virtual std::string GetCanvasId() = 0;

    [[nodiscard]] uint32_t GetWidth() const {
        return mWidth;
    }
    [[nodiscard]] uint32_t GetHeight() const {
        return mHeight;
    }


protected:
    int mId;
    std::string mCanvasId;
    Vec4f mClearColor;
    uint32_t mWidth;
    uint32_t mHeight;
private:
    static int sId;
};