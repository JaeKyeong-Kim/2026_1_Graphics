# Agent Instructions for Graphics Workspace

Purpose
- This document provides a concise, actionable guide for an AI agent to continue working in this Graphics workspace. It summarizes project layout, build and run steps, coding conventions, and recent tasks so the agent can pick up work with minimal human instruction.

Workspace layout
- Root: `CMakeLists.txt` defines subdirectories for each week.
- Weekly folders: `weekNN_MM` and `weekNN_test_MM` each contain `main.cpp` and a small `CMakeLists.txt`.
- Current notable folders:
  - `week12_01`, `week12_test_01` — helix + rotating squares examples
  - `week13_01`, `week13_test_01`, `week13_02`, `week13_03`
  - `week14_01`, `week14_test_01`, `week14_test_02` — newly added

Build & run
- Configure and build the workspace:

```
cmake -S . -B build
cmake --build build --target <target_name> -j
```

- Run a target briefly to verify startup (example):

```
./build/week14_test_01/week14_test_01
```

Conventions
- Use legacy OpenGL (immediate mode) and FreeGLUT/GLUT API.
- Use `glBegin`/`glEnd` primitives: `GL_TRIANGLES`, `GL_TRIANGLE_STRIP`, `GL_TRIANGLE_FAN`, `GL_POINTS`, etc.
- Prefer `GLUT`/`glutMainLoop` single-window code unless user requests multiple windows.
- Test variants (`*_test_*`) should be minimal and comment-free.
- `ChangeSize` should manage projection (`glMatrixMode(GL_PROJECTION)` + `glOrtho`) using the aspect-ratio-preserving logic used in `week13_03`:
  - Use `wSize=100`, compute `aspectRatio = (float)w/h`, and set `glOrtho` accordingly.
- `SetupRC` should set clear color and shading model (`glShadeModel(GL_SMOOTH)` or `GL_FLAT` as requested).

Recent modifications and patterns
- `week12_test_01`: Helix visual with rotating squares; uses `(float)rand()/RAND_MAX` for colors and `GL_LINE_STRIP` for square outlines.
- `week13_01`: Minimal `GL_TRIANGLES` example (filled triangle) with `GL_CCW` front face.
- `week13_test_01`: `GL_TRIANGLE_STRIP` example (4 vertices forming a square).
- `week13_02`: `GL_TRIANGLE_STRIP` with 5 vertices forming partial strip.
- `week13_03`: `GL_TRIANGLE_FAN` circle with 16 slices; `ChangeSize` handles projection; `RenderScene` draws green fan and red points.
- `week14_*`: Copies of `week13_03` variants; `week14_test_01` modified to:
  - Draw 32 slices with `GL_TRIANGLE_FAN`
  - White background (`glClearColor(1,1,1,1)`)
  - Flat shading (`glShadeModel(GL_FLAT)`)
  - Slice coloring: first slice blue, then alternating red/green around counter-clockwise.

Editing guidance
- When modifying `main.cpp`, prefer replacing the entire file in a single patch to avoid syntax mismatches.
- Use `apply_patch` (or the provided file-edit tool) to make atomic edits; include minimal context lines as required.
- After edits, run the build for the specific target and execute it briefly to validate.

Common tasks for the agent
- Create new `weekNN_MM` directories by copying `week13_03` template, update `CMakeLists.txt`, and add `add_subdirectory` to root `CMakeLists.txt`.
- Convert example primitives between `GL_TRIANGLES`, `GL_TRIANGLE_STRIP`, and `GL_TRIANGLE_FAN` on user request.
- Toggle shading using `glShadeModel(GL_SMOOTH)` or `GL_FLAT`.
- Add per-vertex colors (use `glColor3f` before `glVertex`) to demonstrate interpolation.

Build & run checklist
- After changes:
  1. `cmake -S . -B build`
  2. `cmake --build build --target <target>`
  3. Run `./build/<target>/<target>` briefly to validate UI and output.

Notes
- macOS OpenGL/GLUT functions produce deprecation warnings; these are expected and can be ignored unless the user asks to migrate to GLFW or modern GL.
- Test variants must be comment-free and as minimal as possible.

If you want, I can also commit these changes and create a `README.md` with usage examples, or export a short script that builds and runs any week target automatically.
