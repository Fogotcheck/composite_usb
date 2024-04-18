cmake_minimum_required(VERSION 3.22)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(STM32_TARGET_TRIPLET arm-none-eabi)

find_program(CMAKE_C_COMPILER NAMES ${STM32_TARGET_TRIPLET}-gcc)
get_filename_component(C_COMPILER_PATH "${CMAKE_C_COMPILER}" DIRECTORY)
set(C_COMPILE_PREFIX ${C_COMPILER_PATH}/${STM32_TARGET_TRIPLET})

if(WIN32)
  set(WIN_EXE ".exe")
else()
  # set stuff for other systems
endif()

set(CMAKE_AR "${C_COMPILE_PREFIX}-gcc-ar${WIN_EXE}")
set(CMAKE_RANLIB "${C_COMPILE_PREFIX}-gcc-ranlib${WIN_EXE}")
set(CMAKE_LD "${C_COMPILE_PREFIX}-ld${WIN_EXE}")
set(CMAKE_CXX_COMPILER "${C_COMPILE_PREFIX}-g++${WIN_EXE}")
set(CMAKE_OBJCOPY "${C_COMPILE_PREFIX}-objcopy${WIN_EXE}")
set(CMAKE_OBJDUMP "${C_COMPILE_PREFIX}-objdump${WIN_EXE}")
set(CMAKE_GDB "${C_COMPILE_PREFIX}-gdb${WIN_EXE}")
set(CMAKE_SIZE "${C_COMPILE_PREFIX}-size${WIN_EXE}")
set(CMAKE_ASM_COMPILER "${C_COMPILE_PREFIX}-gcc${WIN_EXE}")

set(CMAKE_EXECUTABLE_FORMAT ELF)

set(STM32_CPU "-mcpu=cortex-m4")
set(STM32_FPU "-mfpu=fpv4-sp-d16")
set(STM32_FLOAT_ABI "-mfloat-abi=hard")

add_compile_options(
  ${STM32_CPU}
  "-mthumb"
  ${STM32_FPU}
  ${STM32_FLOAT_ABI}
  "-fdata-sections"
  "-ffunction-sections"
  "-Wall"
)

add_link_options(
  ${STM32_CPU}
  "-mthumb"
  ${STM32_FPU}
  ${STM32_FLOAT_ABI}
  "--specs=nosys.specs"
  "-Wl,-Map=${PROJECT_NAME}.map"
  "-Wl,--gc-sections"
  "-static"
  "-Wl,--start-group"
  "-lc"
  "-lm"
  "-Wl,--end-group"
)
