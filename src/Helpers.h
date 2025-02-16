﻿/******************************************************************************
*                                                                             *
*                                                                             *
* Notepad3                                                                    *
*                                                                             *
* Helpers.h                                                                   *
*   Definitions for general helper functions and macros                       *
*   Based on code from Notepad2, (c) Florian Balmer 1996-2011                 *
*                                                                             *
*                                                  (c) Rizonesoft 2008-2019   *
*                                                    https://rizonesoft.com   *
*                                                                             *
*                                                                             *
*******************************************************************************/
#pragma once
#ifndef _NP3_HELPERS_H_
#define _NP3_HELPERS_H_

#include "TypeDefs.h"

#include <math.h>
#include <shlwapi.h>
#include <versionhelpers.h>

// ============================================================================
// ---  Disable/Enable some CodeAnalysis Warnings  ---

#pragma warning ( disable: 26451 28159)
//#pragma warning ( enable : 6001 )

// ============================================================================

// ============================================================================

#ifndef _W
#define __CC(p,s) p ## s
#define _W(s)  __CC(L,s)
#endif

#ifndef _STRG
#define _STRINGIFY(s) #s
#define _STRG(s)  _STRINGIFY(s)
#endif

#define UNUSED(expr) (void)(expr)
#define SIZEOF(ar) sizeof(ar)
//#define ARRAYSIZE(A) (assert(!(sizeof(A) % sizeof(*(A)))), (sizeof(A) / sizeof((A)[0])))
#define COUNTOF(ar) ARRAYSIZE(ar)
#define CSTRLEN(s)  (COUNTOF(s)-1)

#define NOOP ((void)0)

// ============================================================================

// direct heap allocation
#if (defined(_DEBUG) || defined(DEBUG)) && !defined(NDEBUG)
  #define DEFAULT_ALLOC_FLAGS (HEAP_GENERATE_EXCEPTIONS)
#else
  #define DEFAULT_ALLOC_FLAGS (0)
#endif

inline LPVOID AllocMem(size_t numBytes, DWORD dwFlags)
{
  return HeapAlloc(Globals.hndlProcessHeap, (dwFlags | DEFAULT_ALLOC_FLAGS), numBytes);
}

inline bool FreeMem(LPVOID lpMemory)
{
  return (lpMemory ? HeapFree(Globals.hndlProcessHeap, 0, lpMemory) : true);
}

inline size_t SizeOfMem(LPCVOID lpMemory)
{
  return (lpMemory ? HeapSize(Globals.hndlProcessHeap, 0, lpMemory) : 0);
}

// ============================================================================

#if (defined(_DEBUG) || defined(DEBUG)) && !defined(NDEBUG)
void DbgLog(const char *fmt, ...);
#else
#define DbgLog(fmt, ...) NOOP
#endif

// ============================================================================

// min/max
#define _min_(x,y) (((x) < (y)) ? (x) : (y))
inline int min_i(const int x, const int y) { return (x < y) ? x : y; }
inline unsigned int min_u(const unsigned int x, const unsigned int y) { return (x < y) ? x : y; }
inline long min_l(const long x, const long y) { return (x < y) ? x : y; }
inline size_t min_s(const size_t x, const size_t y) { return (x < y) ? x : y; }
inline DocPos min_p(const DocPos x, const DocPos y) { return (x < y) ? x : y; }
inline DocLn min_ln(const DocLn x, const DocLn y) { return (x < y) ? x : y; }
inline DocPosCR min_cr(const DocPosCR x, const DocPosCR y) { return (x < y) ? x : y; }

#define _max_(x,y) (((x) > (y)) ? (x) : (y))
inline int max_i(int x, int y) { return (x > y) ? x : y; }
inline unsigned int max_u(unsigned int x, unsigned int y) { return (x > y) ? x : y; }
inline long max_l(const long x, const long y) { return (x > y) ? x : y; }
inline size_t max_s(const size_t x, const size_t y) { return (x > y) ? x : y; }
inline DocPos max_p(const DocPos x, const DocPos y) { return (x > y) ? x : y; }
inline DocLn max_ln(const DocLn x, const DocLn y) { return (x > y) ? x : y; }
inline DocPosCR max_cr(const DocPosCR x, const DocPosCR y) { return (x > y) ? x : y; }

