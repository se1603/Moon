/* Author:董梦丹
* Date:2020-04-26
* Note:广告
*/
import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: typeMenu
    width: parent.width
    height: 1 / 10 * parent.height

    property var types:"电影"
    property var selectedType:""

    property bool flag:true

    signal selectAll(var typename)
    signal cancelSelect(var cancelname)
    signal sendBack(var typename)

    Row{
        height: parent.height
        spacing: 1 / 10 * parent.width
        anchors.horizontalCenter: parent.horizontalCenter
        Repeater {
            id: modelDelegate
            model: JSON.parse(client.showVideoCategory())

            Row {
                anchors.top: parent.top
                anchors.topMargin: 20
                property var checks:false
                property var name:modelData.name
                CheckBox {
                    id: box
                    anchors.top: txt.top
                    anchors.topMargin: 3
                    property var myname:parent.name
                    enabled: types === name ? true : false
                    visible: types === name ? true : false
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
                    checked: parent.checks
                    onClicked: {
                        parent.checks = checked
                        if(checked === true){
                            selectAll(modelData.name)
                        }
                        else if(checked === false && flag === true){
                            cancelSelect(modelData.name)
                        }
                    }
                    Connections {
                        target: videoChoice
                        onSendcategorycheck: {
//                            console.log(box.myname)
                            if(value === "check" && box.myname === category){
                                box.checked = true
                                box.parent.checks = box.checked
                            }else if(value === "uncheck" && box.myname === category){
                                box.checked = false
                                box.parent.checks = box.checked
                            }
                        }
                    }
                }
                Text {
                    id: txt
                    text: "「"+modelData.name+"」"
                    font.pixelSize: 16
                    opacity: 0.7
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        enabled: true
                        onEntered: {
                            parent.opacity = 1
                        }
                        onExited: {
                            parent.opacity = 0.7
                        }
                        onClicked: {
                            types = modelData.name
                            videoChoice.menus =
                                    JSON.parse(client.showDetailCategory(videoTypeMenu.types))
                            videoChoice.detail = videoChoice.menus[0].name
                            videoChoice.modelDelegate.model =
                                    JSON.parse(client.showVideos(videoTypeMenu.types,
                                                                 videoChoice.detail))
                            videoChoice.videodetail.visible = false
                        }
                    }
                }
            }
        }
    }

    Connections {
        target: videoChoice
        onCategorystate: {
            messageback()
        }
    }

    function messageback(){
        var typename = " "
        for(var i = 0; i !== modelDelegate.model.length; i++){
            if(modelDelegate.itemAt(i).checks === true)
                typename = modelDelegate.itemAt(i).name
        }
        sendBack(typename)
    }
}
