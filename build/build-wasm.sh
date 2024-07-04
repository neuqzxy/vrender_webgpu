cur_dir=$(pwd)
cd ./cpp
# 添加环境变量
export EMCC_DEBUG=0
export WASMENV=1
source ./emsdk/emsdk_env.sh

#添加cmake_build_wasm目录
rm -rf ./cmake_build_wasm
mkdir cmake_build_wasm

# cmake
cd cmake_build_wasm
emcmake cmake -DCMAKE_C_COMPILER="$cur_dir/cpp/emsdk/upstream/emscripten/emcc" \
-DCMAKE_CXX_COMPILER="$cur_dir/cpp/emsdk/upstream/emscripten/em++" \
-DCMAKE_TOOLCHAIN_FILE="$cur_dir/cpp/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake" \
-DCMAKE_CROSSCOMPILING="$cur_dir/cpp/emsdk/node/18.20.3_64bit/bin/node" \
-DCMAKE_BUILD_TYPE=Release ..

# make
emmake make -j 12

# move
script_path=$(cd "$(dirname "$0")"; pwd)
p_dir=$(dirname "$script_path")
pp_dir=$(dirname "$p_dir")

file_path="$p_dir/dist/*"
target_path="$pp_dir/lib/wasm"
cp -r $file_path $target_path
