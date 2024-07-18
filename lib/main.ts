import createModule from './wasm/vrender_webgpu.js';

export async function abc() {
  createModule().then((Module: any) => {
    function r() {
      console.log('加载完成 Module', Module);
      console.log('aaaaaa', Module._getNum());
      console.time('创建canvas生成上下文');
      const window = new Module.BrowserWindow();
      window.Init({ width: 600, height: 600, title: 'abc' });
      // console.log(Module.IWindowPtr._constructor);
      const graphicManager = new Module.OpenGLGraphicsManager(window);
      console.log(window, graphicManager);
      graphicManager.Initialize();
      // console.log(Module, new Module.Window({}));
      
      // const window = Module._createBrowserWindow(0, 0, 600, 600);
      // Module._setClearColor(window, 1, 0, 1, 1);
      // Module._initContext(window);
      console.timeEnd('创建canvas生成上下文');
    }
    if (Module.isInitialized()) {
      // console.log('同步');
      r();
    } else {
      console.error('加载wasm发生错误')
      // Module.addInitializationCb(function() {
      //   console.log('异步');
      //   r();
      // });
    }
  })
  console.log('abc');
}

console.log(abc);
