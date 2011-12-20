#include <QTime>
#include <QDeclarativeContext>

#include "papafactory/factory.h"
#include "player.h"
#include "source.h"

Player::Player(QDeclarativeItem *parent)
	: QDeclarativeItem(parent)
{
}
	
Player::Player()
{
	isBanshee = true;

	m_sources = QList<SourceOption*>();
	m_activeSource = NULL;
	scanSources();
	selectSource(0);
}

void Player::scanSources()
{
	m_sources.clear();
	m_sources.append(SourceManager::instance().getSourceOptions());
	emit sourceListChanged(QDeclarativeListProperty<SourceOption>(this, m_sources));
}

void Player::selectSource(int index)
{
	SourceOption *option = m_sources[index];
	qDebug() << "Selecting " << option->name << option->classname;

	QByteArray ba = option->classname.toLocal8Bit();

	boost::shared_ptr<Source> sharedSource(papa::factory<Source>::instance().Create(ba.data(), option->params));
	
	qDebug() << sharedSource;
	Source* source = sharedSource.get();

	if (m_activeSource != source)
	{
		if (m_activeSource != NULL)
		{
			m_activeSource->disable();
			disconnectSignals();
		}

		m_activeSource = source;
		m_sharedSource = sharedSource;
		connectSignals();
		m_activeSource->enable();
		emit activeSourceNameChanged(option->name);
		infoLine1Changed();
		infoLine2Changed();
		playbackStatusChanged();
		repeatStatusChanged();
		shuffleStatusChanged();
	}
}

void Player::connectSignals()
{
	QObject::connect(m_activeSource, SIGNAL(infoLine1Changed()), this, SLOT(infoLine1Changed()));
	QObject::connect(m_activeSource, SIGNAL(infoLine2Changed()), this, SLOT(infoLine2Changed()));
	QObject::connect(m_activeSource, SIGNAL(trackChanged()), this, SLOT(trackChanged()));
	QObject::connect(m_activeSource, SIGNAL(playbackStatusChanged()), this, SLOT(playbackStatusChanged()));
	QObject::connect(m_activeSource, SIGNAL(repeatStatusChanged()), this, SLOT(repeatStatusChanged()));
	QObject::connect(m_activeSource, SIGNAL(shuffleStatusChanged()), this, SLOT(shuffleStatusChanged()));
}

void Player::disconnectSignals()
{
	QObject::disconnect(m_activeSource, SIGNAL(infoLine1Changed()), this, SLOT(infoLine1Changed()));
	QObject::disconnect(m_activeSource, SIGNAL(infoLine2Changed()), this, SLOT(infoLine2Changed()));

	QObject::disconnect(m_activeSource, SIGNAL(trackChanged()), this, SLOT(trackChanged()));
	QObject::disconnect(m_activeSource, SIGNAL(playbackStatusChanged()), this, SLOT(playbackStatusChanged()));
	QObject::disconnect(m_activeSource, SIGNAL(repeatStatusChanged()), this, SLOT(repeatStatusChanged()));
	QObject::disconnect(m_activeSource, SIGNAL(shuffleStatusChanged()), this, SLOT(shuffleStatusChanged()));
}

QString Player::activeSourceName()
{
	return m_activeSource->getName();
}

void Player::playpause()
{
	m_activeSource->playpause();
}

void Player::next()
{
	m_activeSource->next();
}

void Player::previous()
{
	m_activeSource->previous();
}

void Player::toggleShuffle()
{
	m_activeSource->toggleShuffle();
}

void Player::toggleRepeat()
{
	m_activeSource->toggleRepeat();
}

QString Player::infoLine1()
{
	return m_activeSource->getInfoLine1();
}

QString Player::infoLine2()
{
	return m_activeSource->getInfoLine2();
}
	
QString Player::title()
{
	return m_activeSource->getTitle();
}

QString Player::artist()
{
	return m_activeSource->getArtist();
}

QString Player::album()
{
	return m_activeSource->getAlbum();
}

QTime Player::length()
{
	return m_activeSource->getLength();
}

QTime Player::position()
{
	return m_activeSource->position();
}

Source::PlayStatus Player::playStatus()
{
	return m_activeSource->getPlayStatus();
}

Source::RepeatStatus Player::repeatStatus()
{
	return m_activeSource->getRepeatStatus();
}

bool Player::shuffleStatus()
{
	return m_activeSource->getShuffleStatus();
}

void Player::infoLine1Changed()
{
	emit infoLine1Changed(infoLine1());
}

void Player::infoLine2Changed()
{
	emit infoLine2Changed(infoLine2());
}

void Player::playbackStatusChanged()
{
	emit playStatusChanged(playStatus());
}

void Player::repeatStatusChanged()
{
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