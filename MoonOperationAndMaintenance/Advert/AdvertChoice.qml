/* Author:董梦丹
* Date:2020-02-16
* Note:广告
*/
import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Rectangle {
    width: 1 / 5 * parent.width
    height: parent.height
    border.color: "gray"

    property var advertName: ""

    property alias addbutton:addbutton
    property alias allbutton:allbutton
    property alias deletebutton:deletebutton

    ColumnLayout {
        id: choiceColumn
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 1 / 20 * parent.height
        spacing: 1 / 15 * parent.height

        Button {
            text: "选择广告"
            onClicked: {
                advertDir.open()
            }
        }

        Button {
            id: addbutton
            text: "确认插入广告"
        }

        Button {
            id: allbutton
            text: "此页影视全选"
        }

        Button {
            text: "搜索单个影视"
            onClicked: {
                advertLoader.source = "SearchVideo.qml"
            }
        }

        Button {
            id: deletebutton
            text: "删除广告"
        }
    }

    Text {
        id: advertText
        anchors.top: choiceColumn.bottom
        anchors.topMargin: choiceColumn.spacing
        anchors.horizontalCenter: parent.horizontalCenter
        text: "已选广告：" + '\n\n' + advertName
    }
}
