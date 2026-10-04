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
add_executable(test_si4463_transport tests/test_si4463_transport.c)
target_include_directories(test_si4463_transport PRIVATE tests/si4463_host_stub)
target_link_libraries(test_si4463_transport PRIVATE res_protocol)
add_test(NAME si4463_transport COMMAND test_si4463_transport)
add_executable(test_si4463_link_timing tests/test_si4463_link_timing.c)
target_link_libraries(test_si4463_link_timing PRIVATE res_remote res_vehicle)
add_test(NAME si4463_half_duplex_timing COMMAND test_si4463_link_timing)
add_executable(test_bridge_stream tests/test_bridge_stream.c)
target_include_directories(test_bridge_stream PRIVATE tests/stm8_host_stub radio_bridge_stm8)
target_link_libraries(test_bridge_stream PRIVATE res_protocol)
add_test(NAME bridge_stream_framing COMMAND test_bridge_stream)
add_executable(test_radio_stop_bench tests/test_radio_stop_bench.c remote_g0b1/Core/Src/res_remote_app.c)
target_include_directories(test_radio_stop_bench PRIVATE remote_g0b1/Core/Inc)
target_compile_definitions(test_radio_stop_bench PRIVATE RES_RADIO_STOP_BENCH=1)
target_link_libraries(test_radio_stop_bench PRIVATE res_protocol)
add_test(NAME radio_stop_bench COMMAND test_radio_stop_bench)
add_executable(test_uart_transport tests/test_uart_transport.c)
target_include_directories(test_uart_transport PRIVATE tests/uart_host_stub)
target_link_libraries(test_uart_transport PRIVATE res_protocol)
add_test(NAME uart_transport_recovery COMMAND test_uart_transport)
add_executable(test_res_protocol tests/test_res_protocol.c)
target_link_libraries(test_res_protocol PRIVATE res_protocol)
add_test(NAME protocol COMMAND test_res_protocol)

add_executable(test_res_remote tests/test_res_remote.c)
target_link_libraries(test_res_remote PRIVATE res_remote)
add_test(NAME remote_state_machine COMMAND test_res_remote)

add_executable(test_res_indicators tests/test_res_indicators.c)
target_link_libraries(test_res_indicators PRIVATE res_remote)
add_test(NAME four_lamp_contract COMMAND test_res_indicators)

add_executable(test_res_lamp_link tests/test_res_lamp_link.c)
target_link_libraries(test_res_lamp_link PRIVATE res_remote res_vehicle)
add_test(NAME four_lamp_two_endpoint_link COMMAND test_res_lamp_link)

add_executable(test_ina226 tests/test_ina226.c remote_g0b1/Core/Src/ina226.c)
target_include_directories(test_ina226 PRIVATE remote_g0b1/Core/Inc)
add_test(NAME ina226_diagnostics COMMAND test_ina226)

add_executable(test_res_vehicle tests/test_res_vehicle.c)
target_link_libraries(test_res_vehicle PRIVATE res_vehicle)
add_test(NAME vehicle_state_machine COMMAND test_res_vehicle)

if(WIN32)
    add_executable(res_serial_vehicle_harness tools/res_serial_vehicle_harness.c)
    target_link_libraries(res_serial_vehicle_harness PRIVATE res_protocol)
endif()
