include_directories(includes)
# 定义编译变量
if (DEFINED ENV{WASM_OUT})
    SET(WASM $ENV{WASM_OUT})
else()
    SET(WASM 1)
endif()
if (${WASM} EQUAL 1 AND DEFINED ENV{ASYNC_LOAD})
    SET(ASYNC_LOAD $ENV{ASYNC_LOAD})
else()
    SET(ASYNC_LOAD 1)
endif()
#
#SET(WASM 0)
#SET(ASYNC_LOAD 1)
if (CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    MESSAGE(wasm: ${WASM})
    MESSAGE(ASYNC_LOAD: ${ASYNC_LOAD})
    # DISABLE_EXCEPTION_CATCHING 是否禁用异常精确判断（如果不禁用0会增加100多k代码量）
    # ENVIRONMENT=web只在web环境中执行，避免引入require
    # NO_DISABLE_EXCEPTION_CATCHING用于debug
    # ASSERTIONS 用于debug
    # closure 用于代码混淆
    # WASM_ASYNC_COMPILATION 控制是否异步加载asm.js
    # PTHREAD_POOL_SIZE这是设置线程池的数量，如果不设置的话会开线程阻塞会直接阻塞主线程
    # 正式版本请使用-03优化
    add_executable(vrender_webgpu Window.cpp bridge.cpp)
    target_link_libraries(vrender_webgpu core)
    target_link_libraries(vrender_webgpu utils)
    target_link_libraries(vrender_webgpu opengl)
    target_link_libraries(vrender_webgpu webgpu)
    set_target_properties(vrender_webgpu PROPERTIES
            LINK_FLAGS "-O1                \
        -s EXPORTED_FUNCTIONS='[         \
            \"_getNum\",         \
            \"_malloc\",         \
            \"_free\",         \
            \"_freeBuffer\",         \
            \"_callJS\"]'              \
        -s 'EXPORTED_RUNTIME_METHODS=[     \
            \"ccall\",                           \
            \"cwrap\",                           \
            \"getValue\"]'                       \
        --js-library ${CMAKE_CURRENT_LIST_DIR}/library.js \
        --pre-js ${CMAKE_CURRENT_LIST_DIR}/pre.js \
        --post-js ${CMAKE_CURRENT_LIST_DIR}/post.js\
        --closure 1\
        -s EXPORT_ES6=1 \
        -s EXIT_RUNTIME=1 \
        -s MODULARIZE=1 \
        -s 'EXPORT_NAME=\"createModule\"' \
        -s WASM=${WASM} \
        -s WASM_ASYNC_COMPILATION=${ASYNC_LOAD} \
        -s FILESYSTEM=1 \
        -s FORCE_FILESYSTEM \
        -s ASSERTIONS=1 \
        -s LLD_REPORT_UNDEFINED \
        -s FULL_ES3=1 \
        -s USE_WEBGL2=1 \
        -s USE_WEBGPU=1 \
        -s EXIT_RUNTIME=1 \
        -s ASYNCIFY=1 \
        -s DISABLE_EXCEPTION_CATCHING=0 \
        -s INITIAL_MEMORY=125829120\
        -s ALLOW_MEMORY_GROWTH=1")

    #    add_subdirectory(test)
    #    enable_testing()
endif()