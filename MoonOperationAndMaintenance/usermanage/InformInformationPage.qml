/*
 * guchangrong   2016051604218
 * 2020-2-14
 * 管理员处理用户举报信息
 */
import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Rectangle{
    id:untreatedinformationpage
    width: parent.width
    height: parent.height

    property var info:""


    Rectangle{
        id:toprectangle
        width: parent.width
        height: 1/20 * parent.height
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        //退出按钮
        Rectangle{
            id: closebutton
            width: 50
            height: parent.height
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.verticalCenter: toprectangle.verticalCenter
            color: "lightgray"
            Image {
                id: closeicon
                height: 20
                width: 35
                anchors.right: closebutton.right
                anchors.rightMargin: 5
                anchors.verticalCenter: parent.verticalCenter
                opacity: closemousearea.containsMouse ? 1.0 : 0.8
                source: "qrc:/image/manage/close.png"
                MouseArea{
                    id:closemousearea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        reportStack.pop()
                        console.log(info)
                    }
                }
            }
        }
    }

    Rectangle{
        id: informationlist
        width: parent.width
        height: 14/15 * parent.height
        anchors.top: toprectangle.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        Column{
            width: parent.width
            height: parent.height
            spacing: 2
            Repeater{
                model:  info
                Rectangle{
                    id:list
                    width: informationlist.width
                    height: informationlist.height
//                    border.color: "black"
//                    border.width: 2
//                    radius: 5
                    ColumnLayout{
                        anchors.left: parent.left
                        anchors.leftMargin: 20
                        anchors.top: parent.top
                        spacing: 20
                        Text {
                            text: '<b>ID: </b>' + modelData.id
                        }
                        Text {
                            text: '<b>被举报人：</b>' + modelData.bereported
                        }
                        Text {
                            text: '<b>举报人：</b>' + modelData.informer
                        }
                        Text {
                            text: '<b>被举报次数：</b>' + modelData.informcount
                        }
                        Text {
                            text: '<b>举报时间: </b>' + modelData.date
                        }
                        Text {
                            text: '<b>评论: </b>' + modelData.comment
                            wrapMode: Text.WrapAnywhere
                            font.pixelSize: 18
                        }
                    }
                    Row{
                        id:buttons
                        width: parent.width
                        height: 1/15 * parent.height
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 1/8 * parent.height
                        anchors.left: parent.left
                        anchors.leftMargin: 1/10 * parent.width
                        spacing: 30
                        Button{
                            id:dropcomment
                            text: "「删除评论」"
                            flat: true
                            onClicked: {
                                console.log("删除评论成功")
                                console.log(modelData.bereported)
                                client.deleteInformedComment(modelData.bereported, modelData.comment)
                                client.updateInformmark(modelData.id)
                            }
                        }
                        Button{
                            id:freezeuser
                            flat: true
                            text: "「冻结用户」"
                            onClicked: {
                                console.log("冻结用户成功")
                            }
                        }
                    }
                }
            }
        }
    }

}



