/* Author:董梦丹
* Date:2020-04-26
* Note:广告
*/
import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4

Rectangle {
    id:puttingpage
    width: parent.pagewidth
    height: parent.pageheight

    property alias advertLoader: puttingpage.parent

    Image {
        id: button
        width: 1 / 20 * parent.width
        height: 1 / 20 * parent.width
        source: "../image/advert/left.png"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                advertLoader.source = "../ManageAdvertPage.qml"
            }
        }
    }

    Row {
        id: titleRow
        width: 1 / 3 * parent.height
        height: button.height
        anchors.left: button.right
        Text {
            text: "全部映前广告："
            font.pixelSize: 16
            anchors.verticalCenter: parent.verticalCenter
            color: "#6495ED"
        }
    }

    Text {
        id: title
        text: "请选择待投放的广告： "
        font.pixelSize: 16
        color: "#99CCFF"
        anchors.top: titleRow.bottom
        anchors.left: titleRow.left
    }

    Rectangle {
        id: listRec
        width: 4 / 5 * parent.width
        height: parent.height - button.height - title.height
        anchors.top: title.bottom
        anchors.left: button.right

        ScrollView {
            anchors.fill: parent
            clip: true
            verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff

            ColumnLayout {
                Repeater {
                    id: advertList
                    model: JSON.parse(client.showAllVideoAdverts())

                    Rectangle {
                        id: listRow
                        width: listRec.width
                        height: 1 / 10 * listRec.height

                        property var name: modelData.name
                        property var company: modelData.company
                        property var clicks: modelData.clicks
                        property var duetime: modelData.duetime
                        property var check: false

                        Row {
                            spacing: 20
                            anchors.verticalCenter: parent.verticalCenter

                            Text {
                                width: 1 / 4 * listRow.width
                                text: "名称："+ listRow.name
                                font.pixelSize: 14
                            }

                            Text {
                                width: 1 / 4 * listRow.width
                                text: "公司：" + listRow.company
                                font.pixelSize: 14
                            }

                            Text {
                                width: 1 / 4 * listRow.width
                                text: "到期时间：" + listRow.duetime
                                font.pixelSize: 14
                            }

                            CheckBox {
                                property var myname: parent.name
                                style:
                                    CheckBoxStyle {
                                    indicator: Rectangle {
                                        implicitWidth: 20
                                        implicitHeight: 20
                                        radius: 3
                                        border.color: control.activeFocus ? "blue" : "gray"
                                        border.width: 1
                                        Rectangle {
                                            visible: control.checked === true
                                            color: "#6495ED"
                                            border.color: "#333"
                                            radius: 1
                                            anchors.margins: 4
                                            anchors.fill: parent
                                        }
                                    }
                                }
                                checked: listRow.check
                                onClicked: {
                                    listRow.check = checked
                                    judgeBeSelected()
                                    judgeToSelect()
                                }
                            }
                        }
                    }
                }
            }
        }
    }

//    Dialog {
//        id: messageDialog
//        width: 1 / 7 * parent.width
//        height: 1 / 6 * parent.height
//        visible: false
//        anchors.centerIn: parent

//        Column {
//            width: 3 / 4 * parent.width
//            height: 3 / 4 * parent.height
//            spacing: 1 / 10 * parent.width
//            anchors.centerIn: parent

//            Text {
//                text: "未勾选广告请先选择广告"
//                width: parent.width
//                wrapMode: Text.Wrap
//                font.pixelSize: 14
//            }

//            Button {
//                text: "Close"
//                onClicked: {
//                    messageDialog.close()
//                }
//            }
//        }
//    }

    Column{
        spacing: 30
        anchors.right: parent.right
        anchors.rightMargin: spacing
        anchors.top: title.top

        Text {
            text: "请选择投放模式（单选）："
            font.pixelSize: 16
            color: "#99CCFF"
        }

        Text {
            text: "映前广告"
            font.pixelSize: 16
            color: "#6495ED"
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    parent.opacity = 0.6
                }
                onExited: {
                    parent.opacity = 1
                }
                onClicked: {
                    selection()
                }
            }
        }

        Text {
            text: "图片模式"
            font.pixelSize: 16
            opacity: 0.6
            color: "#666666"
        }
    }

    function judgeBeSelected(){
        var index = 0
        for(var i = 0; i != advertList.model.length; i++){
            if(advertList.itemAt(i).check === true){
                index = i
            }
        }
        for(var j = 0; j != advertList.model.length; j++){
            if(j !== index){
                advertList.itemAt(j).enabled = false
            }
        }
    }

    function judgeToSelect(){
        var flag = 0
        for(var i = 0; i != advertList.model.length; i++){
            if(advertList.itemAt(i).check === false){
                flag++
            }
        }

        if(flag === advertList.model.length){
            for(var j = 0; j != advertList.model.length; j++){
                advertList.itemAt(j).enabled = true
            }
        }
    }

    function selection(){
        for(var i = 0; i != advertList.model.length; i++){
            if(advertList.itemAt(i).check === true){
                var name = advertList.itemAt(i).name
                var company = advertList.itemAt(i).company
                var duetime = advertList.itemAt(i).duetime
                nextStep(name,company,duetime)
            }
        }
    }

    Loader {
        id: videoLoader
        anchors.fill: parent
        source:""
        signal advertising(var name, var company, var duetime)
    }

    function nextStep(name,company,duetime){
        videoLoader.source = "PutAdvertisingVideo.qml"
        videoLoader.advertising(name,company,duetime)
    }
}
