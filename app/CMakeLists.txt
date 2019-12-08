set(TARGET bfhttpecho)

add_executable(${TARGET} main.cpp)

target_link_libraries(${TARGET}
  Qt5::Core
)
