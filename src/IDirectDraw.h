#pragma once

#ifndef CINTERFACE
#define CINTERFACE
#define FUSE_MANUAL_CINTERFACE
#endif

#include <ddraw.h>

#ifdef INTERFACE
#undef INTERFACE
#endif
#define INTERFACE OglDirectDraw

struct OglDirectDraw;

struct OglDirectDrawVtable {
  /*** IUnknown methods ***/
  STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
  STDMETHOD_(ULONG, AddRef)(THIS) PURE;
  STDMETHOD_(ULONG, Release)(THIS) PURE;
  /*** IDirectDraw methods ***/
  STDMETHOD(Compact)(THIS) PURE;
  STDMETHOD(CreateClipper)(THIS_ DWORD, LPDIRECTDRAWCLIPPER FAR*, IUnknown FAR*) PURE;
  STDMETHOD(CreatePalette)(THIS_ DWORD, LPPALETTEENTRY, LPDIRECTDRAWPALETTE FAR*, IUnknown FAR*) PURE;
  STDMETHOD(CreateSurface)(THIS_ LPDDSURFACEDESC2, LPDIRECTDRAWSURFACE7 FAR*, IUnknown FAR*) PURE;
  STDMETHOD(DuplicateSurface)(THIS_ LPDIRECTDRAWSURFACE7, LPDIRECTDRAWSURFACE7 FAR*) PURE;
  STDMETHOD(EnumDisplayModes)(THIS_ DWORD, LPDDSURFACEDESC2, LPVOID, LPDDENUMMODESCALLBACK2) PURE;
  STDMETHOD(EnumSurfaces)(THIS_ DWORD, LPDDSURFACEDESC2, LPVOID, LPDDENUMSURFACESCALLBACK2) PURE;
  STDMETHOD(FlipToGDISurface)(THIS) PURE;
  STDMETHOD(GetCaps)(THIS_ LPDDCAPS, LPDDCAPS) PURE;
  STDMETHOD(GetDisplayMode)(THIS_ LPDDSURFACEDESC2) PURE;
  STDMETHOD(GetFourCCCodes)(THIS_ LPDWORD, LPDWORD) PURE;
  STDMETHOD(GetGDISurface)(THIS_ LPDIRECTDRAWSURFACE7 FAR*) PURE;
  STDMETHOD(GetMonitorFrequency)(THIS_ LPDWORD) PURE;
  STDMETHOD(GetScanLine)(THIS_ LPDWORD) PURE;
  STDMETHOD(GetVerticalBlankStatus)(THIS_ LPBOOL) PURE;
  STDMETHOD(Initialize)(THIS_ GUID FAR*) PURE;
  STDMETHOD(RestoreDisplayMode)(THIS) PURE;
  STDMETHOD(SetCooperativeLevel)(THIS_ HWND, DWORD) PURE;
  STDMETHOD(SetDisplayMode)(THIS_ DWORD, DWORD, DWORD) PURE;
  STDMETHOD(WaitForVerticalBlank)(THIS_ DWORD, HANDLE) PURE;
  /*** Added in the v2 interface ***/
  STDMETHOD(GetAvailableVidMem)(THIS_ LPDDSCAPS2, LPDWORD, LPDWORD) PURE;
  /*** Added in the V4 Interface ***/
  STDMETHOD(GetSurfaceFromDC)(THIS_ HDC, LPDIRECTDRAWSURFACE7*) PURE;
  STDMETHOD(RestoreAllSurfaces)(THIS) PURE;
  STDMETHOD(TestCooperativeLevel)(THIS) PURE;
  STDMETHOD(GetDeviceIdentifier)(THIS_ LPDDDEVICEIDENTIFIER2, DWORD) PURE;
  /*** Added in the V7 Interface ***/
  STDMETHOD(StartModeTest)(THIS_ LPSIZE, DWORD, DWORD) PURE;
  STDMETHOD(EvaluateMode)(THIS_ DWORD, DWORD*) PURE;
};

struct OglDirectDraw {
  OglDirectDrawVtable* lpVtbl;

  ULONG ref;
  GUID guid;
};

IDirectDraw* __stdcall OglDirectDrawCreate();

#ifdef FUSE_MANUAL_CINTERFACE
#undef CINTERFACE
#undef FUSE_MANUAL_CINTERFACE
#endif

#ifdef INTERFACE
#undef INTERFACE
#endif
