/*
 * Date :2019.4.27
 * Author:xudan
 *
 * Date :2019.4.27
 * Author:xudan
 * 内容：播放主界面
 *
 * Author:王梦娟
 * Date:2019-5-25
 * Note:修改MouseArea覆盖的问题
*/

import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "../MiddleArea"

Rectangle {
    id: play
    visible: true
    width: middleArea.width
    height: middleArea.height

    property var datas: JSON.parse(client.showInfomation(play.name))
    property string name: middleArea.playName
    property string lastName: ""
    property string type: ""
    property string infoma:""
    property string image: middleArea.playPost
    property bool xRflag: false
    property bool xLflag: true
    property string url: middleArea.playUrl

    property var allAdverts: middleArea.adverts
    Component.onCompleted: {
        middleArea.stopPlay.connect(myplayer.stopPlay)
        middleArea.loadAdvert.connect(myplayer.playAdverts)
        middleArea.startPlay.connect(myplayer.startPlay)
    }

    //右边的组合动画
    ParallelAnimation{
        id: rightStarAnim
        //属性动画
        NumberAnimation{
            target: rightRectangle
            properties: "x"
            from: play.width
            to: 4/5*play.width
            //动画持续时间，毫秒
            duration: 500
            //动画渐变曲线
            easing.type: Easing.OutQuad
        }
        NumberAnimation{
            target: rightRectangle
            properties: "opacity"
            from: 0.2
            to: 0.8
            duration: 500;
            easing.type: Easing.OutQuad
        }
    }
    ParallelAnimation{
        id: rightStopAnim
        NumberAnimation{
            target: rightRectangle
            properties: "x"
            from: 4/5*play.width
            to: play.width
            duration: 500;
            easing.type: Easing.Linear
        }
        NumberAnimation{
            target: rightRectangle
            properties: "opacity"
            from: 0.8
            to: 0.2
            duration: 500;
            easing.type: Easing.Linear
        }
    }


    //左边的组合动画

    ParallelAnimation{
        id: leftStarAnim
        //属性动画
        NumberAnimation{
            target: leftRectangle
            properties: "x"
            from: 0
            to: -1/5*play.width
            //动画持续时间，毫秒
            duration: 500
            //动画渐变曲线
            easing.type: Easing.OutQuad
        }

    }
    ParallelAnimation{
        id: leftStopAnim
        NumberAnimation{
            target: leftRectangle
            properties: "x"
            from: -1/5*play.width
            to: 0
            duration: 500;
            easing.type: Easing.Linear
        }

    }
    Rectangle {
        id: rightRectangle
        x: xRflag?play.width:4/5*play.width
        y: 0
        width: 1/5*play.width
        height: play.height
        color: "#424242"
        Rectangle{
            id:leftM
            anchors.left: parent.left
            anchors.top:parent.top
            anchors.topMargin: 10
            width: 1/2*parent.width-8
            height:40
            color: "#424242"
            Button{
                anchors.fill: parent
                text: "简介"
                onClicked: {
                    right_stack.push(comment_page,StackView.Immediate)
                }
            }
            Text{
                text: adverts[0].rtsp
                font.pixelSize: 6
            }
        }

        Rectangle{
            anchors.top:parent.top
            anchors.topMargin: 10
            anchors.left:leftM.right
            anchors.leftMargin: 15
            width: 1/2*parent.width-8
            height: 40
            //                       height: parent.height-20
            color: "#424242"
            Button{
                anchors.fill: parent
                text: "评论"
                onClicked: {
                    right_stack.push(summary_page,StackView.Immediate)
                }
            }
        }

        StackView{
            width: parent.width
            height: 12/13*play.height
            anchors{
                left: parent.left
                right: parent.right
                bottom: parent.bottom
                //                top: toolBar.bottom
            }
            id:right_stack
            initialItem: comment_page
            MouseArea{
                anchors.fill: parent
            }
        }

        Component{
            id:summary_page
            Comment{

            }
        }
        Component{
            id:comment_page
            Program{
                id:e
            }
        }
    }

    Rectangle {
        id: leftRectangle
        x: xLflag?0:-1/5*play.width
        y: 0
        width: 1/5*play.width
        height: play.height
        color: "#424242"
        //        radius: 5

        Rectangle{
            id:toolBar
            anchors.top: parent.top
            width: parent.width
            height: 1/13*play.height
            color: "#424242"
            Rectangle{
                id:libraryRec
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top:parent.top
                anchors.topMargin: 5
                width: 1/4*parent.width
                height: parent.height-20
                color: "#424242"
                Button{
                    anchors.fill: parent
                    text: qsTr("片库")
                    onClicked: left_stack.push(library_page)
                }
            }
            Rectangle{
                id:localrect
                anchors.top:parent.top
                anchors.topMargin: 5
                anchors.left: libraryRec.right
                anchors.leftMargin: 15
                anchors.right: recordRect.left
                anchors.rightMargin: 15
                width: 1/4*parent.width
                height: parent.height-20
                color: "#424242"
                Button{
                    anchors.fill:parent
                    text: qsTr("本地")
                    onClicked: left_stack.push(local_page)
                }
            }
            Rectangle{
                id:recordRect
                anchors.top:parent.top
                anchors.topMargin: 5
                anchors.right: parent.right
                anchors.rightMargin: 10
                width: 1/4*parent.width
                height: parent.height-20
                color: "#424242"
                Button{
                    anchors.fill:parent
                    text: qsTr("记录")
                    onClicked: left_stack.push(record_page)
                }
            }
        }


        StackView{
            width: parent.width
            height: 12/13*play.height
            anchors{
                left: parent.left
                right: parent.right
                bottom: parent.bottom
                top: toolBar.bottom
            }

            MouseArea{
                anchors.fill: parent
            }
            id:left_stack
            initialItem: library_page
        }
        Component{
            id:local_page
            Local{

            }
        }
        Component{
            id:record_page
            Record{}
        }

        Component{
            id:library_page
            FilmLibraty{
            }
        }
    }

    Item{
        id:centerItem
        anchors.right: rightRectangle.left
        anchors.left: leftRectangle.right
        height: parent.height
        //        color:"green"

        VideoPlayer{
            id: myplayer
            anchors.fill: parent
            videoPath: url
            advertsPlaying: allAdverts
        }

        Rectangle{
            visible: play.name ? false :true
            width: parent.width
            height: parent.height
            color:  "#8B8378"
            Text{
                anchors.centerIn: parent
                text: "请选择视频播放"
                font.pixelSize: 28
                color: "white"
            }
        }
    }

    Rectangle{
        id:rightbt
        y:parent.height/2
        z:3
        anchors.right: center.right
        width: 20
        height: 30
        opacity: 0.5
        Image{
            id:rightButton
            opacity: 1
            mirror: true
            anchors.fill: parent
            source: "qrc:/image/img/left.png"
        }
        MouseArea{
            id:rightMouse
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                if(rightRectangle.x === play.width)
                {
                    rightStarAnim.start()
                    xRflag = false
                }
                else
                {
                    rightStopAnim.start()
                    xRflag = true
                }
            }
        }
    }

    //左箭头，点击，会回到前一张图片
    Rectangle{
        id:leftbu
        y:parent.height/2
        z:3
        anchors.left: center.left
        width: 20
        height: 30
        opacity: 0.5
        Image{
            id:leftButton
            anchors.fill: parent
            opacity: 1
            source: "qrc:/image/img/left.png"
        }
        MouseArea{
            id:leftMouse
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            onClicked: {
                if(leftRectangle.x === 0)
                {
                    leftStarAnim.start()
                    xLflag = false
                }
                else
                {
                    leftStopAnim.start()
                    xLflag = true
                }
            }
        }
    }
}
