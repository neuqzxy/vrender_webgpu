import createModule from './wasm/vrender_webgpu.js';

export async function abc() {
  createModule().then((Module: any) => {
    function r() {
      console.log('加载完成 Module', Module);
      console.log('aaaaaa', Module._getNum());
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
