add_definitions(-DBOOST_FILESYSTEM_NO_DEPRECATED -DBOOST_FILESYSTEM_VERSION=3)
add_definitions(-DBOOST_PYTHON_STATIC_LIB)

if(MSVC)
  set(CMAKE_CXX_FLAGS)
  set(CMAKE_CXX_FLAGS_INIT)
endif()

if(WIN32)
  add_definitions(-DWIN32 -D_WIN32 -D__WINDOWS__ -D__WIN32__)
elseif(UNIX)
  add_definitions(-D_FILE_OFFSET_BITS=64)
endif()

if(MSVC)
  add_definitions(-D__MSVC__ -DWIN32_LEAN_AND_MEAN -D_WIN32_WINNT=0x501)
  add_definitions(-D_CONSOLE -D_UNICODE -DUNICODE -D_BIND_TO_CURRENT_VCLIBS_VERSION=1)

  # VC11 contains std::tuple with variadic templates emulation macro.
  # _VARIADIC_MAX defaulted to 5 but gtest requires 10.
  add_definitions(-D_VARIADIC_MAX=10)

  # prevents std::min() and std::max() to be overwritten
  add_definitions(-DNOMINMAX)

  # W4 -   Set warning level 4.
  # WX -   Treat warnings as errors.
  # MP7 -  Enable multi-processor compilation (max 7).
  # EHsc - Catches C++ exceptions only and tells the compiler to assume that
  #        extern C functions never throw a C++ exception.
  # TP -   Treat sources as C++
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX /MP7 /EHsc /TP")

  # O2 - Optimise code for maximum speed.  Implies the following:
  #      Og (global optimisations)
  #      Oi (replace some function calls with intrinsic functions),
  #      Ot (favour fast code),
  #      Oy (suppress creation of frame pointers on the call stack),
  #      Ob2 (auto inline),
  #      Gs (control stack probes),
  #      GF (eliminate duplicate strings),
  #      Gy (allows the compiler to package individual functions in the form of
  #          packaged functions)
  # GL - Whole program optimisation
  # MD - Use the multithread, dynamic version of the C run-time library.
  set(CMAKE_CXX_FLAGS_RELEASE "/O2 /GL /D \"NDEBUG\" /MD")

  # Zi -   Produce a program database (.pdb) that contains type information and
  #        symbolic debugging information.
  # Od -   No optimizations in the program (speeds compilation).
  # RTC1 - Enables stack frame run-time error checking and checking for
  #        unintialised variables.
  # MDd -  Use the debug multithread, dynamic version of the C run-time library.
  set(CMAKE_CXX_FLAGS_DEBUG "/Zi /Od /D \"_DEBUG\" /D \"DEBUG\" /RTC1 /MDd")
  set(CMAKE_CXX_FLAGS_MINSIZEREL "/MD")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} /Zi")

  set_target_properties(${ALL_LIBRARIES} PROPERTIES
                          STATIC_LIBRARY_FLAGS_RELEASE "/LTCG"
                          STATIC_LIBRARY_FLAGS_RELWITHDEBINFO "/LTCG")

  set_target_properties(${AllExesForCurrentProject} PROPERTIES
                          LINK_FLAGS_RELEASE "/OPT:REF /OPT:ICF /LTCG /INCREMENTAL:NO"
                          LINK_FLAGS_DEBUG "/DEBUG"
                          LINK_FLAGS_RELWITHDEBINFO "/OPT:REF /OPT:ICF /LTCG /INCREMENTAL:NO /DEBUG"
                          LINK_FLAGS_MINSIZEREL "/LTCG")
elseif(UNIX)
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -fno-inline -fno-eliminate-unused-debug-types -g3 -ggdb")
  execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
  if(GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static-libstdc++ -fopenmp -Werror")
  elseif(GCC_VERSION VERSION_GREATER 4.6 OR GCC_VERSION VERSION_EQUAL 4.6)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -static-libstdc++ -fopenmp -Werror")
  else()
    message(FATAL_ERROR "Unsupported version of GCC, minimum 4.6 required")
  endif()

  if(CMAKE_BUILD_TYPE MATCHES "Debug")
    add_definitions(-DDEBUG)
  endif()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wunused-parameter -Wno-system-headers -Wno-deprecated")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wwrite-strings -Wundef")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wuninitialized -Wparentheses")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfloat-equal -Wstrict-overflow -Wstrict-overflow=5 -Wredundant-decls")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -pedantic -pedantic-errors ")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -ggdb")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG -D_FORTIFY_SOURCE=2")
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
  unset(COVERAGE CACHE)
endif()
