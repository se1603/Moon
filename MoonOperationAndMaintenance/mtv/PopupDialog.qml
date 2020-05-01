import QtQuick 2.0
import QtQuick.Controls 2.5


Popup {
    id:pop
    padding: 10
    anchors.centerIn: parent
    width: 200
    height: 200
    x:400
    y:300
    Text{
        anchors.centerIn: parent
        text: "确认删除"
        font.family: "Helvetica"
        font.pointSize: 20
        color: "blue"
    }

    Button{
        text: "OK"
        anchors.bottom: parent.BottomRight
        onClicked: {
            recommendPage.flage = false
//            recommendResource = JSON.parse(client.showRecommend("电影"))
            dd.close()
        }
    }


}
