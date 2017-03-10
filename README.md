# lib-riff

[![Build Status](https://travis-ci.org/redivo/lib-riff.svg?branch=master)](https://travis-ci.org/redivo/lib-riff)


## Introduction

lib-riff if a C Library to abstract Resource Interchange File Format (RIFF). Please refer to [RIFF description]( http://www.digitalpreservation.gov/formats/fdd/fdd000025.shtml).


## Compiling and testin

This library is compiled using [CMake](https://cmake.org/).
CMake enables you to perform an out of tree compilation, so supposing you already have CMake
installed and you have lib-riff cloned:

 - Create an build directory
```
# mkdir -p <build path>
```

 - Enter in build directory:
```
# cd <build path>
```

 - Run **cmake** over lib-riff repository:
```
# cmake <lib-riff path>
```

 - Run **make**:

```
# make
```

 - Execute tests:
```
# test/test
```

Example:
```
# cd /tmp/
# mkdir -p _build
# cd _build/
# cd /tmp/
# git clone https://github.com/redivo/lib-riff.git
Cloning into 'lib-riff'...
remote: Counting objects: 55, done.
remote: Compressing objects: 100% (8/8), done.
remote: Total 55 (delta 1), reused 0 (delta 0), pack-reused 47
Unpacking objects: 100% (55/55), done.
Checking connectivity... done.
#  mkdir -p _build
# cd _build/
# cmake ../lib-riff/
-- The C compiler identification is GNU 4.8.4
-- The CXX compiler identification is GNU 4.8.4
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found GTest: /usr/lib/libgtest.a  
-- Looking for pthread.h
-- Looking for pthread.h - found
-- Looking for pthread_create
-- Looking for pthread_create - not found
-- Looking for pthread_create in pthreads
-- Looking for pthread_create in pthreads - not found
-- Looking for pthread_create in pthread
-- Looking for pthread_create in pthread - found
-- Found Threads: TRUE  
CMake Warning (dev) at test/CMakeLists.txt:15 (add_executable):
  Policy CMP0037 is not set: Target names should not be reserved and should
  match a validity pattern.  Run "cmake --help-policy CMP0037" for policy
  details.  Use the cmake_policy command to set the policy and suppress this
  warning.

  The target name "test" is reserved or not valid for certain CMake features,
  such as generator expressions, and may result in undefined behavior.
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Configuring done
-- Generating done
-- Build files have been written to: /tmp/_build
# make
Scanning dependencies of target riff
[ 25%] Building C object src/CMakeFiles/riff.dir/riff.c.o
[ 50%] Linking C shared library libriff.so
[ 50%] Built target riff
Scanning dependencies of target test
[ 75%] Building CXX object test/CMakeFiles/test.dir/riff.cc.o
[100%] Linking CXX executable test
[100%] Built target test
# test/test 
Running main() from gtest_main.cc
[==========] Running 10 tests from 2 test cases.
[----------] Global test environment set-up.
(...)
[----------] Global test environment tear-down
[==========] 10 tests from 2 test cases ran. (0 ms total)
[  PASSED  ] 10 tests.
```


## Features

What is already done:
 - Subchunk creation
 - Subchunk payload setting
 - Chunk creation
 - Chunk creation passing type
 - Subchunk adding

What is not implemented yet:
 - RIFF list support
 - Get subchunk from chunk
 - Remove subchunk from chunk
 - Get chunk "compiled" data
 - C++ API
