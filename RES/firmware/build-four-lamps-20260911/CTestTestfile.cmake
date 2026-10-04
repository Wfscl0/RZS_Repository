# CMake generated Testfile for 
# Source directory: C:/Users/ABC/Desktop/RZS_Repository/RES/firmware
# Build directory: C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/build-four-lamps-20260911
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(si4463_transport "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/build-four-lamps-20260911/test_si4463_transport.exe")
set_tests_properties(si4463_transport PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;50;add_test;C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;0;")
add_test(si4463_half_duplex_timing "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/build-four-lamps-20260911/test_si4463_link_timing.exe")
set_tests_properties(si4463_half_duplex_timing PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;53;add_test;C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;0;")
add_test(bridge_stream_framing "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/build-four-lamps-20260911/test_bridge_stream.exe")
set_tests_properties(bridge_stream_framing PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;57;add_test;C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;0;")
add_test(radio_stop_bench "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/build-four-lamps-20260911/test_radio_stop_bench.exe")
set_tests_properties(radio_stop_bench PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;62;add_test;C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;0;")
add_test(uart_transport_recovery "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/build-four-lamps-20260911/test_uart_transport.exe")
set_tests_properties(uart_transport_recovery PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;66;add_test;C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;0;")
add_test(protocol "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/build-four-lamps-20260911/test_res_protocol.exe")
set_tests_properties(protocol PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;69;add_test;C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;0;")
add_test(remote_state_machine "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/build-four-lamps-20260911/test_res_remote.exe")
set_tests_properties(remote_state_machine PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;73;add_test;C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;0;")
add_test(four_lamp_contract "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/build-four-lamps-20260911/test_res_indicators.exe")
set_tests_properties(four_lamp_contract PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;77;add_test;C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;0;")
add_test(four_lamp_two_endpoint_link "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/build-four-lamps-20260911/test_res_lamp_link.exe")
set_tests_properties(four_lamp_two_endpoint_link PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;81;add_test;C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;0;")
add_test(ina226_diagnostics "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/build-four-lamps-20260911/test_ina226.exe")
set_tests_properties(ina226_diagnostics PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;85;add_test;C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;0;")
add_test(vehicle_state_machine "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/build-four-lamps-20260911/test_res_vehicle.exe")
set_tests_properties(vehicle_state_machine PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;89;add_test;C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;0;")
