#!/bin/bash
# install.sh
# 用于安装开发和运行本内核所需的工具
# Usage：sudo bash install.sh

set -e

echo "[install.sh] 正在更新软件包列表..."
sudo apt update

# 编译工具
echo "[install.sh] 安装编译工具链..."
sudo apt install -y nasm gcc g++ make cmake

# x86_64 相关依赖
echo "[install.sh] 安装 x86_64 相关依赖..."
sudo apt install -y qemu-system-x86_64

# arm64 相关依赖（交叉工具链）
echo "[install.sh] 安装 arm64 相关依赖..."
sudo apt install -y qemu-efi-aarch64 gcc-aarch64-linux-gnu g++-aarch64-linux-gnu binutils-aarch64-linux-gnu qemu-system-aarch64

# x86_64 Multiboot/GRUB 相关依赖
sudo apt install -y grub-pc-bin grub-common xorriso

echo "[install.sh] 所有依赖已安装完毕。" 