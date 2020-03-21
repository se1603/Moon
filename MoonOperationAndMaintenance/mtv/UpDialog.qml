import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
Popup {
    id:up
    padding: 10

    anchors.centerIn: parent
    width: 400
    height: 200
    x:400
    y:300

     Layout.alignment: Qt.AlignHCenter
    Text{
        id:input
        anchors.centerIn: parent
        text: "确认上传吗"
        font.family: "Helvetica"
        font.pointSize: 20
        color: "blue"
    }
    Button{
        id:btnOk
        text: "OK"
        anchors.top: input.bottom
        anchors.topMargin: 30
        onClicked: {
            client.noticeUp()
            up.close()
        }
    }
    Button{
        id:canncle
        text: "Cancle"
        anchors.top: input.bottom
        anchors.topMargin: 30
        anchors.left: btnOk.right
        anchors.leftMargin: 20
        onClicked: {
            up.close()
        }
    }

}
