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
        target: advertChoice.addbutton
        onClicked: {
            if(advertChoice.advertName){
                commitAdd()
            }else{
                backmessage = "请先勾选待插播视频并选取广告!"
                messageDialog.open()
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
                            Text {
                                id: notes
                                visible: false
                                text: "点击查看详情"
                                font.pixelSize: 16
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            MouseArea {
                                anchors.fill: parent
                                hoverEnabled: true
                                enabled: true
                                onEntered: {
                                    parent.opacity = 0.5
                                    notes.visible = true
                                }
                                onExited: {
                                    parent.opacity = 1
                                    notes.visible = false
                                }
                                onClicked: {
                                    advertLoader.currentName = parent.parent.name
                                    advertLoader.currentPost = parent.parent.source
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

        ColumnLayout {
            width: 3 / 4 * parent.width
            height: parent.height
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10

            Row {
                spacing: 14
                Text {
                    text: qsTr("广告名称")
                    font.pixelSize: 14
                }

                Text {
                    text: advertName
                    font.pixelSize: 14
                }
            }

            Row{
                spacing: 40
                Text {
                    text: qsTr("公司")
                    font.pixelSize: 14
                    anchors.verticalCenter: parent.verticalCenter
                }

                TextField {
                    id: txtCompany
                    font.pixelSize: 14
                }
            }

            Row{
                spacing: 12
                Text {
                    text: qsTr("到期时间")
                    font.pixelSize: 14
                    anchors.verticalCenter: parent.verticalCenter
                }

                TextField {
                    id: txtYear
                    font.pixelSize: 14
                    width: 60
                }

                Text {
                    text: "-"
                    font.pixelSize: 14
                }

                TextField {
                    id: txtMonth
                    font.pixelSize: 14
                    width: 30
                }

                Text {
                    text: "-"
                    font.pixelSize: 14
                }

                TextField {
                    id: txtDay
                    font.pixelSize: 14
                    width: 30
                }
            }

            Rectangle {
                id: txtRec
                width: parent.width
                height: 50
                ScrollView{
                    anchors.fill: parent
                    clip: true
                    Column{
                        Text {
                            id: messages
                            text: "待插播视频：\n" + message
                            font.pixelSize: 14
                            width: txtRec.width
                            wrapMode: Text.Wrap
                        }
                    }
                }
            }

            Row{
                spacing: 50
                Button {
                    text: qsTr("Commit")
                    onClicked: {
                        var txtTime = txtYear.text+"-"+txtMonth.text+"-"+txtDay.text
                        if(txtCompany.text !== "" && txtDuetime.text !== ""){
                            client.addAdvertToVideos(advertName, txtCompany.text,
                                                     txtTime, message,
                                                     "未知")
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
                width: parent.width
                wrapMode: Text.Wrap
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
        advertPath = advertChoice.path

        if(advertName !== "" && message !== ""){
            commitDialog.open()
        }
    }
}
