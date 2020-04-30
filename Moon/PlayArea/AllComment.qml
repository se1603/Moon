//Author:徐丹
//time：2019.4.28
//全部评论界面

import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

ScrollView{
    anchors.fill: parent
    id:all_scroll
    background: Rectangle{
        anchors.fill: parent
        color: "#424242"
    }

    clip: true
    property var models
    property bool listFlag: false

    Rectangle{
        width: parent.width
        height: 100
        color: "#424242"
        visible: listFlag ? false : true
        Text{
            text: "暂无评论"
            color: "#A9A9A9"
            font.pixelSize: 24
            anchors.centerIn: parent
        }
    }

    ListView{
        id:listview
        anchors.fill: parent
        model:models
        delegate: dele
    }


    Component{
        id:dele
        Rectangle{
            width: all_scroll.width
            height: 84
            color:"#424242" //"#8B8378"

            CommentPop{
                id:dd
            }
            Text{
                id:all_name
                anchors.top:parent.top
                anchors.left: parent.left
                text:modelData.audienceName
                font.pixelSize: 14
                color: "#00BFFF"
                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    enabled: true

                    onEntered: {
                        parent.color = "red"
                    }
                    onExited: {
                        parent.color= "#00BFFF"
                    }
                }
            }
            Rectangle{
                id:all_message
                anchors.top: all_name.bottom
                width: parent.width
                height: parent.height/2
                color: "#424242"
                Text{
                    id:all_te
                    width: parent.width-10
                    anchors.top: parent.top
                    anchors.topMargin: 2
                    anchors.left: parent.left
                    anchors.leftMargin: 2
                    font.pixelSize: 14
                    text: modelData.comment
                    wrapMode: Text.Wrap
                    color: "#A9A9A9"
                }
            }
            Text{
                id:all_time
                anchors.top: all_message.bottom
                anchors.left: parent.left
                text:modelData.time
                font.pixelSize: 12
                color: "#A9A9A9"
            }
            Rectangle{
                id:tip
                width: parent.width-10
                height: 20
                anchors.centerIn: parent
                visible: false
                Text{
                    id:informtip
                    anchors.centerIn: parent
                    font.pixelSize: 12
                    color:"#00BFFF"
                    text: "举报成功，请等待审核！"
                }
                MouseArea{
                    anchors.fill: parent
                    onCanceled: {
                        tiptimer.stop()
                        tip.visible = false
                    }
                }
            }

            Rectangle{
                id:all_reply
                anchors.top:all_message.bottom
                anchors.right: parent.right
                anchors.rightMargin: 64
                width: replys.implicitWidth
                height: replys.implicitHeight
                color: "#424242"
//                opacity:0.4
                Text{
                    id:replys
                    font.pixelSize: 14
                    anchors.fill: parent
                    text: "回复"
                    color:"#00BFFF"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        if(audienceInterface.audienceName == ""){
                            audienceItem.open()
                        }else{
                            dd.open()
                        }
                    }
                }
            }
            Rectangle{
                id:inform
                anchors.top:all_message.bottom
                anchors.right: parent.right
                anchors.rightMargin: 14
                width: informs.implicitWidth
                height: informs.implicitHeight
                color: "#424242"
//                opacity:0.4
                Text{
                    id:informs
                    font.pixelSize: 14
                    anchors.fill: parent
                    text: "举报"
                    color:"#00BFFF"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        var year = commentData.getFullYear()
                        var month = commentData.getMonth()+1
                        var day = commentData.getDate()
                        var informtime = year+"-"+month+"-"+day
                        var bereported = modelData.audienceName
                        var comment = modelData.comment
                        var informer = middleArea.audienceInterface.audienceName
                        console.log(bereported)
                        console.log(comment)
                       client.inform(informer,bereported,comment,informtime)
                        tiptimer.start()
                    }
                }
            }

            Timer{
                id:tiptimer
                interval: 1500
                repeat: true
                onTriggered: {
                    tip.visible = true
                }
            }

            Rectangle{
                width: parent.width
                height: 2
                color: "#8B8378"
                anchors.top: all_reply.bottom
                anchors.left: parent.left
                anchors.right: parent.right
            }
        }
    }
}
