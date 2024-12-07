set(SRCS "src/sparse_matrix_COO.cpp")
set(INCLUDE_DIRS "include")

add_library(sparse_matrix STATIC ${SRCS})
target_include_directories(sparse_matrix PUBLIC ${INCLUDE_DIRS})
target_link_libraries(sparse_matrix PUBLIC cxx_setup)

add_subdirectory(tests)