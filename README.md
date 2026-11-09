# Handmade — Win32 Game from Scratch

A Win32 application built from scratch in C++ — no engine, no framework, just the Windows API and raw code.
Inspired by the [Handmade Hero](https://handmadehero.org/) project by Casey Muratori.

---

## What It Does (So Far)

- Creates a native Win32 window using `RegisterClassW` and `CreateWindowEx`
- Handles core window messages (`WM_PAINT`, `WM_SIZE`, `WM_CLOSE`, `WM_DESTROY`, `WM_ACTIVATEAPP`)
- Paints the window alternating between black and white on each resize using `PatBlt`
- Logs window events to the debug output via `OutputDebugStringA`
- Runs a standard Win32 message loop with `GetMessage` / `TranslateMessage` / `DispatchMessage`

---

## Project Structure

```
handmade/
├── handmade.cpp          # Main source file — entry point + window callback
├── handmade.h            # Main header (includes Windows.h)
├── framework.h           # Precompiled header framework
├── targetver.h           # Windows version targeting
├── Resource.h            # Resource IDs
├── handmade.rc           # Resource script (icons, version info)
├── handmade.ico          # Application icon
├── small.ico             # Small application icon
├── handmade.vcxproj      # Visual Studio project file
├── handmade.vcxproj.filters  # VS Solution Explorer file organization
├── handmade.slnx         # Visual Studio solution file
└── README.md             # This file
```

---

## How to Build

### Requirements
- Windows 10/11
- [Visual Studio 2022](https://visualstudio.microsoft.com/) with the **Desktop development with C++** workload

### Steps
1. Open `handmade.slnx` in Visual Studio
2. Select **x64 | Debug** (or Release) from the toolbar
3. Press **Ctrl+Shift+B** to build
4. Press **F5** to run

---

## Roadmap / Coming Soon

- [ ] Pixel back buffer (DIB section) for direct pixel rendering
- [ ] Game loop using `PeekMessage` for continuous frame updates
- [ ] Keyboard and mouse input handling
- [ ] Software rendering / drawing shapes and gradients
- [ ] Audio output

---

## Notes

- No external libraries or dependencies — only the Windows SDK
- The window class uses `CS_OWNDC | CS_HREDRAW | CS_VREDRAW` so the entire window repaints on every resize
- Debug output is visible in Visual Studio's **Output** window (View → Output) while running under the debugger

