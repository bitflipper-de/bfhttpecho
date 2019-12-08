set(TARGET bfhttpecho)

add_executable(${TARGET}
        http_echo.h
        http_echo.cpp
        main.cpp
        responders/GetResponder.cpp responders/GetResponder.h responders/Responder.cpp responders/Responder.h)

target_link_libraries(${TARGET}
        Qt5::Core
        Qt5::Network
)
