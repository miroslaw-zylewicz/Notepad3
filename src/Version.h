﻿/******************************************************************************
*                                                                             *
*                                                                             *
* Notepad3                                                                    *
*                                                                             *
* Version.h                                                                   *
*   Based on code from Notepad2-mod, (c) XhmikosR 2010-2015                   *
*                                                                             *
*                                                  (c) Rizonesoft 2008-2019   *
*                                                 https://www.rizonesoft.com  *
*                                                                             *
*                                                                             *
*******************************************************************************/

#ifndef NOTEPAD3_VERSION_H
#define NOTEPAD3_VERSION_H

#define __CC(p,s) p ## s
#define _V(s)  __CC(v,s)
#define _W(s)  __CC(L,s)

#define _STRINGIFY(s) #s
#define _STRG(s)  _STRINGIFY(s)

#include "VersionEx.h"

// ----------------------------------------------------------------------------
#define VERSION_FILEVERSION          VERSION_MAJOR.VERSION_MINOR.VERSION_REV.VERSION_BUILD
#define VERSION_FILEVERSION_NUM      VERSION_MAJOR,VERSION_MINOR,VERSION_REV,VERSION_BUILD

#if defined(_WIN64)
#define  VERSION_FILEVERSION_LONG    APPNAME (64-bit)  _V(VERSION_FILEVERSION)  VERSION_PATCH
#else
#define  VERSION_FILEVERSION_LONG    APPNAME  _V(VERSION_FILEVERSION)  VERSION_PATCH
#endif


#if defined(_DEBUG) || defined(DEBUG)
#pragma message("Debug Build: " _STRG(VERSION_FILEVERSION_LONG))
#else
#pragma message("Release Build: " _STRG(VERSION_FILEVERSION_LONG))
#endif

#define VERSION_LEGALCOPYRIGHT         "Copyright © 2015-2019 Rizonesoft"
//#define VERSION_LEGALCOPYRIGHT_LONG  "© Rizonesoft 2015-2019"
#define VERSION_AUTHORNAME             "© Rizonesoft"
#define VERSION_WEBPAGEDISPLAY         "https://www.rizonesoft.com"
#define VERSION_COMPANYNAME            "© Rizonesoft"
//#define VERSION_MODPAGEDISPLAY       "https://xhmikosr.github.io/notepad2-mod/"
//#define VERSION_WEBPAGE2DISPLAY      "http://www.flos-freeware.ch"

#ifdef _DLL
#define _SCI_BUILD                     L"Scintilla(dll) "
#else
#define _SCI_BUILD                     L"Scintilla "
#endif

#define VERSION_SCIVERSION             _SCI_BUILD _W(_STRG(_V(SCINTILLA_VER))) L"  (RegEx: Onigmo v" _W(_STRG(ONIGMO_REGEX_VER)) L")"

// ============================================================================

#define VERSION_UPDATE_CHECK           L"https://www.rizonesoft.com/downloads/notepad3/update/?version=" _W(_STRG(VERSION_FILEVERSION))

// ============================================================================

// Compiler specific

