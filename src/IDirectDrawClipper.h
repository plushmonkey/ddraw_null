#pragma once

#ifndef CINTERFACE
#define CINTERFACE
#define FUSE_MANUAL_CINTERFACE
#endif

#include <ddraw.h>

#ifdef INTERFACE
#undef INTERFACE
#endif
#define INTERFACE OglDirectDrawClipper

struct OglDirectDrawClipper;

struct OglDirectDrawClipperVtable {
  /*** IUnknown methods ***/
  STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
  STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
  STDMETHOD_(ULONG, Release) (THIS) PURE;

  /*** IDirectDrawClipper methods ***/
  STDMETHOD(GetClipList)(THIS_ LPRECT, LPRGNDATA, LPDWORD) PURE;
  STDMETHOD(GetHWnd)(THIS_ HWND FAR*) PURE;
  STDMETHOD(Initialize)(THIS_ LPDIRECTDRAW, DWORD) PURE;
  STDMETHOD(IsClipListChanged)(THIS_ BOOL FAR*) PURE;
  STDMETHOD(SetClipList)(THIS_ LPRGNDATA, DWORD) PURE;
  STDMETHOD(SetHWnd)(THIS_ DWORD, HWND) PURE;
};

struct OglDirectDrawClipper {
  OglDirectDrawClipperVtable* lpVtbl;

  ULONG ref;
  GUID guid;
};

IDirectDrawClipper* __stdcall OglDirectDrawCreateClipper();

#ifdef FUSE_MANUAL_CINTERFACE
#undef CINTERFACE
#undef FUSE_MANUAL_CINTERFACE
#endif

#ifdef INTERFACE
#undef INTERFACE
#endif
