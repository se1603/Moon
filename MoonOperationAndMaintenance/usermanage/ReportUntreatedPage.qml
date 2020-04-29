/*
 * guchangrong   2016051604218
 * 2020-2-14
 * 管理员处理用户举报主页面
 */
import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Rectangle {
    id: usermanager
    anchors.fill: parent

    property var manageuserinfo:JSON.parse(client.getManageUserInfoByMark("untreated"))
    property var untreatedinformation:JSON.parse(client.getManageUserInfoByID(untreatedid))
    property var untreatedid

    //页面顶部栏
    Rectangle{
        id: toptitle
        width:parent.width
        height: 1/15 * parent.height
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        Text {
            id: tips
            text: qsTr("Welcome")
            anchors.left: toptitle.left
            anchors.verticalCenter: toptitle.verticalCenter
            font.pixelSize: 25
            font.bold: true
            color: "black"
        }

        Text {
            id: manager
            text: qsTr("2020001")
            anchors.left: tips.right
            anchors.leftMargin: 20
            anchors.verticalCenter: toptitle.verticalCenter
            font.pixelSize: 20
            font.bold: true
        }

        Button{
            id:pending
            width: 100
            height:30
            text: "「待处理」"
            anchors.verticalCenter: toptitle.verticalCenter
            anchors.left: manager.right
            anchors.leftMargin: 250
            flat: true

            onClicked: {
                pending.highlighted = true
                done.highlighted = false
                reportStack.push(reportUntreatedPage)
                console.log("待处理")
            }

        }

        Button{
            id:done
            width: 100
            height:30
            text: "「已完成」"
            anchors.verticalCenter: toptitle.verticalCenter
            anchors.left: pending.right
            anchors.leftMargin:10
            flat: true
            onClicked: {
                done.highlighted = true
                pending.highlighted = false
                reportStack.push(reportProcessedPage)
                console.log("已完成")
            }
        }

        //color: "black"
    }

    //事务列表
    Rectangle{
        id: feedbacklist
        width: parent.width
        height: 14/15 * parent.height
        anchors.top: toptitle.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        Column{
            width: parent.width
            height: parent.height
            spacing: 2
            Repeater{
                model:  manageuserinfo
                Rectangle{
                    id:list
                    width: feedbacklist.width
                    height: 1/11 * feedbacklist.height
                    border.color: "black"
                    border.width: 2
                    radius: 5
                    RowLayout{
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 50
                        CheckBox{
                            id:isChoice
                            onClicked: {

                            }

                        }
                        Text {
                            id: id
                            text: "ID: " + modelData.id
                            font.pixelSize: 22
                        }
                        Text {
                            id: jubaoren
                            text: "举报人:" + modelData.informer;
                            font.pixelSize: 22
                        }
                        Text {
                            id: beijubaoren
                            text: "被举报人:" + modelData.bereported;
                            font.pixelSize: 22
                        }
                        Button {
                            id: jubaoxinxi
                            text: "「查看详情」"
                            font.pixelSize: 22
                            flat: true
                            onClicked: {
                                untreatedid = modelData.id
                                console.log(untreatedid)
                                untreatedinformation = JSON.parse(client.getManageUserInfoByID(untreatedid))
                                console.log(untreatedinformation)
                                manageuserPage.untreatedinfobyid = untreatedinformation
                                reportStack.push(informinformationpage)
                                console.log("显示成功")
                            }
                        }
                    }
                }
            }
        }
    }

}
