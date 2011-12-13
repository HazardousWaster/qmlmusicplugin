#!/bin/bash

set -e

qdbusxml2cpp -N -c MprisPlayerProxy \
	-p mprisplayerproxy.h:mprisplayerproxy.cpp \
	-i mprisstatus.h \
	introspection/vlc_player.xml \
	org.freedesktop.MediaPlayer

qdbusxml2cpp -N -c Mpris2PlayerProxy \
	-p mpris2playerproxy.h:mpris2playerproxy.cpp \
	introspection/banshee_player.xml \
	org.mpris.MediaPlayer2.Player