inline DocPos abs_p(const DocPos x) { return (x >= 0LL) ? x : (0LL - x); }

// swap 
inline void swapi(int* a, int* b) { int t = *a;  *a = *b;  *b = t; }
inline void swapos(DocPos* a, DocPos* b) { DocPos t = *a;  *a = *b;  *b = t; }

// clamp
inline int clampi(int x, int lower, int upper) {
  return (x < lower) ? lower : ((x > upper) ? upper : x);
}

inline unsigned clampu(unsigned x, unsigned lower, unsigned upper) {
  return (x < lower) ? lower : ((x > upper) ? upper : x);
}

inline unsigned clampul(unsigned long x, unsigned long lower, unsigned long upper) {
  return (x < lower) ? lower : ((x > upper) ? upper : x);
}

inline DocPos clampp(DocPos x, DocPos lower, DocPos upper) {
  return (x < lower) ? lower : ((x > upper) ? upper : x);
}

// Is the character an octal digit?
inline bool IsDigitA(const CHAR ch) { return ((ch >= '0') && (ch <= '9')); }
inline bool IsDigitW(const WCHAR wch) { return ((wch >= L'0') && (wch <= L'9')); }

// Is the character a white space char?
inline bool IsBlankChar(const CHAR ch) { return ((ch == ' ') || (ch == '\t')); }
inline bool IsBlankCharW(const WCHAR wch) { return ((wch == L' ') || (wch == L'\t')); }

inline int float2int(const float f) { return (int)lroundf(f); }
inline float Round10th(const float f) { return (float)float2int(f * 10.0f) / 10; }
inline bool HasNonZeroFraction(const float f) { return ((float2int(f * 10.0f) % 10) != 0); }

inline bool IsKeyDown(int key) { return (((GetKeyState(key) >> 8) & 0xff) != 0); }
inline bool IsAsyncKeyDown(int key) { return (((GetAsyncKeyState(key) >> 8) & 0xff) != 0); }

// ----------------------------------------------------------------------------

#define SendWMCommandEx(hwnd, id, extra)  SendMessage(hwnd, WM_COMMAND, MAKEWPARAM((id), (extra)), 0)
#define SendWMCommand(hwnd, id)           SendWMCommandEx(hwnd, (id), 1)
#define PostWMCommand(hwnd, id)           PostMessage(hwnd, WM_COMMAND, MAKEWPARAM((id), 1), 0)

//==== StrIs(Not)Empty() =============================================

inline bool StrIsEmptyA(LPCSTR s) { return (!s || (*s == '\0')); }
inline bool StrIsEmptyW(LPCWSTR s) { return (!s || (*s == L'\0')); }

#if defined(UNICODE) || defined(_UNICODE)
#define StrIsEmpty(s)     StrIsEmptyW(s)
#define StrIsNotEmpty(s)  (!StrIsEmptyW(s))
#else
#define StrIsEmpty(s)     StrIsEmptyA(s)
#define StrIsNotEmpty(s)  (!StrIsEmptyA(s))
#endif

//==== Ini-File Handling =============================================

#define IniGetString(lpSection,lpName,lpDefault,lpReturnedStr,nSize) GetPrivateProfileString(lpSection,lpName,(lpDefault),(lpReturnedStr),(nSize),Globals.IniFile)
#define IniGetInt(lpSection,lpName,nDefault)                         GetPrivateProfileInt(lpSection,lpName,(nDefault),Globals.IniFile)
#define IniGetBool(lpSection,lpName,nDefault)                        (GetPrivateProfileInt(lpSection,lpName,(int)(nDefault),Globals.IniFile) ? true : false)
#define IniSetString(lpSection,lpName,lpString)                      WritePrivateProfileString(lpSection,lpName,(lpString),Globals.IniFile)

