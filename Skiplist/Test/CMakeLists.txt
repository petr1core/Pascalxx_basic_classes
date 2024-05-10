file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty")

add_executable(${test} ${srcs} ${hdrs})
target_link_libraries(${test} ${include} gtest ${subProj})
set_target_properties(${test} PROPERTIES FOLDER ${subProj})
