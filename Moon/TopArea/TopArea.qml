import QtQuick 2.0

Rectangle {
    id: topInterface
    width: parent.width
    height: 38 //1 / 18 * parent.height
//    color: "blue"

    property alias rightButton:rightButton

    Rectangle{
        id:icon
        width: 1/11 * parent.width
        height: parent.height
        color: "#F5F5F5"
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        Image {
            id: stIcon
            source: "qrc:/image/TopArea/StarIcon.png"
            width: parent.width
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
        }

    }

    Rectangle{
        id:mainpage
        width: 1/16 * parent.width
        height: parent.height - 5
        radius: 20
        anchors.left: icon.right
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        color: middleArea.middle ? "#1E90FF" : "#F5F5F5"
        z:1
        Text {
            id: mainpagetitle
            text: qsTr("主页")
            font.pixelSize: 23
            color: middleArea.middle ? "white" : "#696969"
            anchors.horizontalCenter: mainpage.horizontalCenter
            anchors.verticalCenter: mainpage.verticalCenter
        }
        MouseArea{
            id: mainpagemousearea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                middleArea.middleLoader.visible = true
                middleArea.playLoader.visible = false
               middleArea.middleLoader.sourceComponent = middleArea.browsePage
                middleArea.audienceInterface.visible = false
            }
        }
    }
    //点击按钮，跳转到播放页面
    Rectangle{
        id:play
        width: 1/16 * parent.width
        height: parent.height - 5
        radius: 20
        anchors.left: mainpage.right
        anchors.leftMargin: 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.topMargin: 0
        z:1
        color: middleArea.play ? "#1E90FF" : "#F5F5F5"
        Text {
            id: playTitle
            text: qsTr("播放")
            font.pixelSize: 23
            color: middleArea.play ? "white" : "#696969"
            anchors.horizontalCenter: play.horizontalCenter
            anchors.verticalCenter: play.verticalCenter
        }
        MouseArea{
            id: playpagemousearea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                middleArea.middleLoader.visible = false
                middleArea.playLoader.visible = true
                middleArea.audienceInterface.visible = false
            }
        }
    }

    Search{

    }
    RightButton {  //右边按钮组件
        id:rightButton
    }
}
