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
    property var path:""

    property alias addbutton:addbutton

    ColumnLayout {
        id: choiceColumn
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 1 / 20 * parent.height
        spacing: 1 / 15 * parent.height

        Button {
            text: "选择广告"
            onClicked: {
                advertDir.folderPathName = "file:///root"
                advertDir.changePathName = ""
                advertDir.absolutePath = "/root"
                advertDir.advertname = ""
                advertDir.folder = advertDir.folderPathName
                advertDir.open()
            }
        }

        Button {
            id: addbutton
            text: "确认插入广告"
        }

        Button {
            text: "搜索单个影视"
            onClicked: {
                advertLoader.source = "SearchVideo.qml"
            }
        }
    }

    Text {
        id: advertText
        anchors.top: choiceColumn.bottom
        anchors.topMargin: choiceColumn.spacing
        anchors.horizontalCenter: parent.horizontalCenter
        width: 5 / 6 * parent.width
        text: "已选广告：" + '\n\n' + path
        wrapMode: Text.Wrap
    }
}
