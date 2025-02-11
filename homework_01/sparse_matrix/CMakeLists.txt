# set(SRCS "src/sparse_matrix.cpp;src/sparse_matrix_COO.cpp;src/sparse_matrix_CSR.cpp")
set(INCLUDE_DIRS "include")

add_library(sparse_matrix INTERFACE)
target_include_directories(sparse_matrix INTERFACE ${INCLUDE_DIRS})
target_link_libraries(sparse_matrix INTERFACE cxx_setup)

add_subdirectory(tests)