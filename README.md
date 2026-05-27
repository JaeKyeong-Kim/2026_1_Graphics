# 2026_1 Graphics

Course repository for the 2026 Spring Graphics class.

This project collects weekly OpenGL practice work built on macOS with CMake and FreeGLUT-style APIs. Most exercises are small, self-contained programs organized by week so each folder can be built and run as an independent target.

## Tech Stack

- Language: C++17
- Build system: CMake
- Graphics API: Legacy OpenGL immediate mode
- Window/input handling: GLUT / FreeGLUT-compatible API
- Platform target: macOS

## Repository Layout

- `week01` to `week18_*`: weekly class exercises and test variants
- `CMakeLists.txt`: root build entry that registers all tracked week targets
- `rebuild_target.sh`: helper script to reconfigure, rebuild, and run one target
- `CPPS.md`: local study and class notes used while implementing exercises

Local-only folders are intentionally excluded from GitHub:

- `Notes/`
- `test/`
- `week00/`
- `build/`

## macOS Setup

This repository is intended for macOS users.

### 1. Install dependencies

You need:

- Xcode Command Line Tools
- CMake
- Homebrew

OpenGL and GLUT are linked through macOS frameworks in the current project layout.

To install CMake with Homebrew:

```bash
brew install cmake
```

### 2. Configure the project

From the repository root:

```bash
cmake -S . -B build
```

### 3. Build a specific week target

Example:

```bash
cmake --build build --target week17_03 -j
```

### 4. Run the target

Example:

```bash
./build/week17_03/week17_03
```

## Faster Build + Run

This repository includes a helper script that runs configure, build, and execute in one step.

Examples:

```bash
./rebuild_target.sh week17_03
./rebuild_target.sh build/week17_03/week17_03
```

The window will stay open until you close it.

## Class Structure

The weekly exercises generally cover:

- basic GLUT window setup
- 2D primitives and viewport handling
- orthographic projection
- point, line, strip, and fan primitives
- simple transformations
- keyboard interaction
- face culling
- depth testing

Recent weeks focus more on:

- winding order and front/back face handling
- triangle fan based circles and cones
- culling and depth-test interactions
- outline and wireframe rendering

## Notes for macOS Users

- macOS will show OpenGL / GLUT deprecation warnings during build. That is expected for this class setup.
- The current codebase uses immediate mode APIs on purpose because the class is focused on foundational graphics concepts.
- If you edit source files and run an old executable directly, your changes will not appear until you rebuild the matching target.

## License

This repository uses the MIT License already attached to the GitHub repository.
