#include <QTime>

#include "player.h"
#include "vlcsource.h"
#include "mpris2source.h"
#include "bansheesource.h"
#include "spotifysource.h"

Player::Player(QDeclarativeItem *parent)
	: QDeclarativeItem(parent)
{
	qDebug() << "1";
}
	
Player::Player()
{
	isBanshee = true;
	m_source = new BansheeSource();

	connectSignals();
}

void Player::connectSignals()
{
	QObject::connect(m_source, SIGNAL(trackChanged()), this, SLOT(trackChanged()));
	QObject::connect(m_source, SIGNAL(playbackStatusChanged()), this, SLOT(playbackStatusChanged()));
	QObject::connect(m_source, SIGNAL(repeatStatusChanged()), this, SLOT(repeatStatusChanged()));
	QObject::connect(m_source, SIGNAL(shuffleStatusChanged()), this, SLOT(shuffleStatusChanged()));

}

void Player::changeSource()
{
	if (isBanshee)
	{
		isBanshee = false;
		m_source->disconnect();
		m_source = new VlcSource();
		emit sourceChanged("VLC");
		connectSignals();
	}
	else
	{
		isBanshee = true;
		m_source->disconnect();
		m_source = new SpotifySource();
		emit sourceChanged("Banshee");
		connectSignals();
	}
}

QString Player::source()
{
	return isBanshee ? "Banshee" : "VLC";
}

void Player::playpause()
{
	m_source->playpause();
}

void Player::next()
{
	m_source->next();
}

void Player::previous()
{
	m_source->previous();
}

void Player::toggleShuffle()
{
	m_source->toggleShuffle();
}

void Player::toggleRepeat()
{
	m_source->toggleRepeat();
}
	
QString Player::title()
{
	return m_source->getTitle();
}

QString Player::artist()
{
	return m_source->getArtist();
}

QString Player::album()
{
	return m_source->getAlbum();
}

QTime Player::length()
{
	return m_source->getLength();
}

QTime Player::position()
{
	return m_source->position();
}

Source::PlayStatus Player::playStatus()
{
	return m_source->getPlayStatus();
}

Source::RepeatStatus Player::repeatStatus()
{
	return m_source->getRepeatStatus();
}

bool Player::shuffleStatus()
{
	return m_source->getShuffleStatus();
}

void Player::playbackStatusChanged()
{
	emit playStatusChanged(playStatus());
}

void Player::repeatStatusChanged()
{
	qDebug("hayo");
	emit repeatStatusChanged(repeatStatus());
}

void Player::shuffleStatusChanged()
{
	emit shuffleStatusChanged(shuffleStatus());
}

void Player::trackChanged()
{
	emit titleChanged(title());
	emit artistChanged(artist());
	emit albumChanged(album());
	emit lengthChanged(length());
}