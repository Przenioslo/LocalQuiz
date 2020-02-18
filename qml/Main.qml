import QtQuick.Dialogs 1.2
import Felgo 3.0
import QtQuick 2.7
import "pages"
import "helper"

App
{
	NavigationStack
	{
		initialPage: theMainPage;

		Page
		{
			id: theMainPage;

			title: qsTr("Host a Quiz or play one");

			ListPage
			{
				title: "Basic List Example"

				onItemSelected:
				{
					console.log("Clicked Item # " + index);
					theMainPage.navigationStack.push(!index ?
							theHostPage : theJoinPage);
				}

				model: [
				{
					 text: "Host",
					 detailText: "Create a quiz, host it and let others play it",
					 icon: IconType.user
				},
				{
					 text: "Join",
					 detailText:
						"Play an existing quiz hostedby someone in the network",
					 icon: IconType.group
				}]
			}
		}
	}

	Component
	{
		id: theHostPage;

		Page
		{
			title: qsTr("Host a Quiz");

			AppTextField
			{
				id: theQuizName;

				width: dp(200);
				placeholderText: "Enter Quiz name";

				anchors.top: parent.top;
				anchors.horizontalCenter: parent.horizontalCenter;
				anchors.topMargin: dp(20);
			}

			AppButton
			{
				id: theLoadQuizBtn;

				width: theQuizName.width;
				text: "Load quiz";

				anchors.top: theQuizName.bottom;
				anchors.horizontalCenter: parent.horizontalCenter;
				anchors.topMargin: dp(20);

				onClicked:
				{
					theFileDialog.open();
				}
			}

			AppButton
			{
				width: theQuizName.width;
				text: "Start quiz";

				anchors.top: theLoadQuizBtn.bottom;
				anchors.horizontalCenter: parent.horizontalCenter;
				anchors.topMargin: dp(20);
			}
		}
	}

	Component
	{
		id: theJoinPage;

		Page
		{
			title: qsTr("Join a Quiz");
		}
	}

	FileDialog
	{
		id: theFileDialog;
		folder: shortcuts.home;

		onAccepted:
		{
			console.log("Choosen file: ", theFileDialog.fileUrl);
		}
	}
}






















