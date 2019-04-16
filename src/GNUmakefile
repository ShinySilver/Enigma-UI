#-----------------------------------------------------------------------------
# this GNU-makefile relies on the GCC toolchain
# nb: under Windows, the Mingw-w64 package provides the mingw32-make command
#     ( see http://www.enib.fr/~harrouet/misc.html#mingw )

#~~~~ control global settings ~~~~
# make opt=1 --> enable optimisation, then disable debug
# make opt=0 --> disable optimisation, then enable debug
opt=0
# make clang=1 --> use clang/clang++, not gcc/g++
# make clang=0 --> use gcc/g++, not clang/clang++
clang=0
# make emcc=1 --> target javascript rather than the native platform
# make emcc=0 --> target the native platform rather than javascript
emcc=0

#~~~~ build library or programs ~~~~
# if LIB_TARGET is provided, this library will be built (with its
# platform-specific name), otherwise ${EXE_PREFIX}* programs will be built
LIB_TARGET=
EXE_PREFIX=prog

#~~~~ detect operating system ~~~~
ifneq (${OS},Windows_NT)
  ifneq (,${findstring Microsoft,${shell cat /proc/version 2>/dev/null}})
    # Windows-Subsystem-for-Linux
    OS:=WSL
  else ifneq (,${findstring Ubuntu,${shell lsb_release -i 2>/dev/null}})
    OS:=Ubuntu
  else
    OS:=${strip ${shell uname -s}}
  endif
endif

#~~~~ adjust project-specific settings ~~~~
CPPFLAGS=
# CPPFLAGS+=-I header/path
CPPFLAGS+=-I ${SFMLDIR}/include
LDFLAGS=
# LDFLAGS+=-L library/path -Wl,-rpath,library/path -l library_name
LDFLAGS=-L ${SFMLDIR}/lib -Wl,-rpath,${SFMLDIR}/lib \
         -lsfml-graphics -lsfml-window -lsfml-system -static-libasan
ifeq (${OS},Windows_NT)
  # nothing special for now
else
  CPPFLAGS+=-fPIC
  ifeq (${OS},Darwin)
    # nothing special for now
  else ifeq (${OS},Ubuntu)
    # sanitizer requires gold-linker on Ubuntu
    LDFLAGS+=-fuse-ld=gold
  else
    # nothing special for now
  endif
endif

#~~~~ adjust platform-specific features (Posix/Windows/Emscripten...) ~~~~
ifeq (${OS},Windows_NT)
  LIB_PREFIX=
  LIB_SUFFIX=.dll
  EXE_SUFFIX=.exe
  SKIP_LINE=echo.
  REMOVE=del /q
else
  LIB_PREFIX=lib
  ifeq (${OS},Darwin)
    LIB_SUFFIX=.dylib
  else
    LIB_SUFFIX=.so
  endif
  EXE_SUFFIX=
  SKIP_LINE=echo
  REMOVE=rm -rf
endif
ifeq (${strip ${emcc}},1)
  LIB_PREFIX:=lib
  LIB_SUFFIX:=.bc
  EXE_SUFFIX:=.html
endif

#~~~~ deduce file names ~~~~
ifneq (${strip ${LIB_TARGET}},)
  LIB_TARGET:=${LIB_PREFIX}${strip ${LIB_TARGET}}${LIB_SUFFIX}
  MAIN_C_FILES=
  MAIN_CXX_FILES=
else
  LIB_TARGET:=
  MAIN_C_FILES=${wildcard ${strip ${EXE_PREFIX}}*.c}
  MAIN_CXX_FILES=${wildcard ${strip ${EXE_PREFIX}}*.cpp}
endif
COMMON_C_FILES=${filter-out ${MAIN_C_FILES},${wildcard *.c}}
COMMON_CXX_FILES=${filter-out ${MAIN_CXX_FILES},${wildcard *.cpp}}
#
MAIN_OBJECT_FILES=${sort ${patsubst %.c,%.o,${MAIN_C_FILES}} \
                         ${patsubst %.cpp,%.o,${MAIN_CXX_FILES}}}
COMMON_OBJECT_FILES=${sort ${patsubst %.c,%.o,${COMMON_C_FILES}} \
                           ${patsubst %.cpp,%.o,${COMMON_CXX_FILES}}}
OBJECT_FILES=${MAIN_OBJECT_FILES} ${COMMON_OBJECT_FILES}
DEPEND_FILES=${patsubst %.o,%.d,${OBJECT_FILES}}
EXE_FILES=${sort ${patsubst %.c,%${EXE_SUFFIX},${MAIN_C_FILES}} \
                 ${patsubst %.cpp,%${EXE_SUFFIX},${MAIN_CXX_FILES}}}
