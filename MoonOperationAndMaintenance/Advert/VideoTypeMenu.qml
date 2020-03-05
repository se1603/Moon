/* Author:董梦丹
* Date:2020-02-16
* Note:广告
*/
import QtQuick 2.0

Rectangle {
    id: typeMenu
    width: parent.width
    height: 1 / 10 * parent.height

    property var types:"电影"

    Row{
        height: parent.height
        spacing: 1 / 10 * parent.width
        anchors.horizontalCenter: parent.horizontalCenter
        Repeater {
            model: JSON.parse(client.showVideoCategory())
            Text {
                text: "「"+modelData.name+"」"
                font.pixelSize: 16
                anchors.top: parent.top
                anchors.topMargin: 1 / 2 * parent.height
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    enabled: true

                    onEntered: {
                        parent.font.pixelSize = 18
                    }
                    onExited: {
                        parent.font.pixelSize = 16
                    }
                    onClicked: {
                        types = modelData.name
                        videoChoice.menus =
                                JSON.parse(client.showDetailCategory(videoTypeMenu.types))
                        videoChoice.detail = videoChoice.menus[0].name
                        videoChoice.modelDelegate.model =
                                JSON.parse(client.showVideos(videoTypeMenu.types,
                                                             videoChoice.detail))
                    }
                }
            }
        }
    }
}