inline void IniClearSection(LPCWSTR lpSection, bool bDelete) {
  if (StrIsEmpty(Globals.IniFile)) { return; }
  WritePrivateProfileSection(lpSection, (bDelete ? NULL : L""), Globals.IniFile);
}
void IniClearAllSections(LPCWSTR lpszPrefix, LPCWSTR lpszIniFile, bool bDelete);

// ----------------------------------------------------------------------------

inline bool IniSetInt(LPCWSTR lpSection, LPCWSTR lpName, int i) {
  WCHAR tch[32] = { L'\0' }; StringCchPrintf(tch, COUNTOF(tch), L"%i", i); return IniSetString(lpSection, lpName, tch);
}

#define IniSetBool(lpSection,lpName,nValue)    IniSetInt(lpSection,lpName,((nValue) ? 1 : 0))
#define LoadIniSection(lpSection,lpBuf,cchBuf) GetPrivateProfileSection(lpSection,lpBuf,(cchBuf),Globals.IniFile)
#define SaveIniSection(lpSection,lpBuf)        WritePrivateProfileSection(lpSection,lpBuf,Globals.IniFile)

int IniSectionGetString(LPCWSTR lpCachedIniSection, LPCWSTR lpName, LPCWSTR lpDefault, LPWSTR lpReturnedString, int cchReturnedString);
int IniSectionGetInt(LPCWSTR lpCachedIniSection, LPCWSTR lpName, int iDefault);
UINT IniSectionGetUInt(LPCWSTR lpCachedIniSection, LPCWSTR lpName, UINT uDefault);
DocPos IniSectionGetPos(LPCWSTR lpCachedIniSection, LPCWSTR lpName, DocPos posDefault);
inline bool IniSectionGetBool(LPCWSTR lpCachedIniSection, LPCWSTR lpName, bool bDefault) {
  return (IniSectionGetInt(lpCachedIniSection, lpName, ((bDefault) ? 1 : 0)) ? true : false);
}

bool IniSectionSetString(LPWSTR lpCachedIniSection,LPCWSTR lpName,LPCWSTR lpString);

inline bool IniSectionSetInt(LPWSTR lpCachedIniSection,LPCWSTR lpName, int i) {
  WCHAR tch[32]={L'\0'}; StringCchPrintf(tch,COUNTOF(tch),L"%i",i); 
  return IniSectionSetString(lpCachedIniSection,lpName,tch);
}
inline bool IniSectionSetBool(LPWSTR lpCachedIniSection, LPCWSTR lpName, bool b) {
  return IniSectionSetInt(lpCachedIniSection, lpName, (b ? 1 : 0));
}
inline bool IniSectionSetPos(LPWSTR lpCachedIniSection, LPCWSTR lpName, DocPos pos){
  WCHAR tch[64] = { L'\0' }; StringCchPrintf(tch, COUNTOF(tch), DOCPOSFMTW, pos); 
  return IniSectionSetString(lpCachedIniSection, lpName, tch);
}

// ----------------------------------------------------------------------------

inline COLORREF GetBackgroundColor(HWND hwnd) { return GetBkColor(GetDC(hwnd)); }

// ----------------------------------------------------------------------------

//#define Is2k()    (g_uWinVer >= 0x0500)
#define IsXP()     IsWindowsXPOrGreater()        // Indicates if the current OS version matches,or is greater than,the Windows XP version.
#define IsXP1()    IsWindowsXPSP1OrGreater()     // Indicates if the current OS version matches,or is greater than,the Windows XP with Service Pack 1 (SP1)version.
#define IsXP2()    IsWindowsXPSP2OrGreater()     // Indicates if the current OS version matches,or is greater than,the Windows XP with Service Pack 2 (SP2)version.
#define IsXP3()    IsWindowsXPSP3OrGreater()     // Indicates if the current OS version matches,or is greater than,the Windows XP with Service Pack 3 (SP3)version.