#
GENERATED_FILES=${DEPEND_FILES} ${OBJECT_FILES} ${LIB_TARGET} ${EXE_FILES}
ifeq (${OS},Darwin)
  GENERATED_FILES+=${wildcard *.dSYM}
endif
ifeq (${strip ${emcc}},1)
  GENERATED_FILES+=${patsubst %.html,%.js,${EXE_FILES}}
  GENERATED_FILES+=${patsubst %.html,%.html.mem,${EXE_FILES}}
endif
GENERATED_FILES+=${wildcard output_* *~ core}
GENERATED_FILES+=${wildcard .[1-9]}
GENERATED_FILES+=${wildcard .[1-9][0-9]}
GENERATED_FILES+=${wildcard .[1-9][0-9][0-9]}
GENERATED_FILES+=${wildcard .[1-9][0-9][0-9][0-9]}
GENERATED_FILES+=${wildcard .[1-9][0-9][0-9][0-9][0-9]}

#~~~~ compiler/linker settings ~~~~
CPPFLAGS+=-pedantic -Wall -Wextra -Wconversion -MMD
CFLAGS=-std=c99 -Wc++-compat -Wwrite-strings -Wold-style-definition
CXXFLAGS=-std=c++1z
# sign-conversion is too restrictive on standard C++ library usage
CXXFLAGS+=-Wno-sign-conversion
# clang warns about missing double-braces on std::array
CXXFLAGS+=-Wno-missing-braces
LDFLAGS+=
ifeq (${strip ${emcc}},1)
  CC=emcc
  CXX=em++
else ifeq (${strip ${clang}},1)
  CC=clang
  CXX=clang++
else
  CC=gcc
  CXX=g++
endif
#
ifneq (${strip ${MAIN_CXX_FILES} ${COMMON_CXX_FILES}},)
  # force c++ usage if there is at least one c++ source file
  CC:=${CXX}
  CFLAGS:=${CXXFLAGS}
endif
#
LD:=${CC}

#~~~~ debug/optimisation settings ~~~~
ifeq (${strip ${opt}},1)
  CPPFLAGS+=-O3 -DNDEBUG -fomit-frame-pointer
  CPPFLAGS+=-ffast-math
  CPPFLAGS+=-march=native
  # CPPFLAGS+=-fopt-info-vec-optimized
else
  CPPFLAGS+=-g -O0 -UNDEBUG
  ifeq (${strip ${emcc}},1)
    # sanitizer is not available yet with Emscripten
  else ifeq (${OS},Windows_NT)
    # sanitizer is not available yet on Windows
  else ifeq (${OS},WSL)
    # sanitizer is not available yet on Windows-Subsystem-for-Linux
  else ifeq (${OS},Darwin)
    # sometimes sanitizer produces linker warnings on MacOSX
  else
    CPPFLAGS+=-fsanitize=address,undefined
  endif
endif
CPPFLAGS+=-pthread
CPPFLAGS+=-fext-numeric-literals # J'ai rajouté ça. Je ne sais pas trop pk. hf.

#~~~~ main target ~~~~
all : ${EXE_FILES} ${LIB_TARGET}

rebuild : clean all

.SUFFIXES:
.SECONDARY:
.PHONY: all clean rebuild

#~~~~ linker command to produce the library (if any) ~~~~
${LIB_TARGET} : ${COMMON_OBJECT_FILES}
	@echo ==== linking $@ ====
	${LD} -shared -o $@ $^ ${CPPFLAGS} ${LDFLAGS}
	@${SKIP_LINE}

#~~~~ linker command to produce the executable files (if any) ~~~~
%${EXE_SUFFIX} : %.o ${COMMON_OBJECT_FILES}
	@echo ==== linking $@ ====
	cd ../build/;${LD} -o $@ $^ ${CPPFLAGS} ${LDFLAGS}
	@${SKIP_LINE}

#~~~~ compiler command for every source file ~~~~
%.o : %.c
	@echo ==== compiling [opt=${opt}] $< ====
	${CC} -o ../build/$@ $< -c ${CPPFLAGS} ${CFLAGS}
	@${SKIP_LINE}

%.o : %.cpp
	@echo ==== compiling [opt=${opt}] $< ====
	${CXX} -o ../build/$@ $< -c ${CPPFLAGS} ${CXXFLAGS}
	@${SKIP_LINE}

-include ${DEPEND_FILES}

#~~~~ remove generated files ~~~~
clean :
	@echo ==== cleaning ====
	cd ../build/;${REMOVE} ${GENERATED_FILES}
	@${SKIP_LINE}

#-----------------------------------------------------------------------------
