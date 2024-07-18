//
// Created by 周欣宇 on 2/12/22.
//
#ifndef EM_PORT_API
#   if defined(__EMSCRIPTEN__)
#       include <emscripten.h>
#       include <emscripten/bind.h>

#       if defined(__cplusplus)
#           define EM_PORT_API(rettype) extern "C" rettype EMSCRIPTEN_KEEPALIVE
#       else
#           define EM_PORT_API(rettype) rettype EMSCRIPTEN_KEEPALIVE
#       endif
#   else
#       if defined(__cplusplus)
#           define EM_PORT_API(rettype) extern "C" rettype
#       else
#           define EM_PORT_API(rettype) rettype
#       endif
#   endif
#endif
#include <cstddef>
#include <cstdlib>
#include "Window.hpp"
#include "OpenGLGraphicsManager.hpp"

extern "C" {
  /* window API */
  // // 创建一个浏览器窗口，会自动创建一个canvas
//  EM_PORT_API(BrowserWindow*) createBrowserWindow(float x, float y, float w, float h);
//  // 使用已有的canvas创建一个Window对象
//  EM_PORT_API(BrowserWindow*) createBrowserWindowWithCanvas(BrowserWindow *window, float w, float h, const char *id);
//  // 初始化上下文，会设置clearColor
//  EM_PORT_API(void) initContext(BrowserWindow *window, const char *id);
//  // 激活当前的window，也就是将上下文设置到当前window上（这个逻辑和OpenGL类似emscripten_webgl_make_context_current，和WebGL逻辑不同）
//  EM_PORT_API(void) active(BrowserWindow *window);
//  // 设置window的ClearColor
//  EM_PORT_API(void) setClearColor(BrowserWindow *window, float r, float g, float b, float a);
  /* window API */

  EM_PORT_API(int) getNum();
  EM_PORT_API(unsigned char*) createBuffer(size_t size);
  EM_PORT_API(void) freeBuffer(void *ptr);
  EM_PORT_API(void) callJS(void);
  extern void testExternalJSMethod();
}

extern "C" {
    EMSCRIPTEN_BINDINGS(WindowConf) {
        emscripten::value_object<WindowConf>("WindowConf")
                .field("width", & WindowConf::width)
                .field("height", &WindowConf::height)
                .field("title", &WindowConf::title);
    }
    EMSCRIPTEN_BINDINGS(IWindow) {
        emscripten::class_<IWindow>("IWindow");
//        emscripten::class_<std::shared_ptr<IWindow>>("IWindowPtr");
//        emscripten::class_<std::shared_ptr<BrowserWindow>>("IBrowserWindowPtr");
    }
    EMSCRIPTEN_BINDINGS(BrowserWindow) {
        emscripten::class_<BrowserWindow, emscripten::base<IWindow>>("BrowserWindow")
                .constructor<>()
                .function("Init", &BrowserWindow::Init)
                .function("InitWithoutCreate", &BrowserWindow::InitWithoutCreate)
                .function("SetClearColor", &BrowserWindow::SetClearColor);
    }
    EMSCRIPTEN_BINDINGS(OpenGLGraphicsManager) {
        emscripten::class_<OpenGLGraphicsManager>("OpenGLGraphicsManager")
                .constructor<BrowserWindow *>()
                .function("Initialize", &OpenGLGraphicsManager::Initialize);
    }
//  EM_PORT_API(BrowserWindow*) createBrowserWindow(float x, float y, float w, float h) {
//    auto *window = new BrowserWindow();
//    window->Init({ w, h, "这是标题" });
//    return window;
//  }
//
//  EM_PORT_API(BrowserWindow*) createBrowserWindowWithCanvas(BrowserWindow *window, float w, float h, const char *id) {
//    window->InitWithoutCreate({w, h, "这是标题"});
//    window->SetCanvasId(std::string(id));
//  }
//
//  EM_PORT_API(void) initContext(BrowserWindow *window, const char *id) {
//    if (id != nullptr) {
//      window->SetCanvasId(std::string(id));
//    }
////    window->InitContext();
//  }
//
//  EM_PORT_API(void) active(BrowserWindow *window) {
////    window->MakeContextCurrent();
//  }
//
//  EM_PORT_API(void) setClearColor(BrowserWindow *window, float r, float g, float b, float a) {
//    window->SetClearColor(r, g, b, a);
//  }

  EM_PORT_API(int) getNum() {
    return 6;
  }
  EM_PORT_API(unsigned char*) createBuffer(size_t size) {
    return (unsigned char*)malloc(size);
  }
  EM_PORT_API(void) freeBuffer(void *ptr) {
    return free(ptr);
  }
  EM_PORT_API(void) callJS(void) {
      testExternalJSMethod();
  }
}