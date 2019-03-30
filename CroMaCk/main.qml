import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import QtQml 2.12


Window {
	//Main window properties
	visible: true;
	width: 640;
	height: 480;
	title: qsTr("CroMaCk");

	//signals
	signal convert(string file_path);

	//slots
	function onConversionDone()
	{
		console.log('DONE!');
		messageDialog.open();
	}

	MessageDialog {
		id: conversion_complete;
		title: "Conversion Completed";
		text: "The conversion completed succesfully. Find your converted media file in the same directory as the original, named 'output'.";
		onAccepted: {
//			Qt.quit()
			conversion_complete.close();
		}
	}

	FileDialog {
		id: file_dialog;
		title: "Please choose a media file";
		folder: shortcuts.home;
		width: 720;
		height: 720;
//		nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
		onAccepted: {
			console.log("You chose: " + fileDialog.fileUrl)
//			Qt.quit()
		}
		onRejected: {
			console.log("Canceled")
//			file_dialog.close();
//			Qt.quit()
		}
//		Component.onCompleted: visible = true
	}

	Button {
		id: open_button;
		x: 320;
		y: 50;
		text: "open media"
		onClicked: {
			file_dialog.open();
		}
	}

	Button {
		id: convert_button;
		x: 320;
		y: 100;
		text: "convert media"
		onClicked: {
//			convert("UndulatusAsperatus.mp4", "/sa/sa/");
//			convert(file_dialog.fileUrl, "/sa/sa/");
//			convert("UndulatusAsperatus.mp4", file_dialog.fileUrl.substring(8, 10/*file_dialog.fileUrl.lastIndexOf('/')*/));
			convert(file_dialog.fileUrl);
		}
	}
}
