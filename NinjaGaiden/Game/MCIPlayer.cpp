#include "MCIPlayer.h"

MCIPlayer* MCIPlayer::instance = NULL;

MCIPlayer::MCIPlayer()
{
	list = new  vector<string>();
	listNowPlaying = new  vector<string>();
}

MCIPlayer::~MCIPlayer()
{
	Unload();
	list->clear();
	listNowPlaying->clear();
	delete list;
	delete listNowPlaying;
}

void MCIPlayer::Load(string filePath, string fileName)
{
	list->push_back(fileName);
	string szCommand = "open " + filePath + " type mpegvideo alias " + fileName;
	mciSendString(ConvertString(szCommand), NULL, 0, 0);
}

void MCIPlayer::PlaySoundTrack(string fileName, int from, int to)
{
	listNowPlaying->push_back(fileName);
	string fromStr = to_string(from);
	string toStr = to_string(to);
	string szCommand = "play " + fileName + " repeat from " + fromStr + " to " + toStr;
	mciSendString(ConvertString(szCommand), NULL, 0, 0);
}

void MCIPlayer::Play(string fileName)
{
	string szCommand = "play " + fileName + " from 0";
	mciSendString(ConvertString(szCommand), NULL, 0, 0);
}

void MCIPlayer::Stop(string fileName)
{
	string szCommand = "stop " + fileName;
	mciSendString(ConvertString(szCommand), NULL, 0, 0);
}

void MCIPlayer::Unload()
{
	for (int i = 0; i < list->size(); i++) {
		string szCommand = "close " + list->at(i);
		Stop(list->at(i));
		mciSendString(ConvertString(szCommand), NULL, 0, 0);
	}
}

void MCIPlayer::SwitchSoundTrack(string fileName, int from, int to)
{
	for (int i = 0; i < listNowPlaying->size(); i++) {
		Stop(listNowPlaying->at(i));
	}
	listNowPlaying->clear();
	PlaySoundTrack(fileName, from, to);
}
