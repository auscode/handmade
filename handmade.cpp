#include "handmade.h"

LRESULT CALLBACK MainWindowCalllback(HWND window, UINT message, WPARAM WParam,
                                     LPARAM LParam) {
  LRESULT RESULT = 0;
  switch (message) {
  case WM_SIZE: {
    OutputDebugStringA("WM_SIZE\n");
  } break;

  case WM_DESTROY: {
    OutputDebugStringA("WM_DESTROY\n");
    PostQuitMessage(0);
    return 0;
  } break;

  case WM_CLOSE: {
    OutputDebugStringA("WM_CLOSE\n");
    DestroyWindow(window);
  } break;

  case WM_ACTIVATEAPP: {
    OutputDebugStringA("WM_ACTIVATEAPP\n");
  } break;

  case WM_PAINT: {
    PAINTSTRUCT Paint;
    HDC DeviceContext = BeginPaint(window, &Paint);

    int X = Paint.rcPaint.left;
    int Y = Paint.rcPaint.top;
    int Width = Paint.rcPaint.right - Paint.rcPaint.left;
    int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
    static DWORD Operation = WHITENESS;
    PatBlt(DeviceContext, X, Y, Width, Height, Operation);
    if (Operation == WHITENESS) {
      Operation = BLACKNESS;
    } else {
      Operation = WHITENESS;
    }

    EndPaint(window, &Paint);
  } break;

  default: {
    OutputDebugStringA("DEFAULT HIT\n");
    RESULT = DefWindowProc(window, message, WParam, LParam);
  } break;
  }
  // return DefWindowProc(window, message, WParam, LParam);
  return RESULT;
}
int APIENTRY wWinMain(_In_ HINSTANCE Instance, _In_opt_ HINSTANCE PrevInstance,
                      _In_ LPWSTR commandline, _In_ int showCode) {

  WNDCLASSW windowClass = {};

  windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
  windowClass.lpfnWndProc = MainWindowCalllback;
  windowClass.hInstance = Instance;
  windowClass.lpszClassName = L"PrayasTestWindow";

  if (RegisterClass(&windowClass)) {
    HWND WindowHandle = CreateWindowEx(
        0, windowClass.lpszClassName, L"Prayas",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, Instance, 0);
    if (WindowHandle) {
      MSG Message;
      for (;;) {
        BOOL msgRes = GetMessage(&Message, 0, 0, 0);
        if (msgRes > 0) {
          TranslateMessage(&Message);
          DispatchMessage(&Message);
        } else {
          break;
        }
      }
    } else {
    }
  } else {
  }

  MessageBoxA(0, "working", "Dialog", MB_OK | MB_ICONINFORMATION);
  return 0;
}
