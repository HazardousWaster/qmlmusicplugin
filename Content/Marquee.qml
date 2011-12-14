import QtQuick 1.0

Rectangle {
    width: parent.width
    height: marqueeText.height + padding
    clip: true

    // text to be displayed by the Marquee
    property string text

    // top/bottom text padding
    property int padding : 10

    // the font size used by the Marquee
    property int fontSize : 16

    // the scrolling animation interval
    property int interval : 100

    // the text color
    property color textColor: "black"


    Text {
	anchors.verticalCenter: parent.verticalCenter
		id: marqueeText
		font.pointSize: fontSize
		color: textColor
		text: parent.text
		x: 0
		wrapMode: Text.NoWrap

	
		onTextChanged: {
			x = 0;

			if (marqueeText.paintedWidth > parent.width)
			{
				marqueeTimer.running = true;
				horizontalAlignment  = Text.AlignLeft;
			}
			else
			{
				marqueeTimer.running = false;
				horizontalAlignment = Text.AlignHCenter;
				width = 224;
			}
		}
    }

    Timer {
	id: marqueeTimer
	interval: parent.interval
	onTriggered: moveMarquee()
	running: true
	repeat: true
    }

    function moveMarquee()
    {
	if(marqueeText.x + marqueeText.paintedWidth < 0)
	{
	    marqueeText.x = marqueeText.parent.width;
	}
	marqueeText.x -= 10;
    }

}
