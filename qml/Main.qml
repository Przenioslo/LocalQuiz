import Felgo 3.0
import QtQuick 2.0
import "pages"
import "helper"

/*/////////////////////////////////////
  NOTE:
  Additional integration steps are needed to use Felgo Plugins, for example to add and link required libraries for Android and iOS.
  Please follow the integration steps described in the plugin documentation of your chosen plugins:
  - Local Notifications: https://felgo.com/doc/plugin-notification/

  To open the documentation of a plugin item in Qt Creator, place your cursor on the item in your QML code and press F1.
  This allows to view the properties, methods and signals of Felgo Plugins directly in Qt Creator.

/////////////////////////////////////*/

App
{

	licenseKey: "544EE322E7E9BAF3272461E8C74BBA7F312029E8D5B626373B2A120143BB9EEB59D05900102538537488E5D0AE74C3A12D99C9B4B6826989390CCA2AA5988FCB3C2AF665AED4A52FC70B799A2839115CE7C438CC62B67B53DBC1B25CF6EDB796183F32B004F0597232968917041C4DA6A55084CC464F44687EE04117CCB860BC6F97344B8FBB4865DF6A004E9CB47D1B8B633DBAD65598C2E3E2B2B1203B1EF747BBFE1BCD9D1D8B70A793ADF31945C60C1E1BE922A69BE19ED5A5F3625008A69EF1665C3BEB2912EEEDC655BA479D95D1583BA4ECB6979534C5451ACC433A594F28C51BADD69D68B30DED464CE26DE9F568CB4DB0439441F6E6B07131393804F0DF1AD31F4ACB6B9A340BA09F50FE378840D5E45A979DDF72DF996CC7DE39606AFA038D5E2771BA749B4210408089EFEDF41170341F3FB02039397CD12371F36BE42A909263BEAA57CEFA2E4AF237E4";

	/*PluginMainItem
	{
		id: pluginMainItem
		z: 1           // display the plugin example above other items in the QML code below
		visible: true // set this to true to show the plugin example

		// keep only one instance of these plugin-pages alive within app
		// this prevents crashes due to destruction of plugin items when popping pages from the stack
		property alias notificationPage: notificationPage

		LocalNotificationPage
		{
			id: notificationPage
			visible: false
			onPopped: { notificationPage.parent = pluginMainItem; visible = false }
		}
	}*/

	NavigationStack
	{

		Page
		{
			title: qsTr("Host a Quiz or play one")

			ListPage
			{
				title: "Basic List Example"

				onItemSelected: console.log("Clicked Item # " + index)

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
}
