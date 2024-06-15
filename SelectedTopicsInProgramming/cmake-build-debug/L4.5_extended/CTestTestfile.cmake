# CMake generated Testfile for 
# Source directory: C:/Users/sebas/OneDrive/Billeder/Dokumenter/GitHub/AAU/SelectedTopicsInProgramming/L4.5_extended
# Build directory: C:/Users/sebas/OneDrive/Billeder/Dokumenter/GitHub/AAU/SelectedTopicsInProgramming/cmake-build-debug/L4.5_extended
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(main "C:/Users/sebas/OneDrive/Billeder/Dokumenter/GitHub/AAU/SelectedTopicsInProgramming/cmake-build-debug/L4.5_extended/main.exe")
set_tests_properties(main PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/sebas/OneDrive/Billeder/Dokumenter/GitHub/AAU/SelectedTopicsInProgramming/L4.5_extended/CMakeLists.txt;18;add_test;C:/Users/sebas/OneDrive/Billeder/Dokumenter/GitHub/AAU/SelectedTopicsInProgramming/L4.5_extended/CMakeLists.txt;0;")
add_test(number_series_test "C:/Users/sebas/OneDrive/Billeder/Dokumenter/GitHub/AAU/SelectedTopicsInProgramming/cmake-build-debug/L4.5_extended/number_series_test.exe")
set_tests_properties(number_series_test PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/sebas/OneDrive/Billeder/Dokumenter/GitHub/AAU/SelectedTopicsInProgramming/L4.5_extended/CMakeLists.txt;22;add_test;C:/Users/sebas/OneDrive/Billeder/Dokumenter/GitHub/AAU/SelectedTopicsInProgramming/L4.5_extended/CMakeLists.txt;0;")
add_test(sort_bm "C:/Users/sebas/OneDrive/Billeder/Dokumenter/GitHub/AAU/SelectedTopicsInProgramming/cmake-build-debug/L4.5_extended/sort_bm.exe")
set_tests_properties(sort_bm PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/sebas/OneDrive/Billeder/Dokumenter/GitHub/AAU/SelectedTopicsInProgramming/L4.5_extended/CMakeLists.txt;26;add_test;C:/Users/sebas/OneDrive/Billeder/Dokumenter/GitHub/AAU/SelectedTopicsInProgramming/L4.5_extended/CMakeLists.txt;0;")
add_test(number_series_bm "C:/Users/sebas/OneDrive/Billeder/Dokumenter/GitHub/AAU/SelectedTopicsInProgramming/cmake-build-debug/L4.5_extended/number_series_bm.exe")
set_tests_properties(number_series_bm PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/sebas/OneDrive/Billeder/Dokumenter/GitHub/AAU/SelectedTopicsInProgramming/L4.5_extended/CMakeLists.txt;30;add_test;C:/Users/sebas/OneDrive/Billeder/Dokumenter/GitHub/AAU/SelectedTopicsInProgramming/L4.5_extended/CMakeLists.txt;0;")
subdirs("../_deps/doctest-build")
subdirs("../_deps/googlebenchmark-build")
