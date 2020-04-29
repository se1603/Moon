import QtQuick 2.0

Rectangle {
    anchors.topMargin: 50
    width: parent.width
    height: parent.height
//    color: "black"

    ListModel {
        id:listModel
        ListElement {
            name: "Bill Smith"
            number: "555 3264"
        }
        ListElement {
            name: "John Brown"
            number: "555 8426"
        }
        ListElement {
            name: "Sam Wise"
            number: "555 0473"
        }
    }

    ListView {
        id:recommendNameView
        width: 180; height: 200

        model: listModel
        delegate: Text {
              text: name + ": " + number
          }
    }
//    Rectangle{
//        id:leftRec
//        anchors.left: parent.left
//        width: parent.width/5
//        height: parent.height
//        color: "red"
//    }
//    Rectangle{
//        id:rigntRec
//        anchors.right: parent.right
//        width: parent.width*4/5
//        height: parent.height
//        color: "yellow"
//    }
}
