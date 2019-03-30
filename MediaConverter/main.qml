import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import QtQml 2.12


Window {
	visible: true;
	width: 640
	height: 480
	title: qsTr("Media Converter")
	signal convert(string file_path);
	function onConversionDone()
	{
		console.log('DONE!');
		messageDialog.open();
	}
	MessageDialog {
	    id: messageDialog
	    title: "May I have your attention please"
	    text: "It's so cool that you are using Qt Quick."
	    onAccepted: {
		console.log("And of course you could only agree.")
		Qt.quit()
	    }
	}
	Rectangle {
		width: 640
		height: 480

		Button {
			x: 320;
			y: 100;
			text: "convert media"
			onClicked: {
				console.log('convert!');
				convert("cute.mp4");
			}
		}
	}
}
