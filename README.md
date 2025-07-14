# myoskernel-cpp

支持x86-64/ARM64指令集

### x86-64
```sh
mkdir build && cd build
cmake .. -DARCH_X86_64=ON -DARCH_ARM64=OFF
make
qemu-system-x86_64 -kernel kernel.elf
```

### ARM64
```sh
mkdir build && cd build
cmake .. -DARCH_X86_64=OFF -DARCH_ARM64=ON
make
qemu-system-aarch64 -M raspi3b -kernel kernel_arm.elf -serial stdio
```

## 依赖
- CMake、nasm、交叉编译工具链（x86_64-elf-gcc、aarch64-elf-gcc）
- QEMU