#define IsVista()  IsWindowsVistaOrGreater()     // Indicates if the current OS version matches,or is greater than,the Windows Vista version.
#define IsVista1() IsWindowsVistaSP1OrGreater()  // Indicates if the current OS version matches,or is greater than,the Windows Vista with Service Pack 1 (SP1)version.
#define IsVista2() IsWindowsVistaSP2OrGreater()  // Indicates if the current OS version matches,or is greater than,the Windows Vista with Service Pack 2 (SP2)version.

#define IsWin7()   IsWindows7OrGreater()         // Indicates if the current OS version matches,or is greater than,the Windows 7 version.
#define IsWin71()  IsWindows7SP1OrGreater()      // Indicates if the current OS version matches,or is greater than,the Windows 7 with Service Pack 1 (SP1)version.
#define IsWin8()   IsWindows8OrGreater()         // Indicates if the current OS version matches,or is greater than,the Windows 8 version.
#define IsWin81()  IsWindows8Point1OrGreater()   // Indicates if the current OS version matches,or is greater than,the Windows 8.1 version.
                                                 //   For Windows 10,IsWindows8Point1OrGreater returns false unless the application contains a manifest that includes
                                                 //   a compatibility section that contains the GUIDs that designate Windows 8.1 and/or Windows 10.

#define IsWin10()  IsWindows10OrGreater()        // Indicates if the current OS version matches, or is greater than, the Windows 10 version.
                                                 //   For Windows 10,IsWindows10OrGreater returns false unless the application contains a manifest that includes
                                                 //   a compatibility section that contains the GUID that designates Windows 10.

#define IsWinServer() IsWindowsServer()          // Indicates if the current OS is a Windows Server release.
                                                 //   Applications that need to distinguish between server and client versions of Windows should call this function.

// ----------------------------------------------------------------------------

#define RGB_GET_R(color)    ((BYTE)((0xFF)&(color)))
#define RGB_GET_G(color)    ((BYTE)(((0xFF<<8)&(color))>>8))
#define RGB_GET_B(color)    ((BYTE)(((0xFF<<16)&(color))>>16))

// ----------------------------------------------------------------------------

bool SetClipboardTextW(HWND hwnd, LPCWSTR pszTextW, size_t cchTextW);

// ----------------------------------------------------------------------------

DPI_T GetCurrentDPI(HWND hwnd);
DPI_T GetCurrentPPI(HWND hwnd);

void UpdateWindowLayoutForDPI(HWND hWnd, int x_96dpi, int y_96dpi, int w_96dpi, int h_96dpi);
HBITMAP ResizeImageForCurrentDPI(HBITMAP hbmp);
inline int ScaleIntToCurrentDPI(int val) { return MulDiv((val), Globals.CurrentDPI.y, USER_DEFAULT_SCREEN_DPI); }
inline int ScaleToCurrentDPI(float fVal) { return float2int((fVal * Globals.CurrentDPI.y) / (float)USER_DEFAULT_SCREEN_DPI); }
inline int ScaleIntFontSize(int val) { return MulDiv((val), Globals.CurrentDPI.y, Globals.CurrentPPI.y); }
inline int ScaleFontSize(float fSize) { return float2int((fSize * Globals.CurrentDPI.y) / (float)Globals.CurrentPPI.y); }
inline int ScaleFractionalFontSize(float fSize) { return float2int((fSize * 10.0f * Globals.CurrentDPI.y) / (float)Globals.CurrentPPI.y) * 10; }

int GetSystemMetricsEx(int nValue);

// ----------------------------------------------------------------------------

inline void GetCurrentMonitorResolution(HWND hwnd, int* pCXScreen, int* pCYScreen)
{
  HMONITOR const hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
  MONITORINFO mi;
  ZeroMemory(&mi, sizeof(MONITORINFO));
  mi.cbSize = sizeof(mi);
  GetMonitorInfo(hMonitor, &mi);
  *pCXScreen = (mi.rcMonitor.right - mi.rcMonitor.left);
  *pCYScreen = (mi.rcMonitor.bottom - mi.rcMonitor.top);
}

