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
			//console.log("You chose: " + fileDialog.fileUrl)
			filename_label.text = file_dialog.fileUrl.toString().substring(file_dialog.fileUrl.toString().lastIndexOf('/') + 1, file_dialog.fileUrl.toString().length);
			//TODO: Check somehow if the file is valid
			convert_button.enabled = true; //TODO: If the file is valid as checked above
		}
		onRejected: {
			console.log("Canceled")
//			file_dialog.close();
		}
//		Component.onCompleted: visible = true
	}

	Button {
		id: open_button;
		x: 20;
		y: 150;
		text: "Load Media"
		onClicked: {
			file_dialog.open();
		}
	}

	Button {
		id: convert_button;
		enabled: false;
		x: 20;
		y: 200;
		text: "Start Conversion"
		onClicked: {
			convert(file_dialog.fileUrl);
		}
	}

	Label {
		id: filename_label;
		x: open_button.x + open_button.width + 30;
		y: open_button.y + open_button.height - 25;
		text: "... Load a media file by clicking the load button to the left.";
	}

	ProgressBar {
		id: conversion_progressbar;
		x: convert_button.x;
		y: convert_button.y + convert_button.height + 10;
		width: 500;
		height: 70;
		value: main_window.progress;
	}
}
