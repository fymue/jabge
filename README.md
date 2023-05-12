# **J**ust **A**nother **B**asic **G**ame **E**ngine

## About

Linux-/Windows-compatible game engine written in C++.

This engine was written as a practice project with many ideas adopted from the [Hazel engine](https://github.com/TheCherno/Hazel) (all credits go to [TheCherno](https://github.com/TheCherno)).

This repository contains the [core engine](https://github.com/fymue/jabge/tree/main/engine) as well as a [sandbox app](https://github.com/fymue/jabge/tree/main/app/) that uses the engine to power a basic application. Most major components of the engine (Logger etc.) are implemented from scratch. Other parts like e.g. the Renderer depend on external libraries like `OpenGL`.

## Installation

### Prerequistes and dependencies

The core engine is written in C++17 and uses [OpenGL] for all graphics-related operations as well the Boost serialization library for serialization/checkpointing. `gcc` is used for Linux compilation and `mingw32` is used for Windows compilation.

### Linux

To install the dependencies for your type of Linux OS, you can execute the following commands:

#### Ubuntu / Debian
```
sudo apt install build-essential libboost-serialiation-dev libwayland-dev libxkbcommon-dev wayland-protocols extra-cmake-modules xorg-dev

```
#### Fedora
```
sudo dnf install gcc-c++ boost-serialization wayland-devel libxkbcommon-devel wayland-protocols-devel extra-cmake-modules libXcursor-devel libXi-devel libXinerama-devel libXrandr-devel mesa-libGL-devel
```

To build the engine (as a shared library), simply run `make` after cloning this repository:
```
git clone --recursive https://github.com/fymue/jabge
cd jabge
make
```

This will build the shared library `libengine.so` in the `engine/bin` directory, which is the core engine and can be linked into an executable. Including the [engine.h](https://github.com/fymue/jabge/blob/main/engine/engine.h) header file allows a program to access to public API of the engine.

### Windows