inline bool IsFullHDOrHigher(HWND hwnd, int resX, int resY) 
{
  int cxScreen, cyScreen;
  GetCurrentMonitorResolution(hwnd, &cxScreen, &cyScreen);
  if (resX <= 0) { resX = cxScreen; }
  if (resY <= 0) { resY = cxScreen; }
  return ((resX >= 1920) && (resY >= 1080));
}

inline float GetBaseFontSize(HWND hwnd) { return (IsFullHDOrHigher(hwnd, -1, -1) ? 11.0f : 10.0f); }

// ----------------------------------------------------------------------------

HRESULT PrivateSetCurrentProcessExplicitAppUserModelID(PCWSTR AppID);
bool IsElevated();
bool IsUserAdmin();
//bool SetExplorerTheme(HWND);


bool BitmapMergeAlpha(HBITMAP hbmp,COLORREF crDest);
bool BitmapAlphaBlend(HBITMAP hbmp,COLORREF crDest,BYTE alpha);
bool BitmapGrayScale(HBITMAP hbmp);
bool VerifyContrast(COLORREF cr1,COLORREF cr2);
bool IsFontAvailable(LPCWSTR lpszFontName);

bool IsCmdEnabled(HWND hwnd, UINT uId);


#define SetBtn(b) ((b) ? BST_CHECKED : BST_UNCHECKED)

inline bool IsButtonChecked(HWND hwnd, int iButtonID) { return (IsDlgButtonChecked(hwnd, iButtonID) == BST_CHECKED); }
inline bool IsButtonIntermediate(HWND hwnd, int iButtonID) { return (IsDlgButtonChecked(hwnd, iButtonID) == BST_INDETERMINATE); }
inline bool IsButtonUnchecked(HWND hwnd, int iButtonID) { return (IsDlgButtonChecked(hwnd, iButtonID) == BST_UNCHECKED); }


#define EnableCmd(hmenu,id,b) EnableMenuItem((hmenu),(id),(b)?MF_BYCOMMAND|MF_ENABLED:MF_BYCOMMAND|MF_GRAYED)
#define CheckCmd(hmenu,id,b)  CheckMenuItem((hmenu),(id),(b)?MF_BYCOMMAND|MF_CHECKED:MF_BYCOMMAND|MF_UNCHECKED)

#define EnableTool(htbar,id,b) SendMessage(htbar,TB_ENABLEBUTTON,id, MAKELONG(((b) ? 1 : 0), 0))
#define CheckTool(htbar,id,b)  SendMessage(htbar,TB_CHECKBUTTON,id, MAKELONG((b),0))

#define EnableCmdPos(hmenu,pos,b) EnableMenuItem((hmenu),(pos),(b)?MF_BYPOSITION|MF_ENABLED:MF_BYPOSITION|MF_GRAYED)
#define CheckCmdPos(hmenu,pos,b)  CheckMenuItem((hmenu),(pos),(b)?MF_BYPOSITION|MF_CHECKED:MF_BYPOSITION|MF_UNCHECKED)


bool GetKnownFolderPath(REFKNOWNFOLDERID, LPWSTR lpOutPath, size_t cchCount);
void PathRelativeToApp(LPWSTR lpszSrc,LPWSTR lpszDest,int cchDest,bool,bool,bool);
void PathAbsoluteFromApp(LPWSTR lpszSrc,LPWSTR lpszDest,int cchDest,bool);

bool PathIsLnkFile(LPCWSTR pszPath);
bool PathGetLnkPath(LPCWSTR pszLnkFile,LPWSTR pszResPath,int cchResPath);
bool PathIsLnkToDirectory(LPCWSTR pszPath,LPWSTR pszResPath,int cchResPath);
bool PathCreateDeskLnk(LPCWSTR pszDocument);
bool PathCreateFavLnk(LPCWSTR pszName,LPCWSTR pszTarget,LPCWSTR pszDir);

