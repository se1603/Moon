import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
Popup {
    id:deleteD
    padding: 10

    anchors.centerIn: parent
    width: 200
    height: 200
    x:400
    y:300

     Layout.alignment: Qt.AlignHCenter
    Text{
        id:input
        anchors.centerIn: parent
        text: "删除成功"
//        font.family: "Helvetica"
        font.pointSize: 20
        color: "blue"
    }
    Button{
        id:btnOk
        text: "OK"
        anchors.top: input.bottom
        anchors.topMargin: 30
        onClicked: {
            dele.close()
        }
    }

}
