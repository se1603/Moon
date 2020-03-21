import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
Popup {
    id:addPop
    padding: 10

    anchors.centerIn: parent
    width: 300
    height: 200
    x:400
    y:300
//    property alias namePo: txField
     Layout.alignment: Qt.AlignHCenter
    Text{
        id:input
        anchors.top: parent.Top
        anchors.left: parent.Left
        anchors.leftMargin: 80
        text: "请输入新名字"
        font.family: "Helvetica"
        font.pointSize: 20
        color: "blue"
    }

    Text{
        id:name
        text: "名字："
        font.pixelSize: 15
        anchors.top: input.bottom
        anchors.topMargin: 20
        anchors.left: parent.Left
    }
    TextField{
        id: txField
        anchors.topMargin: 20
        anchors.left: name.right
        anchors.top: input.bottom
        Layout.preferredWidth: 100
        font.pixelSize: 15
    }

    Button{
        id:btnOk
        text: "OK"
        anchors.top: txField.bottom
        anchors.topMargin: 30
        onClicked: {
            console.log(txField.text)
            listModel.append({"name":txField.text,episode: " ",
                                 typ:"悬疑",
                                 region:"中国",
                                 bigType:"电影",
                                 introduction:"简介",
                                 actor:"演员",
                                 dictor:"导演",
                                 imgSource:" ",
                                 about:"相关影视"})
            addDig.close()
        }
    }

    Button{
        text: "Cancle"
        anchors.top: txField.bottom
        anchors.left: btnOk.right
        anchors.leftMargin: 30
        anchors.topMargin: 30
        onClicked: {
//            console.log(txField.text)
//            listModel.append({"name":txField.text})
            addDig.close()
        }
    }
}
