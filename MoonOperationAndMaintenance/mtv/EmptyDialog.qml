import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
Popup {
    id:empty
    padding: 10

    anchors.centerIn: parent
    width: 300
    height: 200
    x:400
    y:300

     Layout.alignment: Qt.AlignHCenter
    Text{
        id:input
        anchors.top: parent.Top
        anchors.left: parent.Left
        anchors.leftMargin: 80
        text: "文件为空"
        font.family: "Helvetica"
        font.pointSize: 20
        color: "blue"
    }


}
