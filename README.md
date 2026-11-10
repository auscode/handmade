# Handmade — Win32 Game from Scratch

A Win32 application built from scratch in C++ — no engine, no framework, just the Windows API and raw code.
Inspired by the [Handmade Hero](https://handmadehero.org/) project by Casey Muratori.

---

## What It Does (So Far)

- Creates a native Win32 window using `RegisterClassW` and `CreateWindowEx`
- Handles core window messages (`WM_PAINT`, `WM_SIZE`, `WM_CLOSE`, `WM_DESTROY`, `WM_ACTIVATEAPP`)
- Allocates a **DIB (Device Independent Bitmap) back buffer** — a region of memory where pixels can be written directly
- Resizes the back buffer automatically whenever the window is resized (`WM_SIZE`)
- Blits the back buffer to the window every frame using `StretchDIBits`
- Logs window events to the debug output via `OutputDebugStringA` (visible in DebugView or VS Output window)
- Uses a `Running` boolean flag to control the main loop — either `WM_CLOSE` or `WM_DESTROY` sets it to `false` to exit cleanly

---

## Code Architecture

### Macros (readability helpers)
```cpp
#define internal        static   // function only visible in this file
#define local_persist   static   // variable persists across calls
#define global_variable static   // file-scope global
```

### Global State
| Variable | Type | Purpose |
|---|---|---|
| `Running` | `bool` | Controls the main message loop |
| `BitmapInfo` | `BITMAPINFO` | Describes the DIB format (width, height, bit depth) |
| `BitmapMemory` | `void*` | Raw pointer to the pixel data |
| `BITMAPHANDLE` | `HBITMAP` | GDI handle to the DIB bitmap |
| `BitmapDeviceContext` | `HDC` | Off-screen DC used to hold the DIB |

### Key Functions
- **`ResizeDIBSection(Width, Height)`** — Frees the old bitmap, creates a new 32-bit DIB section sized to the window, and stores a pointer to its pixel memory
- **`Win32UpdateWindow(DC, X, Y, Width, Height)`** — Calls `StretchDIBits` to copy the back buffer to the real window DC
- **`Win32MainWindowCallback(...)`** — Handles all window messages; resizes the buffer on `WM_SIZE`, blits on `WM_PAINT`, sets `Running = false` on close/destroy
- **`wWinMain(...)`** — Registers the window class, creates the window, runs the message loop while `Running` is `true`

---

## Project Structure

```
handmade/
├── handmade.cpp          # Main source file — entry point, window callback, rendering
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

### Viewing Debug Output
- In Visual Studio: **View → Output** → set dropdown to **"Debug"**
- Outside VS: use [Sysinternals DebugView](https://learn.microsoft.com/en-us/sysinternals/downloads/debugview)

---

## Roadmap / Coming Soon

- [x] Basic Win32 window with message loop
- [x] DIB back buffer (32-bit pixel memory allocated and resized with the window)
- [x] `StretchDIBits` blit from back buffer to window
- [x] Clean exit via `Running` flag
- [ ] Write actual pixel colors into `BitmapMemory` (gradients, patterns)
- [ ] Game loop using `PeekMessage` for continuous frame updates
- [ ] Keyboard and mouse input handling
- [ ] Software rendering — shapes, gradients, sprites
- [ ] Audio output

---

## Notes

- No external libraries or dependencies — only the Windows SDK
- The DIB is 32-bit (`biBitCount = 32`), giving 4 bytes per pixel (Blue, Green, Red, unused/alpha)
- The window class uses `CS_OWNDC | CS_HREDRAW | CS_VREDRAW` so the entire window repaints on every resize
- `BitmapDeviceContext` is created once and reused — it is never released during the lifetime of the app
