/* Author:董梦丹
* Date:2020-02-22
* 最后修改: 03-04
* Note:广告
*/
import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle {
    width: parent.width
    height: parent.height
    anchors.top: parent.top
    anchors.topMargin: 1 / 20 * parent.height

    property var advertsmessage:""
    property var backmessage:""
    property var videotype: parent.currentType

    property var date: new Date()

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

    Row {
        id: videoRow
        width: parent.width
        height: 3 / 10 * parent.height
        spacing: 1 / 40 * parent.width

        Image {
            width: 120
            height: 160
            source: "file:" + parent.parent.parent.currentPost
        }

        Row {
            Image {
                width: 50
                height: 50
                source: "../image/advert/left.png"
                opacity: 0.5
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: enabled
                    enabled: true
                    onEntered: {
                        parent.opacity = 1
                    }
                    onExited: {
                        parent.opacity = 0.5
                    }
                    onClicked: {
                        advertStack.push(advertAdd,StackView.Immediate)
                    }
                }
            }

            Text {
                id: txt
                text: parent.parent.parent.parent.currentName
                font.pixelSize: 18
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Rectangle {
        id: advertsRec
        width: parent.width
        height: parent.height - videoRow.height
        anchors.top: videoRow.bottom

        property var adverts:
            JSON.parse(client.showVideoAdverts(txt.text, parent.parent.currentType))

        ScrollView {
            anchors.fill: parent
            clip: true
            ColumnLayout {
                anchors.top: parent.top
                anchors.topMargin: spacing
                spacing: 1 / 20 * videoRow.height

                Row {
                    width: parent.width
                    spacing: 19 / 36 * parent.width

                    Text {
                        id: txttitle
                        text: "该影视所投放的广告："
                        font.pixelSize: 22
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Button {
                        text: "勾选删除"
                        onClicked: {
                            deleteAdvert()
                        }
                    }
                }

                Text {
                    id: notice
                    text: "暂无"
                    font.pixelSize: 22
                    color: "#696969"
                    visible: (advertsRec.adverts[0].name === "NULL"
                              && advertsRec.adverts.length === 1 )
                             ? true : false
                }

                Repeater {
                    id: advertList
                    model: (advertsRec.adverts[0].name === "NULL"
                            && advertsRec.adverts.length === 1 ) ? 0 : advertsRec.adverts

                    Rectangle {
                        id: videoRec
                        width: videoRow.width
                        height: 1 / 5 * videoRow.height
                        property var name: modelData.name
                        property var company: modelData.company
                        property var clicks: modelData.clicks
                        property var duetime: modelData.duetime
                        property var check: false

                        Row {
                            spacing: 1 / 30 * videoRow.width
                            anchors.verticalCenter: parent.verticalCenter

                            Text {
                                width: 1 / 5 * videoRow.width
                                text: "Name: "+ videoRec.name
                                font.pixelSize: 14
                            }

                            Text {
                                width: 1 / 5 * videoRow.width
                                text: "Company: " + videoRec.company
                                font.pixelSize: 14
                            }

                            Text {
                                width: 1 / 5 * videoRow.width
                                text: "Clicks: " + videoRec.clicks
                                font.pixelSize: 14
                            }

                            Text {
                                width: 1 / 5 * videoRow.width
                                text: (judgeTime(videoRec.duetime) === true)
                                      ? "Time: " + videoRec.duetime
                                      : "Time: " + videoRec.duetime + " 已到期请删除"
                                font.pixelSize: (judgeTime(videoRec.duetime) === true)
                                                ? 14 : 12
                            }
                        }

                        CheckBox {
                            scale: 0.85
                            anchors.right: parent.right
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

    Dialog {
        id: deleteDialog
        width: 1 / 3 * mainWindow.width
        height: 1 / 3 * mainWindow.height
        visible: false
        anchors.centerIn: parent

        Column {
            id: content
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 1 / 5 * videoRow.height

            Text {
                text: "影视：" + txt.text
                font.pixelSize: 14
            }

            Text {
                text: "待删除广告：" + advertsmessage
                font.pixelSize: 14
            }

            Row {
                spacing: parent.spacing
                Button {
                    text: "Confirm"
                    onClicked: {
                        client.deleteVideoAdverts(txt.text, advertsmessage)
                        advertsRec.adverts =
                                JSON.parse(client.showVideoAdverts(txt.text, videotype))
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
    }

    Dialog {
        id: messageDialog
        width: 1 / 2 * deleteDialog.width
        height: 1 / 2 * deleteDialog.height
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

    function deleteAdvert(){
        advertsmessage = ""

        for(var i = 0; i != advertList.model.length; i++){
            if(advertList.itemAt(i).check === true){
                advertsmessage += advertList.itemAt(i).name
                advertsmessage += "/"
            }

            if(advertsmessage !== "" && txt.text !== ""){
                deleteDialog.open()
            }
        }
    }

    function judgeTime(duetime){
        var year = date.getFullYear()
        var month = date.getMonth()+1
        var day = date.getDate()

        var str = year+"-"+month+"-"+day
        var newstr = client.cliptime(str)
        console.log(newstr)

        if(duetime > newstr){
            return true
        }else{
            return false
        }
    }
}
