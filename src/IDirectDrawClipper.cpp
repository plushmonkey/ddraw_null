#ifndef CINTERFACE
#define CINTERFACE
#endif

#include "IDirectDrawClipper.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <memory.h>
#include <string.h>

#include <format>
#include <string>
#include <string_view>

#define INTERFACE OglDirectDrawClipper

static OglDirectDrawClipperVtable vtable = {};

static void DisplayMessage(std::string_view msg) {
  // MessageBox(NULL, msg.data(), "DirectDrawClipper_null", MB_OK);
}

HRESULT __stdcall OglClipper_QueryInterface(OglDirectDrawClipper* This, REFIID riid, LPVOID FAR* ppvObj) {
  if (!*ppvObj) return E_INVALIDARG;

  if (!IsEqualGUID(riid, IID_IDirectDrawClipper)) {
    return E_NOINTERFACE;
  }

  OglDirectDrawClipper* clipper = (OglDirectDrawClipper*)malloc(sizeof(OglDirectDrawClipper));

  memcpy(&clipper->guid, &riid, sizeof(clipper->guid));
  clipper->lpVtbl = &vtable;
  clipper->ref = 1;

  *ppvObj = clipper;

  return S_OK;
}

ULONG __stdcall OglClipper_AddRef(OglDirectDrawClipper* This) {
  ULONG ret = ++This->ref;

  return ret;
}

ULONG __stdcall OglClipper_Release(OglDirectDrawClipper* This) {
  ULONG ret = --This->ref;

  if (ret == 0) {
    free(This);
  }

  return ret;
}

HRESULT __stdcall OglClipper_GetClipList(OglDirectDrawClipper* This, LPRECT, LPRGNDATA, LPDWORD) {
  return S_OK;
}

HRESULT __stdcall OglClipper_GetHWnd(OglDirectDrawClipper* This, HWND FAR* hwnd) {
  *hwnd = 0;
  return S_OK;
}

HRESULT __stdcall OglClipper_Initialize(OglDirectDrawClipper* This, LPDIRECTDRAW, DWORD) {
  return S_OK;
}

HRESULT __stdcall OglClipper_IsClipListChanged(OglDirectDrawClipper* This, BOOL FAR*) {
  return S_OK;
}

HRESULT __stdcall OglClipper_SetClipList(OglDirectDrawClipper* This, LPRGNDATA, DWORD) {
  return S_OK;
}

HRESULT __stdcall OglClipper_SetHWnd(OglDirectDrawClipper* This, DWORD, HWND) {
  return S_OK;
}

IDirectDrawClipper* __stdcall OglDirectDrawCreateClipper() {
  vtable.QueryInterface = OglClipper_QueryInterface;
  vtable.AddRef = OglClipper_AddRef;
  vtable.Release = OglClipper_Release;

  vtable.GetClipList = OglClipper_GetClipList;
  vtable.GetHWnd = OglClipper_GetHWnd;
  vtable.Initialize = OglClipper_Initialize;
  vtable.IsClipListChanged = OglClipper_IsClipListChanged;
  vtable.SetClipList = OglClipper_SetClipList;
  vtable.SetHWnd = OglClipper_SetHWnd;

  OglDirectDrawClipper* clipper = (OglDirectDrawClipper*)malloc(sizeof(OglDirectDrawClipper));

  memcpy(&clipper->guid, &IID_IDirectDrawClipper, sizeof(clipper->guid));
  clipper->lpVtbl = &vtable;
  IDirectDrawClipper_AddRef(clipper);

  return (IDirectDrawClipper*)clipper;
}
