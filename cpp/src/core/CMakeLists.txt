# set(glad_path ${PROJECT_SOURCE_DIR}/src/platform/libs/glad)

include_directories(includes)
include_directories(graphic/includes)
# include_directories(${glad_path}/include)
# include_directories(Mark/include)
# include_directories(render/include)

add_library(core Bounds.cpp main.cpp
        graphic/GraphicsManager.cpp graphic/PipelineStateManager.cpp graphic/Shader.cpp graphic/PipelineState.cpp)
# set_target_properties(core PROPERTIES
#         LINK_FLAGS "-pthread")
# target_link_libraries(core font_lib)
# add_subdirectory(test)
# enable_testing()