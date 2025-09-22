#include <iostream>
#include <windows.h>
#include "JunkGenerator.h"

int main() {
  JUNK_GENERATE(100); // for best performance, use between 500 and 1500
  return 0;
}