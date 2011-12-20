#!/bin/bash

set -e

qdbusxml2cpp -N -c MprisPlayerProxy \
	-p mprisplayerproxy.h:mprisplayerproxy.cpp \
	-i mprisstatus.h \
	introspection/vlc_player.xml \
	org.freedesktop.MediaPlayer

qdbusxml2cpp -N -c MprisRootProxy \
	-p mprisrootproxy.h:mprisrootproxy.cpp \
	introspection/vlc_root.xml \
	org.freedesktop.MediaPlayer

qdbusxml2cpp -N -c Mpris2PlayerProxy \
	-p mpris2playerproxy.h:mpris2playerproxy.cpp \
	introspection/banshee_player.xml \
	org.mpris.MediaPlayer2.Player

qdbusxml2cpp -N -c Mpris2RootProxy \
	-p mpris2rootproxy.h:mpris2rootproxy.cpp \
	introspection/banshee_player.xml \
	org.mpris.MediaPlayer2


qdbusxml2cpp -N -c Mpris2TrackListProxy \
	-p mpris2tracklistproxy.h:mpris2tracklistproxy.cpp \
	introspection/clementine_all.xml \
	org.mpris.MediaPlayer2.TrackList
