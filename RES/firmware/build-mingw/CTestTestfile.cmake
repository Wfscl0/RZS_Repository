# CMake generated Testfile for 
# Source directory: C:/Users/icemi/Desktop/RZS_Repository/RES/firmware
# Build directory: C:/Users/icemi/Desktop/RZS_Repository/RES/firmware/build-mingw
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(protocol "C:/Users/icemi/Desktop/RZS_Repository/RES/firmware/build-mingw/test_res_protocol.exe")
set_tests_properties(protocol PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/icemi/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;49;add_test;C:/Users/icemi/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;0;")
add_test(remote_state_machine "C:/Users/icemi/Desktop/RZS_Repository/RES/firmware/build-mingw/test_res_remote.exe")
set_tests_properties(remote_state_machine PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/icemi/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;53;add_test;C:/Users/icemi/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;0;")
add_test(vehicle_state_machine "C:/Users/icemi/Desktop/RZS_Repository/RES/firmware/build-mingw/test_res_vehicle.exe")
set_tests_properties(vehicle_state_machine PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/icemi/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;57;add_test;C:/Users/icemi/Desktop/RZS_Repository/RES/firmware/CMakeLists.txt;0;")
