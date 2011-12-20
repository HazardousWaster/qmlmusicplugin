import QtQuick 1.0
import "music"
import "Content"

Rectangle {
	id: screen

	width: 800; height: 480

	color: "navy"
	
	Rectangle {
		 id: musicbar

		 width: 800; height: 64
		 color: "white"

		 Item {
			 id: container
			 //x: screen.width /2 ; y: 10
		 
			Player
			{
				id: player
			
				onPlayStatusChanged:
				{
					if (playStatus == 0)
						btnPlayPause.image = "pause.png";
					else
						btnPlayPause.image = "play.png";
				}
			}
		 		 
			Row
			{
				spacing: 0
				y: 0
			
				Column
				{
					width: 224
					Marquee {
						id: trackName
						text: player.infoLine1
						//horizontalAlignment: Text.AlignHCenter
					}

					Text {
						id: trackTime
						text: player.infoLine2
						horizontalAlignment: Text.AlignHCenter
						font.pixelSize: 20
						width: 224
					}
				}
			
				Button {
					image: "previous.png"
					onClicked: player.previous()
				}
						
				Button {
					id: btnPlayPause
					image: "pause.png"
					onClicked: player.playpause()
				}
			
				Button {
					image: "next.png"
					onClicked: player.next()
				}

			
				Button {
					id: btnShuffle
					text: "Shuffle\n" + player.shuffleStatus
					//image: "previous.png"
					onClicked: player.toggleShuffle()
				}
			
				Button {
					id: btnRepeat
					text: "Repeat\n" + ((player.repeatStatus == 0) ? "None" : ((player.repeatStatus == 1) ? "All" : "Single"))
					//image: "previous.png"
					onClicked: player.toggleRepeat()
				}
			
				Button {
					text: "Playlist"
					onClicked: container.previous()
				}	

				Button {
					text: "Source\n" + player.activeSourceName
					onClicked: {
						player.scanSources(); 
						sourceSelect.visible = !sourceSelect.visible
					}
				}				
			}
		
			function toggleShuffle()
			{
				if (player.shuffle)
				{
					btnShuffle.text = "S off";
					player.shuffle = false;
				}
				else
				{
					btnShuffle.text = "S on";
					player.shuffle = true;
				}
			}	
		
			function updateUI()
			{
				//trackName.text = player.title + " - " + player.artist + " - " + player.album + "\n" + player.position + " / " + player.length;
			
				/*if (player.shuffle)
					btnShuffle.text = "s on";
				else
					btnShuffle.text = "s off";*.
					player.position = player.position + 1;
				*/
			}
		
			Timer {
				interval: 1; running: true; repeat: true
				onTriggered: container.updateUI();
			}
		 }
	}

	ListView {
		id: sourceSelect
		width: 500; height: 250
		x: 50; y: 100
		visible: false

		model: player.sources

		delegate: Button {
			color: "white"
			text: name
			width: 256
			height: 64
			onClicked: { player.selectSource(index); sourceSelect.visible = false }
		}
	}
 }