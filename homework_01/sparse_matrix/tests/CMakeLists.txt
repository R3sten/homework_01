if(BUILD_TESTING)
    add_executable(sparse_matrix_COO_test sparse_matrix_COO_test.cpp)
    target_link_libraries(sparse_matrix_COO_test PRIVATE GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(sparse_matrix_COO_test)
endif()