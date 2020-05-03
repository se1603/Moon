/* Author:徐丹
* Date:2020-03-25
* Note:更新对话框
*/
import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

Popup {
    id:updateDia
    padding: 10
    anchors.centerIn: parent
    width: 1000
    height: 800
    x:400
    y:300

    property alias name:name1.text
    property alias post: imgPup.updateFileSource//img.source
    property alias typeMo: typeMo.text
    property alias type: type1.text
    property alias region: region1.text
    property alias esd: esd.text
    property alias recommend: recc.text
    property alias infoma: infoma.text
    Layout.alignment: Qt.AlignHCenter
    Rectangle {

        id:upda
        width: parent.width
        height: parent.height



        UpDialog{
            id:up
        }



        Rectangle{
            id:btnF
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: 50
            width: parent.width*4/5-15
            height: 4/5*parent.height
//            border.color: "red"
            Rectangle{
                id:add
                anchors.left: parent.left
                width: 220
                height: 320
                border.color: "lightblue"

                Text{
                    text: "添加图片"
                    anchors.centerIn: parent
                    font.family: "Helvetica"
                    font.pointSize: 18
                    color: "blue"
                }
                Image {
                    id: img
                    source: /*imgSource//*/imgPup.updateFileSource
                    width: parent.width
                    height: parent.height
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {

                        imgPup.open()
                    }
                }

            }
            Text {
                id: nameLabel
                text: qsTr("名字：")
                anchors.left: add.right
                anchors.leftMargin: 20
                font.pointSize: 16
            }
            TextField{
                id:name1
                anchors.left: nameLabel.right
                font.pointSize: 16
            }
            Text {
                id:typeMo1
                text: "类别："
                font.pointSize: 16
                focus: true
                anchors.top: name1.bottom
                anchors.topMargin: 20
                anchors.left: add.right
                anchors.leftMargin: 20
            }
            TextField {
                id:typeMo
                width: 240
                font.family: "Helvetica"
                font.pointSize: 16
                focus: true
                anchors.top: name1.bottom
                anchors.topMargin: 20
                anchors.left: typeMo1.right
            }
            Text{
                id:type
                text: "类型:"
                anchors.top: typeMo1.bottom
                anchors.topMargin: 20
                anchors.left: add.right
                anchors.leftMargin: 20
                font.pointSize: 16
            }
            TextField {
                id:type1
                width: 240
                font.pointSize: 16
                focus: true
                anchors.top: typeMo.bottom
                anchors.topMargin: 20
                anchors.left: type.right
                anchors.leftMargin: 20
            }
            Text{
                id:region
                text: "地域："
                anchors.top: type.bottom
                anchors.topMargin: 20
                anchors.left: add.right
                anchors.leftMargin: 20
                font.pointSize: 16
            }

            TextField {
                id:region1
                width: 240
                font.pointSize: 16
                focus: true
                anchors.top: type1.bottom
                anchors.topMargin: 20
                anchors.left: region.right
            }


            Text{
                id:ed
                text: "集数："
                font.pointSize: 16
                focus: true
                anchors.top: region.bottom
                anchors.topMargin: 30
                anchors.left: add.right
                anchors.leftMargin: 20
            }
            TextField{
                id:esd
                width:100
                height: 35
                font.pointSize: 16
                focus: true
                anchors.top: region1.bottom
                anchors.topMargin: 20
                anchors.left: ed.right
            }
            Text {
                id: e
                text: qsTr("集")
                font.pointSize: 16
                focus: true
                anchors.top: region1.bottom
                anchors.topMargin: 20
                anchors.left: esd.right
            }

            Text {
                id: rec
                text: qsTr("是否推荐：")
                font.pointSize: 16
                focus: true
                anchors.top: ed.bottom
                anchors.topMargin: 30
                anchors.left: add.right
                anchors.leftMargin: 20
            }
            TextField{
                id:recc
                font.pointSize: 16
                focus: true
                anchors.top: esd.bottom
                anchors.topMargin: 20
                anchors.left: rec.right
//                text: "fff"
            }


            Rectangle{
                id:info
                width: parent.width-10
                height: 150
                clip: true
                anchors.top: add.bottom
                anchors.topMargin: 20
                border.color: "lightblue"
                Text {
                    id: infoma1
                    text: qsTr("简介：")
                    anchors.top: info.top
                    anchors.left: info.left
                    font.pointSize: 16

                }
                TextEdit{
                    id:infoma
                    width: parent.width-100
                    height: parent.height
                    wrapMode: TextEdit.Wrap
                    anchors.top: info.top
                    anchors.left: infoma1.right
                    anchors.leftMargin: 10
                    font.pointSize: 16
                    focus: true
                    text: "  "
                }

            }

            Rectangle{
                id:updateRtn
                width: parent.width/5
                height: 90//parent.height
                z:3
                anchors.left: parent.Left
                anchors.top:  info.bottom
                anchors.topMargin: 20
                anchors.leftMargin: 150
                Text {
                    id: name
                    anchors.centerIn: parent
                    font.pixelSize: 18
                    text: qsTr("「  更新   」")
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        var message = typeMo.text+" "+name1.text+" "+type1.text+" "+region1.text+" "+esd.text+" "+recc.text+" "+imgPup.updateFileSource+" "+imgPup.adress
                        console.log(message)
                        client.updateVideos(message)
                        date.close()
                    }
                    onEntered: {
                        name.font.pixelSize = 20
                    }
                    onExited: {
                        name.font.pixelSize = 18
                    }
                }
            }

            Rectangle{
                id:cancle
                width: parent.width/5
                height: 90//parent.height
                z:3
                anchors.left: updateRtn.right
                anchors.top:  info.bottom
                anchors.topMargin: 20
                anchors.leftMargin: 150
    //            anchors.bottomMargin: 100
                Text {
                    id: ca
                    anchors.centerIn: parent
                    font.pixelSize: 18
                    text: qsTr("「  取消   」")
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        date.close()

                    }
                    onEntered: {
                        name.font.pixelSize = 20
                    }
                    onExited: {
                        name.font.pixelSize = 18
                    }
                }
            }

            ImagePup{
                id:imgPup
            }
        }

    }
    Connections{
        target: client
        onUpdateSucceed:{
            messageDialog.visible=true
           console.log("更新成功！")
        }
    }

    Dialog {
        id: messageDialog
        width:200 //1 / 2 * deleteDialog.width
        height: 200//1 / 2 * deleteDialog.height
        visible: false
        anchors.centerIn: parent

        Column {
            spacing: 1 / 6 * parent.width
            anchors.centerIn: parent

            Text {
                text: "更新成功！"
            }

            Button {
                text: "Close"
                onClicked: {
                    messageDialog.close()
                }
            }
        }
    }

}
