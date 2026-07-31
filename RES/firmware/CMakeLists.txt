cmake_minimum_required(VERSION 3.16)
project(res_firmware_tests C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Werror -pedantic)
endif()

add_library(res_protocol
    shared/src/res_protocol.c
    shared/src/res_can_contract.c
)
target_include_directories(res_protocol PUBLIC shared/include)

add_library(res_remote
    remote_g0b1/Core/Src/res_remote_app.c
)
target_include_directories(res_remote PUBLIC
    shared/include
    remote_g0b1/Core/Inc
)
target_link_libraries(res_remote PUBLIC res_protocol)

add_library(res_vehicle
    vehicle_g0b1/Core/Src/res_vehicle_app.c
)
target_include_directories(res_vehicle PUBLIC
    shared/include
    vehicle_g0b1/Core/Inc
)
target_link_libraries(res_vehicle PUBLIC res_protocol)

# Compile the STM8 bridge with API stubs to catch portable C syntax/regressions.
# The final binary still requires IAR for STM8 and Ebyte's vendor SDK.
add_library(res_bridge_syntax STATIC
    radio_bridge_stm8/res_bridge_main.c
    radio_bridge_stm8/res_bridge_callback.c
)
target_include_directories(res_bridge_syntax PRIVATE
    tests/stm8_host_stub
    radio_bridge_stm8
)

enable_testing()
add_executable(test_res_protocol tests/test_res_protocol.c)
target_link_libraries(test_res_protocol PRIVATE res_protocol)
add_test(NAME protocol COMMAND test_res_protocol)

add_executable(test_res_remote tests/test_res_remote.c)
target_link_libraries(test_res_remote PRIVATE res_remote)
add_test(NAME remote_state_machine COMMAND test_res_remote)

add_executable(test_res_vehicle tests/test_res_vehicle.c)
target_link_libraries(test_res_vehicle PRIVATE res_vehicle)
add_test(NAME vehicle_state_machine COMMAND test_res_vehicle)
