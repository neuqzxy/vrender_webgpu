#include "Window.hpp"
// #include <GLES2/gl2.h>
#include <cstring>
#include <vector>
#include <thread>

extern "C" {
//emscripten::val window = emscripten::val::global("window");
extern void createWindow(float x, float y, float w, float h, int id);
}

std::string BrowserWindow::sCanvasPrefix{"vrender_"};

int IWindow::sId = 0;

int BrowserWindow::Init(const WindowConf &conf) {
    createWindow(0, 0, conf.width, conf.height, mId);
    mWidth = conf.width;
    mHeight = conf.height;

    emscripten::val window = emscripten::val::global("window");
    mDpr = window["devicePixelRatio"].as<float>();
    return 0;
}

int BrowserWindow::InitWithoutCreate(const WindowConf &conf) {
    mWidth = conf.width;
    mHeight = conf.height;
    emscripten::val window = emscripten::val::global("window");
    mDpr = window["devicePixelRatio"].as<float>();

    return 0;
}

void BrowserWindow::InitContext() {
    EmscriptenWebGLContextAttributes attrs{};
    attrs.explicitSwapControl = 0;
    attrs.depth = 1;
    attrs.stencil = 1;
    attrs.antialias = 1;
    attrs.majorVersion = 2;
    attrs.minorVersion = 0;

    mContext = emscripten_webgl_create_context(mCanvasId.c_str(), &attrs);
    if (mContext == 0) {
        throw std::runtime_error("获取context发生错误");
    }
    MakeContextCurrent();
    return;

//    InitResourceManager({"default"});

    // glClearColor(mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a);
    // glClear(GL_COLOR_BUFFER_BIT);
}

void BrowserWindow::MakeContextCurrent() const {
    emscripten_webgl_make_context_current(mContext);
}

void BrowserWindow::Destroy() {
    mDestroyed = true;
}

void BrowserWindow::Resize(const int &width, const int &height) {
    mWidth = width; mHeight = height;
}

void BrowserWindow::GetSize(int *width, int *height) {
    *width = mWidth; *height = mHeight;
}

bool BrowserWindow::IsDestroyed() {
    return mDestroyed;
}

void BrowserWindow::SetClearColor(float r, float g, float b, float a) {
    mClearColor.r = r;
    mClearColor.g = g;
    mClearColor.b = b;
    mClearColor.a = a;
}

int BrowserWindow::GetId() {
    return mId;
}

void BrowserWindow::SetId(const int &id) {
    mId = id;
}

void BrowserWindow::SetCanvasId(std::string canvasId) {
    mCanvasId = std::move(canvasId);
}

std::string BrowserWindow::GetCanvasId() {
    return mCanvasId;
}

void BrowserWindow::SwapFrame() {
    return;
}

float BrowserWindow::GetDpr() {
    return mDpr;
}