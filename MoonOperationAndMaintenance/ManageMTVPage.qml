import QtQuick 2.0
//import QtQuick.Controls 1.4
import QtQuick.Controls 2.4
import "./mtv"
Item {
    anchors.fill: parent
    Rectangle{
        id:menu
        anchors.top: parent.top
        width: parent.width
        height: 40
        color: "lightblue"
        Button{
            id:btn1
            text: "上架"
            anchors.top: parent.top
            anchors.left: parent.left
            width: 100
            height: parent.height
            onClicked: {
                stackView.push(ground)
            }
        }
        Button{
            id:btn2
            text: "下架"
            anchors.top: parent.top
            anchors.left: btn1.right
            anchors.leftMargin: 40
            width: 100
            height: parent.height
            onClicked: {
                stackView.push(under)
//                loader1.source = "UnderPage.qml"
            }
        }
        Button{
            id:btn3
            text: "更新"
            anchors.top: parent.top
            anchors.left: btn2.right
            anchors.leftMargin: 40
            width: 100
            height: parent.height
            onClicked: {
                stackView.push(update)
//                loader1.source = "GroundingMovie.qml"
            }
        }
        Text {
            id:nameTex

        }
    }

//    Loader{
//        id: loader1
//        anchors.fill: parent
//    }

    StackView{
        id:stackView
        width: parent.width
//        anchors.top: menu.bottom
        anchors.topMargin: 45
        anchors.fill: parent
        initialItem: ground
    }
    Component{
        id:under
        UnderPage{

        }
    }
    Component{
        id:ground
        GroundingMovie{

        }
    }
    Component{
        id:update
        UpdatePage{

        }
    }

//    Text {
//        text: qsTr("MTV")
//        anchors.horizontalCenter: anchors.horizontalCenter
//        font.pixelSize: 30
//    }
}
