#include <Windows.h>
#include "debug.h"

void DebugOut(wchar_t *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	wchar_t dbg_out[4096];
	vswprintf_s(dbg_out, fmt, argp);
	va_end(argp);
	OutputDebugStringW(dbg_out);
}

static const char* PATH = "Log\\trace.log";
void trace(const LPCWSTR format, ...)
{

	FILE *f = stderr;
	if (PATH != NULL)
	{
		if (fopen_s(&f, PATH, "a") != 0)
		{
			fprintf(stderr, "WARNING: Failed to open trace file '%s' for writing!\n", PATH);
			return;
		}
	}

	va_list ap;
	va_start(ap, format);
	vfwprintf(f, format, ap);
	va_end(ap);
	fprintf(f, "\n");
	if (PATH != NULL) fclose(f);
}

void clearFile() {
	FILE *f = stderr;
	if (PATH != NULL)
	{
		if (fopen_s(&f, PATH, "a") != 0)
		{
			fprintf(stderr, "WARNING: Failed to open trace file '%s' for writing!\n", PATH);
			return;
		}
	}
	if (PATH != NULL) fclose(f);
}