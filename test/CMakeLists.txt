set(random_test_srcs random_hao_test.cpp test_all.cpp)

add_executable(randomtest ${random_test_srcs})

target_link_libraries(randomtest randomhao)

target_link_libraries(randomtest ${lib_all})

install(TARGETS randomtest  DESTINATION test)
