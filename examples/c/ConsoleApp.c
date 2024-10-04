/**
 *  Product:        Tolk
 *  File:           ConsoleApp.c
 *  Description:    C console application example.
 *  Copyright:      (c) 2014, Davy Kager <mail@davykager.nl>
 *  License:        LGPLv3
 *  Depends:        Tolk.dll, Tolk.lib
 */

// See README.md for general information.
// See Tolk.h for full documentation of all functions.

#define UNICODE

#include <windows.h>
#include <stdio.h>
#include "..\..\src\Tolk.h"

int main() {
  const wchar_t *name = NULL;

  printf("Tolk -- C Console App Example\n");

  printf("Initializing Tolk...\n");
  // Tolk will also initialize COM
  // if it has not been initialized on the calling thread
  Tolk_Load();

  printf("Querying for the active screen reader driver...\n");
  name = Tolk_DetectScreenReader();
  if (name) {
    printf("The active screen reader driver is: %ls\n", name);
  }
  else {
    printf("None of the supported screen readers is running\n");
  }

  if (Tolk_HasSpeech()) {
    printf("This screen reader driver supports speech\n");
  }
  if (Tolk_HasBraille()) {
    printf("This screen reader driver supports braille\n");
  }

  printf("Let's output some text...\n");
  // C does not have default parameter values (compile as C++)
  if (!Tolk_Output(L"Hello, World!", false)) {
    printf("Failed to output text\n");
  }

  printf("Finalizing Tolk...\n");
  // Tolk will also try to uninitialize COM
  Tolk_Unload();

  printf("Done!\n");

  return 0;
}
