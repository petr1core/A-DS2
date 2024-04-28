set(target ${SUBPROJECT_NAME})

file(GLOB hdrs "*.h*" "../${SUBPROJECT_NAME}Lib/*.h*")
file(GLOB srcs "*.cpp")

add_library(${target} STATIC ${srcs} ${hdrs})
target_link_libraries(${target} ${LIBRARY_DEPS})
set_target_properties(${target} PROPERTIES FOLDER ${SUBPROJECT_NAME})

# LLTable main