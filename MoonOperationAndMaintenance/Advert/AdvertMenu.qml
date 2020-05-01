/* Author:董梦丹
* Date:2020-01-31
* Note:广告
*/
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle {
    width: 1 / 6 * parent.width
    height: parent.height

    property var name: "c"

    ColumnLayout {
        spacing: 1 / 16 * advertMenu.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 1 / 20 * parent.height

        Row {
            opacity: 0.7
            Text {
                text: "「 Welcome, "
                font.pixelSize: 16
                color: "#6495ED"
            }

            Text {
                text: name+"」"
                font.pixelSize: 16
                color: "#6495ED"
            }
        }


        Text {
            text: "「插入广告」"
            font.pixelSize: 16

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
                    advertStack.push(advertAdd,StackView.Immediate)
                    parent.opacity = 1
                }
            }
        }

        Text {
            text: "「统计播放量」"
            font.pixelSize: 16

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
                    advertStack.push(advertCalculation,StackView.Immediate)
                    parent.opacity = 1
                }
            }
        }
    }
}
