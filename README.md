# Redball

Redball 是一个基于 SDL3 的简单演示项目，展示了一个在窗口中运动的红色球体效果，包含重力、阻力、反弹以及拖尾动画。

## 功能特点

- 使用 SDL3 创建窗口和渲染器
- 模拟球体受重力影响的运动
- 支持边界反弹和阻力效果
- 通过键盘控制球体的运动方向
- 实现简单的拖尾视觉效果

## 依赖

- CMake 3.10 或更高版本
- SDL3

## 构建方法(MacOS)

在项目根目录执行以下命令：

```bash
cmake -S . -B build
cmake --build build
```

构建完成后，可运行：

```bash
./bin/main
```

## 控制说明

- W: 增加向上的作用力
- A: 向左调整运动
- D: 向右调整运动
- 关闭窗口即可退出程序

## 项目结构

```bash
redball
├── bin
│   └── main
├── build
├── CMakeLists.txt
├── include
├── main.cpp
├── README.md
└── src
    └── main.cpp
```