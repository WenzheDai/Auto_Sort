project(motor)

set(HEADER_FILES
        motorDriver.h
        motor_control.h
        thread_motor.h
        )

set(SOURCE_FILES
        motorDriver.cpp
        motor_control.cpp
        thread_motor.cpp
        )

add_library(motor STATIC ${SOURCE_FILES} ${HEADER_FILES})
#target_link_libraries(motor motor Google_tests)