#pragma once

#include <vector>
#include "IWindow.hpp"
#include "Vector.hpp"

class BrowserWindow final: public IWindow {
public:
    BrowserWindow(): IWindow({1.f, 0.f, 0.f, 1.f}, sCanvasPrefix+std::to_string(mId), 0, 0),
        mDestroyed{false}, mDpr{1.f} {};
    ~BrowserWindow() override = default;
    int Init(const WindowConf &conf) override; // 会初始化并创建canvas
    int InitWithoutCreate(const WindowConf &conf); // 并不创建canvas，只是绑定canvas
    void Destroy() override;
    void Resize(const int &width, const int &height) override;
    void GetSize(int *width, int *height) override;
    inline int GetId() override;
    inline void SetId(const int &id) override;
    void SwapFrame() override;
    inline bool IsDestroyed() override;
    void SetClearColor(float r, float g, float b, float a) override;
    [[nodiscard]] const Vec4f& GetClearColor() const override;

    inline std::string GetCanvasId() override;
    void SetCanvasId(std::string canvasId);

    float GetDpr() override;

private:
//    int InitResourceManager(const std::vector<std::string> &shaderLists);
    float mDpr;
    std::string mTitle;
    bool mDestroyed;


    static std::string sCanvasPrefix;
};