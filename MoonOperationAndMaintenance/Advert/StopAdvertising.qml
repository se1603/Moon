/* Author:董梦丹
* Date:2020-04-26
* Note:广告
*/
import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle {
    id: stoppage
    width: parent.pagewidth
    height: parent.pageheight

    property alias advertLoader: stoppage.parent

    property var deletemessage: ""
    property var backmessage: ""

    Connections {
        target: client
        onDeleteAdvertSucceed: {
            deleteDialog.close()
            backmessage = "Succeed!"
            messageDialog.open()
        }
        onDeleteAdvertFailed: {
            deleteDialog.close()
            backmessage = "Failed!"
            messageDialog.open()
        }
    }

    Image {
        id: button
        width: 1 / 20 * parent.width
        height: 1 / 20 * parent.width
        source: "../image/advert/left.png"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                advertLoader.source = "../ManageAdvertPage.qml"
            }
        }
    }

    Row{
        id: titleRow
        height: button.height
        anchors.left: button.right
        spacing: 2 / 3 * parent.width
        Text {
            id: title1
            text: "已投放的映前广告："
            font.pixelSize: 16
            color: "#6495ED"
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            id: title2
            text: "操作选项："
            font.pixelSize: 16
            color: "#6495ED"
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Rectangle {
        id: listRec
        width: 3 / 4 * parent.width
        height: parent.height - button.height - 10
        anchors.top: button.bottom
        anchors.topMargin: 10
        anchors.left: button.right

        ScrollView {
            anchors.fill: parent
            clip: true

            ColumnLayout {
                Repeater {
                    id: linkList
                    model: JSON.parse(client.showAdvertising())

                    Rectangle {
                        id: listRow
                        width: listRec.width
                        height: 1 / 10 * listRec.height

                        property var name: modelData.name
                        property var company: modelData.company
                        property var duetime: modelData.duetime
                        property var videoname: modelData.videoname

                        property bool checks: false

                        Row {
                            id: detailrow
                            spacing: 20
                            anchors.verticalCenter: parent.verticalCenter

                            Text {
                                width: 1 / 5 * listRow.width
                                text: "名称："+ listRow.name
                                wrapMode: Text.Wrap
                                font.pixelSize: 14
                            }

                            Text {
                                width: 1 / 5 * listRow.width
                                text: "公司：" + listRow.company
                                wrapMode: Text.Wrap
                                font.pixelSize: 14
                            }

                            Text {
                                width: 1 / 5 * listRow.width
                                text: "到期时间：" + listRow.duetime
                                wrapMode: Text.Wrap
                                font.pixelSize: 14
                            }

                            Text {
                                width: 1 / 5 * listRow.width
                                text: "投放位置："+ listRow.videoname
                                wrapMode: Text.Wrap
                                font.pixelSize: 14
                            }
                        }

                        RadioButton {
                            checked: listRow.checks
                            scale: 0.7
                            anchors.left: detailrow.right
                            anchors.verticalCenter: parent.verticalCenter
                            onClicked: {
                                listRow.checks = !listRow.checks
                            }
                        }
                    }
                }
            }
        }
    }

    Button {
        id: stop
        text: "勾选停止播放"
        anchors.left: titleRow.left
        anchors.leftMargin: title1.width + titleRow.spacing
        anchors.top: listRec.top
        onClicked: {
            stopAdvertising()
        }
    }

    Dialog {
        id: deleteDialog
        width: 1 / 3 * parent.width
        height: 1 / 3 * parent.height
        visible: false
        anchors.centerIn: parent

        Rectangle {
            id: txtRec
            width: 3 / 4 * parent.width
            height: 60
            anchors.top: parent.top
            anchors.topMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
            ScrollView{
                anchors.fill: parent
                clip: true
                Column{
                    Text {
                        id: txt
                        text: "待删除广告：\n" + deletemessage
                        width: txtRec.width
                        wrapMode: Text.Wrap
                        font.pixelSize: 14
                    }
                }
            }
        }

        Row {
            spacing: 30
            anchors.top: txtRec.bottom
            anchors.topMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                text: "Confirm"
                onClicked: {
                    client.deleteVideoAdverts(deletemessage)
                    linkList.model = JSON.parse(client.showAdvertising())
                }
            }
            Button {
                text: "Cancel"
                onClicked: {
                    deleteDialog.close()
                }
            }
        }
    }

    Dialog {
        id: messageDialog
        width: 1 / 2 * deleteDialog.width
        height: 1 / 2 * deleteDialog.height
        visible: false
        anchors.centerIn: parent

        Column {
            spacing: 30
            anchors.centerIn: parent

            Text {
                text: backmessage
            }

            Button {
                text: "Close"
                onClicked: {
                    messageDialog.close()
                }
            }
        }
    }

    function stopAdvertising() {
        for(var i = 0; i != linkList.model.length; i++){
            if(linkList.itemAt(i).checks === true){
                deletemessage += linkList.itemAt(i).name
                deletemessage += "/"
                deletemessage += linkList.itemAt(i).videoname
                deletemessage += "#"
            }

            if(deletemessage !== ""){
                deleteDialog.open()
            }
        }
    }
}
