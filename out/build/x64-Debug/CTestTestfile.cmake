# CMake generated Testfile for 
# Source directory: D:/github/libnss-maria
# Build directory: D:/github/libnss-maria/out/build/x64-Debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(config_helpers_test "test/maria_config_helpers_test")
set_tests_properties(config_helpers_test PROPERTIES  _BACKTRACE_TRIPLES "D:/github/libnss-maria/CMakeLists.txt;30;add_test;D:/github/libnss-maria/CMakeLists.txt;0;")
add_test(config_test "test/maria_config_test")
set_tests_properties(config_test PROPERTIES  _BACKTRACE_TRIPLES "D:/github/libnss-maria/CMakeLists.txt;31;add_test;D:/github/libnss-maria/CMakeLists.txt;0;")
add_test(logger_test "test/maria_logger_test")
set_tests_properties(logger_test PROPERTIES  _BACKTRACE_TRIPLES "D:/github/libnss-maria/CMakeLists.txt;32;add_test;D:/github/libnss-maria/CMakeLists.txt;0;")
add_test(integration_nss_test "test/integration/nss_module")
set_tests_properties(integration_nss_test PROPERTIES  _BACKTRACE_TRIPLES "D:/github/libnss-maria/CMakeLists.txt;33;add_test;D:/github/libnss-maria/CMakeLists.txt;0;")
subdirs("src")
subdirs("test")
