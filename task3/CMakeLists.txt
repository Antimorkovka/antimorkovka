cmake_minimum_required (VERSION 2.6)
project (rational)
add_library (rational rational.cpp)
install (TARGETS rational DESTINATION lib)
install (FILES rational.h DESTINATION include)