#if defined(_MSC_VER)
    #if (_MSC_VER >= 1920)
        #if(_MSC_FULL_VER >= 192127702)
            #define VER_CPL     MS Visual C++ 2019 v16.1.(0-4)
        #elif(_MSC_FULL_VER >= 192027508)
            #define VER_CPL     MS Visual C++ 2019 v16.0.(0-4)
        #elif(_MSC_FULL_VER >= 192027027)
            #define VER_CPL     MS Visual C++ 2019 v16.0.Prev(1-4)
        #endif
    #elif (_MSC_VER >= 1916)
        #if(_MSC_FULL_VER >= 191627031)
            #define VER_CPL     MS Visual C++ 2017 v15.9.12
        #elif(_MSC_FULL_VER >= 191627030)
            #define VER_CPL     MS Visual C++ 2017 v15.9.11
        #elif(_MSC_FULL_VER >= 191627027)
            #define VER_CPL     MS Visual C++ 2017 v15.9.(7-10)
        #elif(_MSC_FULL_VER >= 191627026) 
            #define VER_CPL     MS Visual C++ 2017 v15.9.(5-6)
        #elif(_MSC_FULL_VER >= 191627025) 
            #define VER_CPL     MS Visual C++ 2017 v15.9.4
        #elif(_MSC_FULL_VER >= 191627024) 
            #define VER_CPL     MS Visual C++ 2017 v15.9.(2-3)
        #elif(_MSC_FULL_VER >= 191627023) 
            #define VER_CPL     MS Visual C++ 2017 v15.9.(0-1)
        #endif
    #elif (_MSC_VER >= 1915)
        #if(_MSC_FULL_VER >= 191526732)
            #define VER_CPL     MS Visual C++ 2017 v15.8.(8-9)
        #elif(_MSC_FULL_VER >= 191526730)
            #define VER_CPL     MS Visual C++ 2017 v15.8.(5-7)
        #elif(_MSC_FULL_VER >= 191526729)
            #define VER_CPL     MS Visual C++ 2017 v15.8.4
        #elif(_MSC_FULL_VER >= 191526726)
            #define VER_CPL     MS Visual C++ 2017 v15.8.(0-3)
        #endif
    #elif (_MSC_VER >= 1914)
        #if(_MSC_FULL_VER >= 191426433)
            #define VER_CPL     MS Visual C++ 2017 v15.7.(5-6)
        #elif(_MSC_FULL_VER >= 191426431)
            #define VER_CPL     MS Visual C++ 2017 v15.7.4
        #elif(_MSC_FULL_VER >= 191426430)
            #define VER_CPL     MS Visual C++ 2017 v15.7.3
        #elif(_MSC_FULL_VER >= 191426429)
            #define VER_CPL     MS Visual C++ 2017 v15.7.2
        #elif(_MSC_FULL_VER >= 191426428)
            #define VER_CPL     MS Visual C++ 2017 v15.7.(0-1)
        #endif
    #elif (_MSC_VER >= 1913)
        #if (_MSC_FULL_VER >= 191326132)
            #define VER_CPL     MS Visual C++ 2017 v15.6.7
        #elif(_MSC_FULL_VER >= 191326131)
            #define VER_CPL     MS Visual C++ 2017 v15.6.6
        #elif(_MSC_FULL_VER >= 191326129)
            #define VER_CPL     MS Visual C++ 2017 v15.6.(3-5)
        #elif(_MSC_FULL_VER >= 191326128)
            #define VER_CPL     MS Visual C++ 2017 v15.6.(0-2)
        #endif
    #elif (_MSC_VER >= 1912)
        #if(_MSC_FULL_VER >= 191225835)
            #define VER_CPL     MS Visual C++ 2017 v15.5.(5-7)
        #elif(_MSC_FULL_VER >= 191225834)
            #define VER_CPL     MS Visual C++ 2017 v15.5.(3-4)
        #elif(_MSC_FULL_VER >= 191225831)
            #define VER_CPL     MS Visual C++ 2017 v15.5.2
        #elif(_MSC_FULL_VER >= 191225830)
            #define VER_CPL     MS Visual C++ 2017 v15.5
        #else
            #define VER_CPL     MS Visual C++ 2017 (version unknown)
        #endif
    #elif (_MSC_VER >= 1911)
        #if((_MSC_FULL_VER >= 191125542) && (_MSC_FULL_VER <= 191125547))
           #define VER_CPL     MS Visual C++ 2017 v15.4
        #elif((_MSC_FULL_VER >= 191125506) && (_MSC_FULL_VER <= 191125508))
           #define VER_CPL     MS Visual C++ 2017 v15.3
        #else
           #define VER_CPL     MS Visual C++ 2017 (version unknown)
        #endif
    #elif (_MSC_VER >= 1910)
        #if ((_MSC_FULL_VER >= 191025017) && (_MSC_FULL_VER <= 191025019))
           #define VER_CPL     MS Visual C++ 2017 v15.2
        #else
            #define VER_CPL    MS Visual C++ 2017 RC
        #endif
    #elif (_MSC_VER == 1900)
        #if (_MSC_FULL_VER == 190024210) || (_MSC_FULL_VER == 190024215)
            #define VER_CPL    MS Visual C++ 2015 Update 3
        #elif (_MSC_FULL_VER == 190023918)
            #define VER_CPL    MS Visual C++ 2015 Update 2
        #elif (_MSC_FULL_VER == 190023506)
            #define VER_CPL    MS Visual C++ 2015 Update 1
        #elif (_MSC_FULL_VER == 190023506)
            #define VER_CPL    MS Visual C++ 2015 Update 1
        #else
            #define VER_CPL    MS Visual C++ (version unknown)
        #endif
    #else
        #define VER_CPL        MS Visual C++ (version unknown)
    #endif
#else
    #define VER_CPL            (Unknown Compiler)
#endif

#pragma message("Compiler " _STRG(VER_CPL) "  (v" _STRG(_MSC_FULL_VER) ")")

#define VERSION_COMPILER  L"Compiler: " _W(_STRG(VER_CPL)) L" (VC v" _W(_STRG(_MSC_VER)) L")"


#endif // NOTEPAD3_VERSION_H
