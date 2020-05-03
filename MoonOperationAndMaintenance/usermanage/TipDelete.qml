import QtQuick 2.0

Rectangle {
    id:tipdelete
    width: parent.width * 1/6
    height: parent.height * 1/7
    border.color: "gray"
    anchors.centerIn: parent
    radius: 4
//    opacity: 0.2
    Rectangle{
        id:back
        width: 16
        height: 16
        radius: 8
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        color: "red"
        Image {
            id: backicom
            width: 16
            height: 16
            anchors.centerIn: parent
            source: "qrc:/image/close.png"
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    reportStack.pop()
                }
            }
        }
    }
    Text {
        id: deletetip
        anchors.centerIn: parent
        font.pixelSize: 24
        text: qsTr("评论已删除")
    }
}
