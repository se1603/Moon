/* Author:董梦丹
* Date:2020-02-18
* Note:广告
*/
import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle {
    width: 4 / 5 * advertMiddle.width
    height: advertMiddle.height

    property var message: ""
    property var advertName: ""

    property var backmessage: ""

    Connections {
        target: advertChoice.allbutton
        onClicked: {
            allBeChoosen(true)
        }
    }

    Connections {
        target: advertChoice.addbutton
        onClicked: {
            if(advertChoice.advertName){
                commitAdd()
            }
        }
    }

    Connections {
        target: client
        onAddAdvertSucceed: {
            commitDialog.close()
            backmessage = "Succeed!"
            messageDialog.open()
        }
        onAddAdvertFailed: {
            commitDialog.close()
            backmessage = "Failed!"
            messageDialog.open()
        }
    }

    Row {
        id: row
        anchors.top: parent.top
        anchors.topMargin: 1 / 2 * spacing
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 1 / 20 * parent.width
        Text {
            text: "搜索名称："
            font.pixelSize: 16
            anchors.verticalCenter: parent.verticalCenter
        }

        TextField {
            id: txtInput
        }

        Image {
            id: searchbutton
            source: "qrc:/image/advert/search.png"
            anchors.verticalCenter: parent.verticalCenter
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(txtInput.text !== ""){
                        modelDelegate.model = JSON.parse(client.searchVideos(txtInput.text))
                    }
                }
            }
        }
    }

    Rectangle {
        id: search
        width: parent.width
        height: parent.height - row.height
        anchors.top: row.bottom

        ScrollView {
            anchors.fill: parent
            clip: true
            GridLayout {
                anchors.top: parent.top
                anchors.topMargin: 1 / 4 * row.height
                columns: mainWindow.width < 1100 ? 4 : 5
                columnSpacing: 1 / 2 * row.height
                rowSpacing: 1 / 2 * row.height

                Repeater {
                    id: modelDelegate
                    model: 0
                    Rectangle {
                        width: 150
                        height: 250
                        property var name:modelData.name
                        property var source:modelData.post
                        property bool check:false
                        Image {
                            id: videoPost
                            width: parent.width
                            height: 5 / 6 * parent.height
                            source: "file:" + parent.source
                        }
                        CheckBox {
                            id: videoCheck
                            text: parent.name
                            anchors.top: videoPost.bottom
                            checked: parent.check
                            onClicked: {
                                parent.check = !parent.check
                            }
                        }
                    }
                }
            }
        }
    }

    Popup {
        id: commitDialog
        width: 1 / 3 * mainWindow.width
        height: 1 / 2 * mainWindow.height
        visible: false
        anchors.centerIn: parent

        GridLayout {
            id: content
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            columnSpacing: 10
            rowSpacing: 20
            columns: 2

            Text {
                text: qsTr("广告名称")
                font.pixelSize: 14
            }

            Text {
                text: advertName
                font.pixelSize: 14
            }

            Text {
                text: qsTr("公司")
                font.pixelSize: 14
            }

            TextField {
                id: txtCompany
                font.pixelSize: 14
            }

            Text {
                text: qsTr("到期时间")
                font.pixelSize: 14
            }

            TextField {
                id: txtDuetime
                font.pixelSize: 14
            }
        }

        Text {
            id: messages
            text: "待插播视频：" + message
            font.pixelSize: 14
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: content.bottom
            anchors.topMargin: 20
            width: content.width
            wrapMode: Text.Wrap
        }

        Row{
            anchors.top: messages.bottom
            anchors.topMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 30
            Button {
                text: qsTr("Commit")
                onClicked: {
                    if(txtCompany.text !== "" && txtDuetime.text !== ""){
                        client.addAdvertToVideos(advertName, txtCompany.text,
                                                  txtDuetime.text, message,
                                                 "未知")
                    }
                }
            }

            Button {
                text: qsTr("CLose")
                onClicked: {
                    commitDialog.close()
                }
            }
        }
    }

    Dialog {
        id: messageDialog
        width: 1 / 2 * commitDialog.width
        height: 1 / 2 * commitDialog.height
        visible: false
        anchors.centerIn: parent

        Column {
            spacing: 1 / 6 * parent.width
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

    function allBeChoosen(checkState) {
        for(var i = 0;i !== modelDelegate.model.length;i++){
            modelDelegate.itemAt(i).check = checkState
        }
    }

    function commitAdd() {
        message = ""

        for(var i = 0;i !== modelDelegate.model.length;i++){
            if(modelDelegate.itemAt(i).check === true){
                message += modelDelegate.itemAt(i).name
                message += "/"
            }
        }

        advertName = advertChoice.advertName

        if(advertName !== "" && message !== ""){
            commitDialog.open()
        }
    }
}
