
if(NOT "/mnt/c/Users/rotmu/Desktop/FIT/1.BIT/2. SEM/IVS/assignment/build/googletest/googletest-prefix/src/googletest-stamp/googletest-gitinfo.txt" IS_NEWER_THAN "/mnt/c/Users/rotmu/Desktop/FIT/1.BIT/2. SEM/IVS/assignment/build/googletest/googletest-prefix/src/googletest-stamp/googletest-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/mnt/c/Users/rotmu/Desktop/FIT/1.BIT/2. SEM/IVS/assignment/build/googletest/googletest-prefix/src/googletest-stamp/googletest-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E remove_directory "/mnt/c/Users/rotmu/Desktop/FIT/1.BIT/2. SEM/IVS/assignment/build/googletest-master"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/mnt/c/Users/rotmu/Desktop/FIT/1.BIT/2. SEM/IVS/assignment/build/googletest-master'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"  clone --no-checkout "https://github.com/google/googletest.git" "googletest-master"
    WORKING_DIRECTORY "/mnt/c/Users/rotmu/Desktop/FIT/1.BIT/2. SEM/IVS/assignment/build"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/google/googletest.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git"  checkout main --
  WORKING_DIRECTORY "/mnt/c/Users/rotmu/Desktop/FIT/1.BIT/2. SEM/IVS/assignment/build/googletest-master"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'main'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/mnt/c/Users/rotmu/Desktop/FIT/1.BIT/2. SEM/IVS/assignment/build/googletest-master"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/mnt/c/Users/rotmu/Desktop/FIT/1.BIT/2. SEM/IVS/assignment/build/googletest-master'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/mnt/c/Users/rotmu/Desktop/FIT/1.BIT/2. SEM/IVS/assignment/build/googletest/googletest-prefix/src/googletest-stamp/googletest-gitinfo.txt"
    "/mnt/c/Users/rotmu/Desktop/FIT/1.BIT/2. SEM/IVS/assignment/build/googletest/googletest-prefix/src/googletest-stamp/googletest-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/mnt/c/Users/rotmu/Desktop/FIT/1.BIT/2. SEM/IVS/assignment/build/googletest/googletest-prefix/src/googletest-stamp/googletest-gitclone-lastrun.txt'")
endif()

