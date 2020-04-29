/* Author:董梦丹
* Date:2020-02-22
* 最后修改: 04-26
* Note:广告
*/
import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle {
    width: parent.width
    height: parent.height
    anchors.top: parent.top

    property var advertsmessage:""
    property var backmessage:""
    //    property var videotype: parent.currentType

    property var date: new Date()
    property var currentPost: ""
    property var currentName: ""

    //    Connections {
    //        target: client
    //        onDeleteAdvertSucceed: {
    //            deleteDialog.close()
    //            backmessage = "Succeed!"
    //            messageDialog.open()
    //        }
    //        onDeleteAdvertFailed: {
    //            deleteDialog.close()
    //            backmessage = "Failed!"
    //            messageDialog.open()
    //        }
    //    }

    Row {
        id: videoRow
        width: 2 / 3 * parent.width
        height: 160
        spacing: 15
        anchors.horizontalCenter: parent.horizontalCenter

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
                    videoDetail.visible = false
                }
            }
        }

        Image {
            id: post
            width: 120
            height: 160
            source: "file:" + currentPost
        }

        Text {
            id: txt
            text: currentName
            font.pixelSize: 18
        }
    }

    Text {
        id: txttitle
        text: "该影视所投放的广告："
        font.pixelSize: 16
        anchors.left: videoRow.left
        anchors.leftMargin: 65
        anchors.top: videoRow.bottom
        anchors.topMargin: 10
    }

    Rectangle {
        id: advertsRec
        width: 600
        height: parent.height - videoRow.height - txttitle.height - 10
        anchors.top: txttitle.bottom
        anchors.left: videoRow.left
        anchors.leftMargin: 65

//        color:"green"

        property var adverts:
            JSON.parse(client.showVideoAdverts(txt.text, videoTypeMenu.types))

        ScrollView {
            anchors.fill: parent
            clip: true
            ColumnLayout {
                anchors.top: parent.top
                anchors.topMargin: 15
                spacing: 30

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
                        width: 600
                        height: 20
                        property var name: modelData.name
                        property var company: modelData.company
//                        property var clicks: modelData.clicks
                        property var duetime: modelData.duetime
//                        property var check: false

                        Row {
                            spacing: 30
                            anchors.verticalCenter: parent.verticalCenter

                            Text {
                                text: "Name: "+ videoRec.name
                                font.pixelSize: 14
                            }

                            Text {
                                text: "Company: " + videoRec.company
                                font.pixelSize: 14
                            }

                            Text {
                                text: "Time: " + videoRec.duetime

                                /*(judgeTime(videoRec.duetime) === true)
                                      ? "Time: " + videoRec.duetime
                                      : "Time: " + videoRec.duetime + " 已到期请删除"*/

                                font.pixelSize: 14

                                /*(judgeTime(videoRec.duetime) === true)
                                                ? 14 : 12*/

                            }
                        }
                    }
                }
            }
        }
    }

//    function judgeTime(duetime){
//        var year = date.getFullYear()
//        var month = date.getMonth()+1
//        var day = date.getDate()

//        var str = year+"-"+month+"-"+day
//        var newstr = client.cliptime(str)
//        console.log(newstr)

//        if(duetime > newstr){
//            return true
//        }else{
//            return false
//        }
//    }
}
