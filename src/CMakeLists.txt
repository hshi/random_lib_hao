set(random_srcs random_hao.cpp)

add_library(randomhao STATIC ${random_srcs})

install(TARGETS randomhao  DESTINATION lib)
