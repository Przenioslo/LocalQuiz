import Felgo 3.0
import QtQuick 2.0
import "helper"
import "pages"

Item {
	anchors.fill: parent

	// app content with plugin list
	NavigationStack {
		id: pluginMainItem

		// initial page contains list if plugins and opens pages for each plugin when selected
		ListPage {
			id: page
			title: qsTr("Felgo Plugins")

			model: ListModel {
				ListElement { type: "Notifications"; name: "Local Notifications"
					detailText: "Schedule Local Notifications"; image: "../assets/logo-localpush.png" }
			}

			delegate: PluginListItem {
				visible: name !== "GameCenter" || Theme.isIos

				onSelected: {
					switch (name) {
					case "Local Notifications":
						page.navigationStack.push(notificationPage)
						break
					}
				}
			}

			section.property: "type"
			section.delegate: SimpleSection { }
		}
	}
}
