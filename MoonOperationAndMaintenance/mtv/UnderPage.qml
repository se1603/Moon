import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle {
    id:underP
    anchors.topMargin: 50
    width: parent.width
    height: parent.height
    color: "yellow"
    property string  underName:""


    property alias middleLoader: loader
    property alias browsePage: browseComponent
//    property alias playPage: playComponent

    property string playPost
    property string playName

    Loader{
        id: loader
        anchors.fill: parent
        sourceComponent: browseComponent
    }

    Component{
        id: browseComponent
        UnderBroese{

        }
    }

//    ListModel {
//        id:listModel
//        ListElement {
//            name: "西游记"
//            time: "2020-02-29"
//        }
//        ListElement {
//            name: "ll"
//            time: "2020-02-29"
//        }

//    }

//    ListView {
//        id:list
//        width: parent.width; height: 200

//        model: listModel
//        delegate:dele /*Text {
//              text: name + ": " + number
//          }*/
//    }

//    Component{
//        id:dele
//        Rectangle{
//            width: parent.width
//            height: 100
//            Text {
//                id:texName
//                anchors.left: parent.left
//                font.family: "Helvetica"
//                font.pointSize: 20
//                color: "blue"
//                text: name
//            }
//            CheckBox {
//                id:check
//                anchors.right: parent.right
//                onCheckedChanged: {
//                    if(check.checked === true){
//                        underName = underName+" "+texName.text
//                        console.log(underName)
//                    }
//                }
//            }

//        }
//    }
//    Button{
//        anchors.bottom: parent.bottom
//        anchors.bottomMargin: 200
//        text: "Cancle"
//        onClicked: {
//            dd.open()
//        }
//    }

//    PopupDialog
//    {
//        id:dd
//    }
}
