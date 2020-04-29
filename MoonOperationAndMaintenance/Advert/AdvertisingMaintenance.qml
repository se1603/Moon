/* Author:董梦丹
* Date:2020-04-25
* Note:广告
*/
import QtQuick 2.0

Rectangle {
    id: maintenancepage
    width: parent.pagewidth
    height: parent.pageheight

    property alias advertLoader:maintenancepage.parent

    Column {
        spacing: 1 / 9 * parent.width
        anchors.centerIn: parent

        Text {
            text: "Advertising   Maintenance"
            font.pixelSize: 45
            color: "#6495ED"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            text: "Welcome, C"
            font.pixelSize: 20
            color: "#999999"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Row {
            spacing: parent.spacing
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {
                width: 1 / 8 * maintenancepage.width
                height: 3 / 4 * width
                radius: 6
                border.color: "#6495ED"

                Text {
                    text: "投放广告"
                    font.pixelSize: 16
                    anchors.centerIn: parent
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        parent.scale = 1.3
                    }
                    onExited: {
                        parent.scale = 1
                    }
                    onClicked: {
                        advertLoader.source = "PutAdvertising.qml"
                    }
                }
            }

            Rectangle {
                width: 1 / 8 * maintenancepage.width
                height: 3 / 4 * width
                radius: 6
                border.color: "#6495ED"

                Text {
                    text: "停止投放广告"
                    font.pixelSize: 16
                    anchors.centerIn: parent
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        parent.scale = 1.3
                    }
                    onExited: {
                        parent.scale = 1
                    }
                    onClicked: {
                        advertLoader.source = "StopAdvertising.qml"
                    }
                }
            }

            Rectangle {
                width: 1 / 8 * maintenancepage.width
                height: 3 / 4 * width
                radius: 6
                border.color: "#6495ED"

                Text {
                    text: "调整投放配置"
                    font.pixelSize: 16
                    anchors.centerIn: parent
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        parent.scale = 1.3
                    }
                    onExited: {
                        parent.scale = 1
                    }
                    onClicked: {
                        advertLoader.source = "AdjustAdvertising.qml"
                    }
                }
            }
        }
    }
}
