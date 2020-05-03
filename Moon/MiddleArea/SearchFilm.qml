/*
  * author:guchangrong 2016051604218
  * date:2020.4.26
  * 显示搜索电影的界面
  */
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import "../TopArea"

Rectangle {
    id: movie
    height: parent.height
    width: parent.width
    anchors.fill: parent
    property var showResult: middleArea.searchResource.resource

    property var date: new Date()

    //显示信息栏
    Rectangle{
        id: showrectanggle
        width: parent.width
        height: 19/20 * parent.height
        anchors.top: toprectangle.bottom
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.verticalCenter: parent.verticalCenter
        //        color: "gray"

        Rectangle{  //提示搜索内容
            id:relation
            height: 40
            width: parent.width
            anchors.top: toprectangle.bottom
            anchors.left: parent.left
            //            color: "#FAF0E6"
            Row{
                id:rowbutton
                spacing: 10
                anchors.left: parent.left
                Rectangle{
                    id:button1
                    width: 40
                    height: 30
                    border.width: 1
                    border.color: "gray"
                    Text {
                        id: button1text
                        anchors.centerIn: parent
                        text: qsTr("相关")
                    }
                }
                Rectangle{
                    id:button2
                    width: 40
                    height: 30
                    border.width: 1
                    border.color: "gray"
                    Text {
                        id: button2text
                        anchors.centerIn: parent
                        text: qsTr("最新")
                    }
                }
                Rectangle{
                    id:button3
                    width: 40
                    height: 30
                    border.width: 1
                    border.color: "gray"
                    Text {
                        id: button3text
                        anchors.centerIn: parent
                        text: qsTr("最热")
                    }
                }
            }
        }
        Rectangle{   //将搜索的内容以列表的形式显示
            id:showlist
            width: 4/5 * parent.width
            height: parent.height-40
            anchors.top: relation.bottom
            anchors.left: parent.left

            Column{
                anchors.top: parent.top
                anchors.left: parent.left
                spacing: 10
                Repeater{
                    model: showResult
                    Rectangle{
                        width: showlist.width
                        height: 200
                        border.width: 1
                        border.color: "lightgray"
                        Rectangle{
                            id:showposter
                            width: 120
                            height: 180
                            anchors.left: parent.left
                            anchors.leftMargin: 25
                            anchors.verticalCenter: parent.verticalCenter
                            border.width: 2
                            border.color: "gray"

                            Image {   //显示海报
                                id: poster
                                width:120
                                height: 180
                                anchors.fill: parent
                                source: "file:" + modelData.post
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        console.log(poster.source)

                                    }
                                }
                            }


                        }
                        Text{   //显示影视节目名称
                            id: movietitle
                            width: 100
                            height: 35
                            anchors.left: showposter.right
                            anchors.leftMargin: 20
                            anchors.top: parent.top
                            anchors.topMargin: 20
                            font.pixelSize: 24
                            color: "lightblue"
                            text: modelData.name
                        }
                        Text{     //显示简介
                            id: movieintro
                            width: parent.width - 240
                            height: 50
                            anchors.left: showposter.right
                            anchors.leftMargin: 20
                            anchors.top: movietitle.bottom
                            anchors.topMargin: 20
                            font.pixelSize: 12
                            wrapMode: Text.WrapAnywhere
                            lineHeight: 1
                            text:modelData.introduction
                        }
                        Rectangle{   //播放按钮
                            id: playbutton
                            width: 80
                            height: 30
                            color: "#FFEFD5"
                            anchors.left: showposter.right
                            anchors.leftMargin: 50
//                            anchors.top: movieintro.bottom
//                            anchors.topMargin: 30
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 30
                            MouseArea{
                                id:playmousearea
                                anchors.fill: parent
                                hoverEnabled: true
                                onClicked: {
                                    //开始记录
                                    var d = new Date()
                                    var year = d.getFullYear()
                                    var month = d.getMonth()+1
                                    var day = d.getDate()
                                    var hours = d.getHours()
                                    var minutes = d.getMinutes()
                                    var starttime =
                                            year+"-"+month+"-"+day+"-"
                                            +hours+":"+minutes
                                    if(middleArea.startTime === ""){
                                        middleArea.startTime = starttime
                                    }else{
                                        middleArea.lastStartTime =
                                                middleArea.startTime
                                        middleArea.startTime = starttime
                                    }


                                    middleArea.nextName = modelData.name
                                    middleArea.stopPlay(playName,nextName)

                                    playName = modelData.name
                                    playPost = "file:" + modelData.post
                                    playUrl = modelData.rtspURL

                                    middleArea.middleLoader.visible = false
                                    middleArea.playLoader.visible = true
                                    adverts = JSON.parse(client.advertInfo(playName))
                                    if(adverts !== null)
                                    {
                                        middleArea.loadAdvert()
                                    }
                                    else
                                    {
                                        console.log(playUrl)
                                        middleArea.startPlay()
                                    }
                                }
                            }

                            Text {
                                id: buttontitle
                                anchors.horizontalCenter: playbutton.horizontalCenter
                                anchors.verticalCenter: playbutton.verticalCenter
                                font.pixelSize: 18
                                color: "lightblue"
                                text: qsTr("开始播放")
                            }
                        }
                    }
                }
            }

        }  //showlist
    }//showrectangle
//    function load_page(page){
//            search_stack.push(searchmovie, StackView.Immediate)
//    }
}//searchpage
