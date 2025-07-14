cmake_minimum_required(VERSION 3.10)

# 目标架构
option(ARCH_TARGET "Target architecture (x86_64 or arm64)" "x86_64")

if(ARCH_TARGET STREQUAL "arm64")
    if(NOT (CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "aarch64" OR CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "arm64"))
        message(STATUS "交叉编译")
        set(CMAKE_SYSTEM_NAME Linux)
        set(CMAKE_SYSTEM_PROCESSOR aarch64)
        set(CMAKE_C_COMPILER   aarch64-linux-gnu-gcc)
        set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
        set(CMAKE_ASM_COMPILER aarch64-linux-gnu-gcc)
    endif()
endif()

project(myos_kernel C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SHARED_SRCS
    kernel/main.cpp
    kernel/shell.cpp
    kernel/proc.cpp
    kernel/mm.cpp
    kernel/common.hpp
    kernel/spinlock.cpp
    kernel/printf.cpp
    kernel/panic.cpp
    kernel/clock.cpp
    kernel/trap.cpp
    kernel/drivers/uart.cpp
    kernel/drivers/timer.cpp
)

if(ARCH_TARGET STREQUAL "x86_64")
    set(CMAKE_CXX_FLAGS "-ffreestanding -fno-exceptions -fno-rtti -Wl,--build-id=none -Wall -Wextra")
    set(CMAKE_C_FLAGS   "-ffreestanding -mno-red-zone -Wall -Wextra")
    set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
    enable_language(ASM_NASM)
    add_executable(kernel_x86_64.elf
        kernel/arch/x86_64/boot.asm
        kernel/arch/x86_64/entry.cpp
        kernel/arch/x86_64/smp.cpp
        kernel/arch/x86_64/trap.cpp
        kernel/arch/x86_64/isr.S
        kernel/arch/x86_64/idle.cpp
        kernel/arch/x86_64/switch.S
        kernel/arch/x86_64/power.cpp
        kernel/drivers/x86_64/uart.cpp
        kernel/drivers/x86_64/timer_pit.cpp
        ${SHARED_SRCS}
    )
    set_target_properties(kernel_x86_64.elf PROPERTIES LINKER_LANGUAGE CXX)
    target_link_options(kernel_x86_64.elf PRIVATE -T ${CMAKE_SOURCE_DIR}/kernel/arch/x86_64/linker.ld -nostdlib -static)
elseif(ARCH_TARGET STREQUAL "arm64")
    set(CMAKE_CXX_FLAGS "-ffreestanding -fno-exceptions -fno-rtti -Wl,--build-id=none -Wall -Wextra")
    set(CMAKE_C_FLAGS   "-ffreestanding -Wall -Wextra")
    enable_language(ASM)
    add_executable(kernel_arm64.elf
        kernel/arch/arm64/boot.S
        kernel/arch/arm64/entry.cpp
        kernel/arch/arm64/smp.cpp
        kernel/arch/arm64/trap.cpp
        kernel/arch/arm64/trap.S
        kernel/arch/arm64/idle.cpp
        kernel/arch/arm64/switch.S
        kernel/arch/arm64/power.cpp
        kernel/drivers/arm64/uart.cpp
        kernel/drivers/arm64/timer_generictimer.cpp
        kernel/drivers/arm64/timer_bcm2835.cpp
        ${SHARED_SRCS}
    )
    set_target_properties(kernel_arm64.elf PROPERTIES LINKER_LANGUAGE CXX)
    target_link_options(kernel_arm64.elf PRIVATE -T ${CMAKE_SOURCE_DIR}/kernel/arch/arm64/linker.ld -nostdlib -static)
else()
    message(FATAL_ERROR "ARCH_TARGET 必须为 x86_64 或 arm64，不支持\"${ARCH_TARGET}\"")
endif() 