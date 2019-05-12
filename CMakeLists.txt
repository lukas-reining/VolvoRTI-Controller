cmake_minimum_required(VERSION 3.7.2)
project(RTIController)

set(CMAKE_C_STANDARD 11)

add_executable(RTIController src/RTIController.c include/Volvo_RTI.h src/RaspberryRTI.c include/Controller_Settings.h include/RTI_Settings.h src/RTI_Settings.c include/RaspberryRTI.h)

target_link_libraries(RTIController wiringPi)