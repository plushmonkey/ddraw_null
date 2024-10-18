#include <format>
#include <string>
#include <string_view>

#include "IDirectDraw.h"
#include "IDirectDrawClipper.h"

//
#include <detours.h>

static int(WINAPI* RealSetDIBitsToDevice)(_In_ HDC hdc, _In_ int xDest, _In_ int yDest, _In_ DWORD w, _In_ DWORD h,
                                          _In_ int xSrc, _In_ int ySrc, _In_ UINT StartScan, _In_ UINT cLines,
                                          _In_ CONST VOID* lpvBits, _In_ CONST BITMAPINFO* lpbmi,
                                          _In_ UINT ColorUse) = SetDIBitsToDevice;

static void DisplayMessage(std::string_view msg) {
  // MessageBox(NULL, msg.data(), "render_ogl", MB_OK);
}

extern "C" {

HRESULT __stdcall DirectDrawCreate(GUID* lpGUID, LPDIRECTDRAW* lplpDD, IUnknown* pUnkOuter) {
  *lplpDD = OglDirectDrawCreate();
  return S_OK;
}

HRESULT __stdcall DirectDrawCreateClipper(DWORD dwFlags, LPDIRECTDRAWCLIPPER* lplpDDClipper, IUnknown* pUnkOuter) {
  *lplpDDClipper = OglDirectDrawCreateClipper();
  return S_OK;
}
}

int WINAPI OverrideSetDIBitsToDevice(_In_ HDC hdc, _In_ int xDest, _In_ int yDest, _In_ DWORD w, _In_ DWORD h,
                                     _In_ int xSrc, _In_ int ySrc, _In_ UINT StartScan, _In_ UINT cLines,
                                     _In_ CONST VOID* lpvBits, _In_ CONST BITMAPINFO* lpbmi, _In_ UINT ColorUse) {
  return cLines;
}

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID reserved) {
  switch (dwReason) {
    case DLL_PROCESS_ATTACH: {
      DetourRestoreAfterWith();

      DetourTransactionBegin();
      DetourUpdateThread(GetCurrentThread());
      DetourAttach(&(PVOID&)RealSetDIBitsToDevice, OverrideSetDIBitsToDevice);
      DetourTransactionCommit();
    } break;
  }

  return TRUE;
}
