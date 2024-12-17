#include "Window.hpp"
#include <emscripten/bind.h>
#include <vector>

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

const Vec4f& BrowserWindow::GetClearColor() const {
    return mClearColor;
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

float BrowserWindow::GetDpr() {
    return mDpr;
}