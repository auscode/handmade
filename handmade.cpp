#include "handmade.h"

#define internal static 
#define local_persist static 
#define global_variable static 

global_variable bool Running;
global_variable BITMAPINFO BitmapInfo;
global_variable void* BitmapMemory;
global_variable HBITMAP BITMAPHANDLE;
global_variable HDC BitmapDeviceContext;

internal void ResizseDIBSection(int Width, int Height) {

    if (BITMAPHANDLE) {
		DeleteObject(BITMAPHANDLE);
    }
    if(!BitmapDeviceContext) {
        BitmapDeviceContext = CreateCompatibleDC(0);
    }
	//BITMAPINFO BitmapInfo;
    BitmapInfo.bmiHeader.biSize =sizeof(BitmapInfo.bmiHeader);
	BitmapInfo.bmiHeader.biWidth = Width;
    BitmapInfo.bmiHeader.biHeight = Height;
	BitmapInfo.bmiHeader.biPlanes = 1;
	BitmapInfo.bmiHeader.biBitCount = 32;
	BitmapInfo.bmiHeader.biCompression = BI_RGB;
	//BitmapInfo.bmiHeader.biSizeImage = 0;
	//BitmapInfo.bmiHeader.biXPelsPerMeter = 0;
	//BitmapInfo.bmiHeader.biYPelsPerMeter = 0;
	//BitmapInfo.bmiHeader.biClrUsed = 0;
	//BitmapInfo.bmiHeader.biClrImportant = 0;

    //void* BitmapMemory;
	//HDC DeviceContext = GetDC(0);
    BITMAPHANDLE =  CreateDIBSection(
        BitmapDeviceContext,
        &BitmapInfo,
        DIB_RGB_COLORS ,
        &BitmapMemory,
        NULL,
        NULL
    );
	//ReleaseDC(0, DeviceContext);

}

internal void Win32UpdateWindow(HDC DeviceContext, int X, int Y, int Width, int Height) {
    StretchDIBits(
		DeviceContext, 
        X, Y, Width, Height, 
        X, Y, Width, Height, 
        BitmapMemory,
        &BitmapInfo,
        DIB_RGB_COLORS,
        SRCCOPY
    );
}

LRESULT CALLBACK Win32MainWindowCalllback(HWND window, UINT message, WPARAM WParam,
                                     LPARAM LParam) {
  LRESULT RESULT = 0;
  switch (message) {
  case WM_SIZE: {
	  RECT ClientRect;
	GetClientRect(window, &ClientRect);
	int Width = ClientRect.right - ClientRect.left;
	int Height = ClientRect.bottom - ClientRect.top;
      ResizseDIBSection(Width, Height);
    OutputDebugStringA("WM_SIZE\n");
  } break;

  case WM_DESTROY: {
    //OutputDebugStringA("WM_DESTROY\n");
    //PostQuitMessage(0); 
    //return 0;
	  Running = false;
  } break;

  case WM_CLOSE: {
    //OutputDebugStringA("WM_CLOSE\n");
    //DestroyWindow(window);
	  Running = false;
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
    Win32UpdateWindow(DeviceContext, X, Y, Width, Height);
    //local_persist DWORD Operation = WHITENESS;
    //PatBlt(DeviceContext, X, Y, Width, Height, Operation);
    //if (Operation == WHITENESS) {
    //  Operation = BLACKNESS;
    //} else {
    //  Operation = WHITENESS;
    //}

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
  windowClass.lpfnWndProc = Win32MainWindowCalllback;
  windowClass.hInstance = Instance;
  windowClass.lpszClassName = L"PrayasTestWindow";

  if (RegisterClass(&windowClass)) {
    HWND WindowHandle = CreateWindowEx(
        0, windowClass.lpszClassName, L"Prayas",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, Instance, 0);
    if (WindowHandle) {
		Running = true;
      while (Running) {
        MSG Message;
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

  //MessageBoxA(0, "working", "Dialog", MB_OK | MB_ICONINFORMATION);
  return 0;
}
