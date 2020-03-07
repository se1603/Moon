/* Author:董梦丹
* Date:2020-02-20
* Note:广告
*/
import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Rectangle {
    width: parent.width
    height: parent.height - videoTypeMenu.height

    property var menus: JSON.parse(client.showDetailCategory(videoTypeMenu.types))
    property var detail: menus[0].name

    property alias modelDelegate: modelDelegate

    property var message: ""
    property var advertName: ""

    property var backmessage: ""

    property var videotype: videoTypeMenu.types

    Connections {
        target: advertChoice.allbutton
        onClicked: {
            allBeChoosen(true)
        }
    }

    Connections {
        target: advertChoice.addbutton
        onClicked: {
            if(advertChoice.advertName !== ""){
                commitAdd()
                console.log(message)
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

    //    property var wid: mainWindow.width < 1100
    //                      ? (videoBlock.width - 3.2*videoGrid.columnSpacing) / 4
    //                      : (videoBlock.width - 4*videoGrid.columnSpacing) / 5
    //    property var hei: 4 * videoTypes.height

    Rectangle {
        id: videoTypes
        width: parent.width
        height: 1 / 12 * parent.height
        Row{
            height: parent.height
            spacing: 1 / 15 * parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            Repeater {
                model: menus
                Text {
                    text: modelData.name
                    font.pixelSize: 14
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#6495ED"
                    opacity: 0.7
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        enabled: true
                        onEntered: {
                            parent.font.pixelSize = 16
                        }
                        onExited: {
                            parent.font.pixelSize = 14
                        }
                        onClicked: {
                            detail = modelData.name
                            modelDelegate.model = JSON.parse(client.showVideos(
                                                                 videoTypeMenu.types, detail))
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        id: videoBlock
        width: parent.width
        height: parent.height - videoTypes.height
        anchors.top: videoTypes.bottom

        ScrollView {
            anchors.fill: parent
            clip: true
            GridLayout {
                anchors.top: parent.top
                columns: mainWindow.width < 1100 ? 4 : 5
                columnSpacing: 1 / 2 * videoTypes.height
                rowSpacing: 1 / 2 * videoTypes.height

                Repeater {
                    id: modelDelegate
                    model: JSON.parse(client.showVideos(videoTypeMenu.types, detail))
                    Rectangle {
                        id: videoRec
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
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    advertLoader.currentName = parent.parent.name
                                    advertLoader.currentPost = parent.parent.source
                                    advertLoader.currentType = videotype
                                    advertLoader.source = "VideoDetailAdvert.qml"
                                }
                            }
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
                                                 videoTypeMenu.types)
                        advertChoice.advertName = ""
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