void  ExpandEnvironmentStringsEx(LPWSTR lpSrc, DWORD dwSrc);
void  PathCanonicalizeEx(LPWSTR lpszPath, DWORD cchBuffer);
DWORD GetLongPathNameEx(LPWSTR lpszPath, DWORD cchBuffer);
void  PathGetDisplayName(LPWSTR lpszDestPath, DWORD cchDestBuffer, LPCWSTR lpszSourcePath);
DWORD NormalizePathEx(LPWSTR lpszPath, DWORD cchBuffer, bool bRealPath, bool bSearchPathIfRelative);


bool StrLTrim(LPWSTR pszSource,LPCWSTR pszTrimChars);

inline bool TrimStringA(LPSTR lpString) {
  if (!lpString || !*lpString) { return false; }
  StrTrimA(lpString, " ");
  return true;
};

inline bool TrimStringW(LPWSTR lpString) {
  if (!lpString || !*lpString) { return false; }
  StrTrimW(lpString, L" ");
  return true;
};

#if (defined(UNICODE) || defined(_UNICODE))
#define TrimString TrimStringW
#else
#define TrimString TrimStringA
#endif

bool ExtractFirstArgument(LPCWSTR lpArgs, LPWSTR lpArg1, LPWSTR lpArg2, int len);

void PrepareFilterStr(LPWSTR lpFilter);

void StrTab2Space(LPWSTR lpsz);
void PathFixBackslashes(LPWSTR lpsz);


size_t FormatNumberStr(LPWSTR lpNumberStr, size_t cch, int fixedWidth);
bool SetDlgItemIntEx(HWND hwnd,int nIdItem,UINT uValue);


UINT    GetDlgItemTextW2MB(HWND hDlg,int nIDDlgItem,LPSTR lpString,int nMaxCount);
UINT    SetDlgItemTextMB2W(HWND hDlg,int nIDDlgItem,LPSTR lpString);
LRESULT ComboBox_AddStringMB2W(HWND hwnd,LPCSTR lpString);


UINT CodePageFromCharSet(UINT uCharSet);
UINT CharSetFromCodePage(UINT uCodePage);


//==== MRU Functions ==========================================================

LPMRULIST MRU_Create(LPCWSTR pszRegKey,int iFlags,int iSize);
bool      MRU_Destroy(LPMRULIST pmru);
bool      MRU_Add(LPMRULIST pmru, LPCWSTR pszNew, cpi_enc_t iEnc, DocPos iPos, LPCWSTR pszBookMarks);
bool      MRU_FindFile(LPMRULIST pmru,LPCWSTR pszFile,int* iIndex);
bool      MRU_AddFile(LPMRULIST pmru, LPCWSTR pszFile, bool, bool, cpi_enc_t iEnc, DocPos iPos, LPCWSTR pszBookMarks);
bool      MRU_Delete(LPMRULIST pmru,int iIndex);
bool      MRU_DeleteFileFromStore(LPMRULIST pmru,LPCWSTR pszFile);
bool      MRU_Empty(LPMRULIST pmru);
int       MRU_Enum(LPMRULIST pmru,int iIndex,LPWSTR pszItem,int cchItem);
bool      MRU_Load(LPMRULIST pmru);
bool      MRU_Save(LPMRULIST pmru);
bool      MRU_MergeSave(LPMRULIST pmru,bool,bool,bool);
#define   MRU_Count(pmru) MRU_Enum((pmru), 0, NULL, 0)

//==== UnSlash Functions ======================================================
void TransformBackslashes(char* pszInput,bool,UINT cpEdit,int* iReplaceMsg);
void TransformMetaChars(char* pszInput,bool,int iEOLMode);

//==== MinimizeToTray Functions - see comments in Helpers.c ===================
bool GetDoAnimateMinimize(VOID);
VOID MinimizeWndToTray(HWND hWnd);
VOID RestoreWndFromTray(HWND hWnd);

// console helper from Print.cpp
//void RedirectIOToConsole();

//==== StrCut methods ===================

CHAR*  StrCutIA(CHAR* s,const CHAR* pattern);
WCHAR* StrCutIW(WCHAR* s,const WCHAR* pattern);
#if defined(UNICODE) || defined(_UNICODE)  
#define StrCutI StrCutIW
#else
#define StrCutI _StrCutIA
#endif


