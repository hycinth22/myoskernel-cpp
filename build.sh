#!/bin/bash
# build.sh
# 用于在任意主机上交叉编译 x86_64 或 arm64 内核，并输出对应 QEMU 启动命令
# 用法：./build.sh [x86_64|arm64|clean]

set -e

if [ "$1" = "clean" ]; then
    echo "[myos] 清理 build 目录..."
    rm -rf build
    echo "[myos] 清理完成。"
    exit 0
fi

ARCH=${1:-x86_64}
BUILD_DIR=build
BUILD_OUTPUT_NAME=kernel_$ARCH.elf
ISO_TEMPLATE_DIR=iso
ISO_BUILD_DIR=$BUILD_DIR/iso
ISO_OUTPUT_NAME="myos-$(date +%Y%m%d_%H%M%S).iso"
SRC_DIR=src

if [ "$ARCH" = "x86_64" ]; then
    echo "[myos] 目标架构: x86_64"
    cmake -B $BUILD_DIR -S $SRC_DIR -DARCH_TARGET=x86_64
    cmake --build $BUILD_DIR
    echo "[myos] 编译完成: $BUILD_DIR/$BUILD_OUTPUT_NAME"
    # 生成 Multiboot2 ISO 镜像
    echo "[myos] 正在生成 Multiboot2 ISO 镜像..."
    mkdir -p $ISO_BUILD_DIR
    cp -r $ISO_TEMPLATE_DIR/* $ISO_BUILD_DIR/
    cp $BUILD_DIR/$BUILD_OUTPUT_NAME $ISO_BUILD_DIR/boot/$BUILD_OUTPUT_NAME
    grub-mkrescue -o $BUILD_DIR/$ISO_OUTPUT_NAME $ISO_BUILD_DIR
    echo "[myos] ISO 镜像已生成: $ISO_OUTPUT_NAME"
    echo "QEMU运行: qemu-system-x86_64 -cdrom $BUILD_DIR\\$ISO_OUTPUT_NAME -nographic"
elif [ "$ARCH" = "arm64" ]; then
    echo "[myos] 目标架构: arm64"
    HOST_ARCH=$(uname -m)
    if [ "$HOST_ARCH" != "aarch64" ] && [ "$HOST_ARCH" != "arm64" ]; then
        export CC=aarch64-linux-gnu-gcc
        export CXX=aarch64-linux-gnu-g++
    fi
    cmake -B $BUILD_DIR -S $SRC_DIR -DARCH_TARGET=arm64
    cmake --build $BUILD_DIR
    echo "[myos] 编译完成: $BUILD_DIR/$BUILD_OUTPUT_NAME"
    echo "QEMU运行: qemu-system-aarch64 -M raspi3b -kernel $BUILD_DIR/$BUILD_OUTPUT_NAME -serial stdio"
else
    echo "用法: ./build.sh [x86_64|arm64|clean]"
    exit 1
fi 