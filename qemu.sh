#!/bin/bash
# 编译并用 QEMU 启动内核
# 用法：./run.sh [x86_64|arm64]（默认x86_64）

set -e
ARCH=${1:-x86_64}

# 编译
./build.sh $ARCH

# 运行
if [ "$ARCH" = "x86_64" ]; then
    echo "[run.sh] 使用 QEMU 启动 x86_64 内核..."
    qemu-system-x86_64 -cdrom myos.iso -serial stdio -nographic -smp 4
elif [ "$ARCH" = "arm64" ]; then
    echo "[run.sh] 使用 QEMU 启动 arm64 内核..."
    qemu-system-aarch64 -M raspi3b -kernel build/kernel_arm64.elf -serial mon:stdio -smp 4 -nographic
    # qemu-system-aarch64 -M virt -cpu cortex-a53 -kernel build/kernel_arm64.elf -serial mon:stdio -smp 4 -nographic
else
    echo "用法: ./run.sh [x86_64|arm64]"
    exit 1
fi 