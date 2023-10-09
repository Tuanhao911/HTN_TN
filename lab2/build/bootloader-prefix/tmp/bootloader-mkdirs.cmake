# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Learning/HTN_TN/Espressif/frameworks/esp-idf-v5.0.2/components/bootloader/subproject"
  "D:/Learning/HTN_TN/Espressif/frameworks/esp-idf-v5.0.2/examples/get-started/sample_project/build/bootloader"
  "D:/Learning/HTN_TN/Espressif/frameworks/esp-idf-v5.0.2/examples/get-started/sample_project/build/bootloader-prefix"
  "D:/Learning/HTN_TN/Espressif/frameworks/esp-idf-v5.0.2/examples/get-started/sample_project/build/bootloader-prefix/tmp"
  "D:/Learning/HTN_TN/Espressif/frameworks/esp-idf-v5.0.2/examples/get-started/sample_project/build/bootloader-prefix/src/bootloader-stamp"
  "D:/Learning/HTN_TN/Espressif/frameworks/esp-idf-v5.0.2/examples/get-started/sample_project/build/bootloader-prefix/src"
  "D:/Learning/HTN_TN/Espressif/frameworks/esp-idf-v5.0.2/examples/get-started/sample_project/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Learning/HTN_TN/Espressif/frameworks/esp-idf-v5.0.2/examples/get-started/sample_project/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Learning/HTN_TN/Espressif/frameworks/esp-idf-v5.0.2/examples/get-started/sample_project/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
