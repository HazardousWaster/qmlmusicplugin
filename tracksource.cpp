#include "tracksource.h"

QString TrackSource::getInfoLine1()
{
	return title + " - " + artist;
}

QString TrackSource::getInfoLine2()
{
	return length.toString();
}

QString TrackSource::getTitle()
{
	return title;
}

QString TrackSource::getArtist()
{
	return artist;
}

QString TrackSource::getAlbum()
{
	return album;
}

QTime TrackSource::getLength()
{
	return length;
}

Source::PlayStatus TrackSource::getPlayStatus()
{
	return playStatus;
}

Source::RepeatStatus TrackSource::getRepeatStatus()
{
	return repeatStatus;
}

bool TrackSource::getShuffleStatus()
{
	return shuffleStatus;
}

