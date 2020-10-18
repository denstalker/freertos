include(CMakeForceCompiler)

set(MCU_LINKER_SCRIPT STM32F103C8Tx_FLASH.ld)
set(MCU_ARCH cortex-m3)
set(MCU_FLOAT_ABI soft)
set(MCU_FPU fpv4-sp-d16)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
CMAKE_FORCE_C_COMPILER(arm-none-eabi-gcc GCC)
CMAKE_FORCE_CXX_COMPILER(arm-none-eabi-g++ GCC)

set(COMMON_FLAGS "-mcpu=${MCU_ARCH} -mthumb -specs=nano.specs -specs=nosys.specs -mfloat-abi=${MCU_FLOAT_ABI}  -Og -Wall -fdata-sections -ffunction-sections -g -gdwarf-2 -MMD -MP -MF")

if (MCU_FLOAT_ABI STREQUAL hard)
    set(COMMON_FLAGS "${COMMON_FLAGS} -mfpu=${MCU_FPU}")
endif ()

set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=c++17")
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -std=gnu99")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-gc-sections -T ${CMAKE_SOURCE_DIR}/${MCU_LINKER_SCRIPT}")