//==== StrNextTok methods ===================
CHAR*  StrNextTokA(CHAR* strg, const CHAR* tokens);
WCHAR* StrNextTokW(WCHAR* strg, const WCHAR* tokens);
#if defined(UNICODE) || defined(_UNICODE)  
#define StrNextTok StrNextTokW
#else
#define StrNextTok StrNextTokA
#endif

// ----------------------------------------------------------------------------

bool StrDelChrA(LPSTR pszSource, LPCSTR pCharsToRemove);

//==== StrSafe lstrlen() =======================================================
inline size_t StringCchLenA(LPCSTR s, size_t n) { 
  size_t len = (n ? n : STRSAFE_MAX_CCH); return (size_t)(!s ? 0 : (SUCCEEDED(StringCchLengthA(s, len, &len)) ? len : n));
}
inline size_t StringCchLenW(LPCWSTR s, size_t n) { 
  size_t len = (n ? n : STRSAFE_MAX_CCH); return (size_t)(!s ? 0 : (SUCCEEDED(StringCchLengthW(s, len, &len)) ? len : n));
}

#if defined(UNICODE) || defined(_UNICODE)  
#define StringCchLen(s,n)  StringCchLenW((s),(n))
#else
#define StringCchLen(s,n)  StringCchLenA((s),(n))
#endif

// ----------------------------------------------------------------------------

inline char* StrEndA(const char* pStart, size_t siz) {
  return (char*)(pStart + StringCchLenA(pStart, siz));
}

inline WCHAR* StrEndW(const WCHAR* pStart, size_t siz) {
  return (WCHAR*)(pStart + StringCchLenW(pStart, siz));
}

#if defined(UNICODE) || defined(_UNICODE)  
#define StrEnd(s,n) StrEndW((s),(n))
#else
#define StrEnd(s,n) StrEndA((s),(n))
#endif

//==== StrSafe lstrcmp(),lstrcmpi() =============================================

// NOTE: !!! differences in AutoCompleteList depending compare functions (CRT vs. Shlwapi)) !!!

#define StringCchCompareNA(s1,l1,s2,l2)   StrCmpNA((s1),(s2),min_i((int)(l1),(int)(l2)))
//#define StringCchCompareNA(s1,l1,s2,l2)   strncmp((s1),(s2),min_s((l1),(l2)))
#define StringCchCompareXA(s1,s2)         StrCmpA((s1),(s2))
//#define StringCchCompareXA(s1,s2)         strcmp((s1),(s2))

#define StringCchCompareNIA(s1,l1,s2,l2)  StrCmpNIA((s1),(s2),min_i((int)(l1),(int)(l2)))
//#define StringCchCompareNIA(s1,l1,s2,l2)  _strnicmp((s1),(s2),min_s((l1),(l2)))
#define StringCchCompareXIA(s1,s2)        StrCmpIA((s1),(s2))
//#define StringCchCompareXIA(s1,s2)        _stricmp((s1),(s2))


#define StringCchCompareNW(s1,l1,s2,l2)   StrCmpNW((s1),(s2),min_i((int)(l1),(int)(l2)))
#define StringCchCompareXW(s1,s2)         StrCmpW((s1),(s2))

#define StringCchCompareNIW(s1,l1,s2,l2)  StrCmpNIW((s1),(s2),min_i((int)(l1),(int)(l2)))
#define StringCchCompareXIW(s1,s2)        StrCmpIW((s1),(s2))

