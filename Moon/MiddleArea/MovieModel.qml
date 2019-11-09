import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
Rectangle {

    width: parent.width
    height: parent.height
    //    color: "red"

//    property alias stackName: comic_stack


    Rectangle {
        anchors.top:parent.top
        anchors.topMargin: 40
        width: parent.width; height: parent.height
        //        y:40

        Component {
            id: contactDelegate
            Item {
                width: grid.cellWidth; height: grid.cellHeight
                Column {
                    anchors.fill: parent
                    //                    leftPadding: 20
                    Rectangle { border.color: "red"; width: grid.cellWidth-10;height: grid.cellHeight-40;anchors.horizontalCenter: parent.horizontalCenter
                        color: "red"//图片
                    }
                    Text {
                        text: modelData//名字
                        font.pixelSize: 15
                        wrapMode: Text.Wrap; anchors.horizontalCenter: parent.horizontalCenter }
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {

                    }
                }
            }
        }

        GridView {
            id: grid
            //            anchors.topMargin: 60
            anchors.fill: parent
            cellWidth: parent.width>1080?parent.width/6:parent.width/4; cellHeight: parent.width>1080? 330 : 340
            model: 10
            delegate: contactDelegate
            focus: true
        }
    }

}
