/* Author:董梦丹
* Date:2020-04-26
* Note:广告
*/
import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    id: videopage
    width: parent.width
    height: parent.height

    property alias videoLoader: videopage.parent
    property var advertname: ""
    property var advertcompany: ""
    property var advertduetime: ""

    Connections {
        target: videoLoader
        onAdvertising: {
            console.log(name+" "+company+" "+duetime)
            advertname = name
            advertcompany = company
            advertduetime = duetime
        }
    }

    Image {
        id: button
        width: 1 / 20 * parent.width
        height: 1 / 20 * parent.width
        source: "../image/advert/left.png"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                videoLoader.source = "../ManageAdvertPage.qml"
            }
        }
    }

    Row {
        height: button.height
        spacing: 30
        anchors.horizontalCenter: parent.horizontalCenter
        Text {
            text: "待投放的广告信息：" + advertname + "," + advertcompany + "," + advertduetime
            font.pixelSize: 16
            anchors.verticalCenter: parent.verticalCenter
            color: "#6495ED"
        }

        Row {
            height: parent.height
            spacing: 15

            Text {
                text: "搜索影视名称："
                font.pixelSize: 14
                anchors.verticalCenter: parent.verticalCenter
            }

            TextField {
                id: txtInput
                width: 100
                height: 30
                anchors.verticalCenter: parent.verticalCenter
            }

            Image {
                id: searchbutton
                source: "qrc:/image/advert/search.png"
                anchors.verticalCenter: parent.verticalCenter
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(txtInput.text !== ""){
                            videoChoice.modelDelegate.model
                                    = JSON.parse(client.searchVideos(txtInput.text))
                        }
                    }
                }
            }
        }

        Button {
            id: advertisingButton
            text: "点击投放广告"
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    PutAdvertisingVideoMenu {
        id: videoTypeMenu
        anchors.top: button.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

    PutAdvertisingVideoList {
        id: videoChoice
        anchors.top: videoTypeMenu.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