#if defined(UNICODE) || defined(_UNICODE)  
#define StringCchCompareN(s1,l1,s2,l2)   StringCchCompareNW((s1),(l1),(s2),(l2))
#define StringCchCompareX(s1,s2)         StringCchCompareXW((s1),(s2))
#define StringCchCompareNI(s1,l1,s2,l2)  StringCchCompareNIW((s1),(l1),(s2),(l2))
#define StringCchCompareXI(s1,s2)        StringCchCompareXIW((s1),(s2))
#else
#define StringCchCompareN(s1,l1,s2,l2)   StringCchCompareNA((s1),(l1),(s2),(l2))
#define StringCchCompareX(s1,s2)         StringCchCompareXA((s1),(s2))
#define StringCchCompareNI(s1,l1,s2,l2)  StringCchCompareNIA((s1),(l1),(s2),(l2))
#define StringCchCompareXI(s1,s2)        StringCchCompareXIA((s1),(s2))
#endif

#ifdef __cplusplus
#undef NULL
#define NULL nullptr
#endif

// ----------------------------------------------------------------------------

// Is the character an octal digit?
#define IsOctalDigit(ch) (((ch) >= '0') && ((ch) <= '7'))

// If the character is an hexa digit, get its value.
inline int GetHexDigit(char ch) {
  if (ch >= '0' && ch <= '9') { return ch - '0'; }
  if (ch >= 'A' && ch <= 'F') { return ch - 'A' + 10; }
  if (ch >= 'a' && ch <= 'f') { return ch - 'a' + 10; }
  return -1;
}

// ----------------------------------------------------------------------------

void UrlUnescapeEx(LPWSTR lpURL, LPWSTR lpUnescaped, DWORD* pcchUnescaped);

int ReadStrgsFromCSV(LPCWSTR wchCSVStrg, prefix_t sMatrix[], int iCount, int iLen, LPCWSTR sDefault);
int ReadVectorFromString(LPCWSTR wchStrg, int iVector[], int iCount, int iMin, int iMax, int iDefault);

inline bool Char2IntW(LPCWSTR str, int* value) {
  LPWSTR end;
  *value = (int)wcstol(str, &end, 10);
  return (str != end);
}
bool Char2FloatW(WCHAR* wnumber, float* fresult);
void Float2String(float fValue, LPWSTR lpszStrg, int cchSize);

// ----------------------------------------------------------------------------

// including <pathcch.h> and linking against pathcch.lib
// api-ms-win-core-path-l1-1-0.dll  library : Minimum supported client is Windows 8 :-/
// so switch back to previous (deprecated) methods:
inline HRESULT PathCchAppend(PWSTR p,size_t l,PCWSTR a)          { UNUSED(l); return (PathAppend(p,a) ? S_OK : E_FAIL); }
inline HRESULT PathCchCanonicalize(PWSTR p,size_t l,PCWSTR a)    { UNUSED(l); return (PathCanonicalize(p,a) ? S_OK : E_FAIL); }
inline HRESULT PathCchRenameExtension(PWSTR p,size_t l,PCWSTR a) { UNUSED(l); return (PathRenameExtension(p,a) ? S_OK : E_FAIL); }
inline HRESULT PathCchRemoveFileSpec(PWSTR p,size_t l)           { UNUSED(l); return (PathRemoveFileSpec(p) ? S_OK : E_FAIL); }

#define _EXTRA_DRAG_N_DROP_HANDLER_ 1

#ifdef _EXTRA_DRAG_N_DROP_HANDLER_

// special Drag and Drop Handling

typedef struct tDROPDATA
{
  CLIPFORMAT cf;
  POINTL pt;
  DWORD dwKeyState;
  HGLOBAL hData;
} 
DROPDATA, *PDROPDATA;

typedef struct tDROPTARGET *PDROPTARGET;
typedef DWORD(*DNDCALLBACK)(CLIPFORMAT cf, HGLOBAL hData, HWND hWnd, DWORD dwKeyState, POINTL pt, void *pUserData);

void DragAndDropInit(HANDLE hHeap);
PDROPTARGET RegisterDragAndDrop(HWND hWnd, CLIPFORMAT *pFormat, ULONG lFmt, UINT nMsg, DNDCALLBACK pDropProc, void *pUserData);
PDROPTARGET RevokeDragAndDrop(PDROPTARGET pTarget);

#endif


#endif //_NP3_HELPERS_H_

///   End of Helpers.h   ///
