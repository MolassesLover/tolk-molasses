/**
 *  Product:        Tolk
 *  File:           Tolk.cpp
 *  Description:    C-style DLL exports.
 *  Copyright:      (c) 2014-2016, Davy Kager <mail@davykager.nl>
 *  License:        LGPLv3
 */

#include <windows.h>
#include <list>
#include "Tolk.h"
#include "ScreenReaderDriverJAWS.h"
#include "ScreenReaderDriverNVDA.h"
#include "ScreenReaderDriverSA.h"
#include "ScreenReaderDriverSAPI.h"
#include "ScreenReaderDriverSNova.h"
#include "ScreenReaderDriverWE.h"
#include "ScreenReaderDriverZT.h"

using namespace std;

bool g_isLoaded = false;
list<ScreenReaderDriver*> g_screenReaderDrivers;
ScreenReaderDriverSAPI *g_sapi = NULL;
ScreenReaderDriver *g_currentScreenReaderDriver = NULL;
bool g_trySAPI = false;
bool g_preferSAPI = false;

extern "C" {

 void  Tolk_Load() {
  if (CoInitializeEx(NULL, COINIT_MULTITHREADED) == S_FALSE) CoUninitialize();
  if (Tolk_IsLoaded()) return;
  g_screenReaderDrivers.push_back(new ScreenReaderDriverJAWS());
  g_screenReaderDrivers.push_back(new ScreenReaderDriverWE());
  g_screenReaderDrivers.push_back(new ScreenReaderDriverNVDA());
#ifndef _WIN64
  // This driver does not have 64-bit support.
  g_screenReaderDrivers.push_back(new ScreenReaderDriverSNova());
#endif
  g_screenReaderDrivers.push_back(new ScreenReaderDriverSA());
  g_screenReaderDrivers.push_back(new ScreenReaderDriverZT());
  if (g_trySAPI)
    g_sapi = new ScreenReaderDriverSAPI();
  g_isLoaded = true;
}

 bool  Tolk_IsLoaded() {
  return g_isLoaded;
}

 void  Tolk_Unload() {
  if (Tolk_IsLoaded()) {
    g_isLoaded = false;
    g_currentScreenReaderDriver = NULL;
    if (g_sapi) {
      delete g_sapi;
      g_sapi = NULL;
    }
    for (list<ScreenReaderDriver*>::reverse_iterator rit = g_screenReaderDrivers.rbegin(); rit != g_screenReaderDrivers.rend(); ++rit)
      delete *rit;
    g_screenReaderDrivers.clear();
  }
  CoUninitialize();
}

 void  Tolk_TrySAPI(bool trySAPI) {
  if (g_trySAPI == trySAPI) return;
  g_trySAPI = trySAPI;
  if (Tolk_IsLoaded()) {
    if (g_trySAPI && !g_sapi)
      g_sapi = new ScreenReaderDriverSAPI();
    else if (!g_trySAPI && g_sapi) {
      delete g_sapi;
      g_sapi = NULL;
    }
    g_currentScreenReaderDriver = NULL;
  }
}

 void  Tolk_PreferSAPI(bool preferSAPI) {
  if (g_preferSAPI == preferSAPI) return;
  g_preferSAPI = preferSAPI;
  if (Tolk_IsLoaded() && g_trySAPI && g_sapi)
    g_currentScreenReaderDriver = NULL;
}

 const wchar_t *  Tolk_DetectScreenReader() {
  if (!Tolk_IsLoaded()) return NULL;
  if (g_currentScreenReaderDriver && (g_preferSAPI || g_currentScreenReaderDriver != g_sapi) && g_currentScreenReaderDriver->IsActive())
    return g_currentScreenReaderDriver->GetName();
  if (g_trySAPI && g_preferSAPI && g_sapi && g_sapi->IsActive()) {
    g_currentScreenReaderDriver = g_sapi;
    return g_currentScreenReaderDriver->GetName();
  }
  for (list<ScreenReaderDriver*>::iterator it = g_screenReaderDrivers.begin(); it != g_screenReaderDrivers.end(); ++it) {
    ScreenReaderDriver *screenReaderDriver = *it;
    if (screenReaderDriver != g_currentScreenReaderDriver && screenReaderDriver->IsActive()) {
      g_currentScreenReaderDriver = screenReaderDriver;
      return g_currentScreenReaderDriver->GetName();
    }
  }
  if (g_trySAPI && !g_preferSAPI && g_sapi && g_sapi->IsActive()) {
    g_currentScreenReaderDriver = g_sapi;
    return g_currentScreenReaderDriver->GetName();
  }
  g_currentScreenReaderDriver = NULL;
  return NULL;
}

 bool  Tolk_HasSpeech() {
  if (Tolk_DetectScreenReader())
    return g_currentScreenReaderDriver->HasSpeech();
  return false;
}

 bool  Tolk_HasBraille() {
  if (Tolk_DetectScreenReader())
    return g_currentScreenReaderDriver->HasBraille();
  return false;
}

 bool  Tolk_Output(const wchar_t *str, bool interrupt) {
  if (str && Tolk_DetectScreenReader())
    return g_currentScreenReaderDriver->Output(str, interrupt);
  return false;
}

bool Tolk_Speak(const wchar_t *str, bool interrupt) {
  if (str && Tolk_DetectScreenReader())
    return g_currentScreenReaderDriver->Speak(str, interrupt);
  return false;
}

 bool  Tolk_Braille(const wchar_t *str) {
  if (str && Tolk_DetectScreenReader())
    return g_currentScreenReaderDriver->Braille(str);
  return false;
}

 bool  Tolk_IsSpeaking() {
  if (Tolk_DetectScreenReader())
    return g_currentScreenReaderDriver->IsSpeaking();
  return false;
}

 bool  Tolk_Silence() {
  if (Tolk_DetectScreenReader())
    return g_currentScreenReaderDriver->Silence();
  return false;
}

} // extern "C"
