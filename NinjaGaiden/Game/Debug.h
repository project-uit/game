#pragma once

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

using namespace std;

void DebugOut(wchar_t *fmt, ...);
void trace(const LPCWSTR format, ...);
void clearFile();