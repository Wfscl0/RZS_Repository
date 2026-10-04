# CMake generated Testfile for 
# Source directory: C:/Users/ABC/Desktop/RZS_Repository/RES/firmware
# Build directory: C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/build-four-lamps-20260910
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(protocol "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/build-four-lamps-20260910/test_res_protocol.exe")
set_tests_properties(protocol PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;49;add_test;C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;0;")
add_test(remote_state_machine "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/build-four-lamps-20260910/test_res_remote.exe")
set_tests_properties(remote_state_machine PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;53;add_test;C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;0;")
add_test(four_lamp_contract "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/build-four-lamps-20260910/test_res_indicators.exe")
set_tests_properties(four_lamp_contract PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;57;add_test;C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;0;")
add_test(ina226_diagnostics "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/build-four-lamps-20260910/test_ina226.exe")
set_tests_properties(ina226_diagnostics PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;61;add_test;C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;0;")
add_test(vehicle_state_machine "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/build-four-lamps-20260910/test_res_vehicle.exe")
set_tests_properties(vehicle_state_machine PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;65;add_test;C:/Users/ABC/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;0;")
