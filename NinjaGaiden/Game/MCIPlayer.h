#pragma once

#ifndef _MP3_USING_MCI
#define _MP3_USING_MCI

#include <string>
#include <vector>
#include <windows.h>
#include <mmsystem.h>

using namespace std;

class MCIPlayer
{
private:
	static MCIPlayer *instance;
	vector<string> *list;
	vector<string> *listNowPlaying;
public:
	static MCIPlayer* GetInstance() {
		if (instance == NULL) {
			instance = new MCIPlayer();
		}
		return instance;
	}
	MCIPlayer();
	~MCIPlayer();
	void Load(string filePath, string fileName);
	void Play(string fileName);
	void PlaySoundTrack(string fileName, int from, int to);
	void SwitchSoundTrack(string fileName, int from, int to);
	void Stop(string fileName);
	void Unload();
	LPWSTR ConvertString(const string& instr)
	{
		// Assumes std::string is encoded in the current Windows ANSI codepage
		int bufferlen = ::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), NULL, 0);

		if (bufferlen == 0)
		{
			// Something went wrong. Perhaps, check GetLastError() and log.
			return 0;
		}

		// Allocate new LPWSTR - must deallocate it later
		LPWSTR widestr = new WCHAR[bufferlen + 1];

		::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), widestr, bufferlen);

		// Ensure wide string is null terminated
		widestr[bufferlen] = 0;

		// Do something with widestr
		return widestr;
		//delete[] widestr;
	}
};
#endif

