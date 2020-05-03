import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Rectangle {
    id:typePage
    width: parent.width
    height: parent.height

    property var showResource: browsePage.showTypeResource
    property alias typeModel: typeMenuRepeater.model

    property var date: new Date()

    ScrollView{
        anchors.fill: parent
        clip: true

        ColumnLayout{
            width: parent.width
            height: parent.height

            Rectangle{
                id: topMenu
                height: 30
                width: 1000
                Row{
                    id: typeMenu
                    spacing: 50
                    Repeater{
                        id: typeMenuRepeater
                        model: 5
                        delegate: typeMenuDelegate
                    }
                }
            }

            GridLayout {
                id: gridLayout
                anchors.top: topMenu.bottom
                anchors.topMargin: 15
                anchors.left: parent.left
                columns: 4
                columnSpacing: 25
                rowSpacing: 15
                Repeater {
                    model: showResource
                    Rectangle {
                        id:image
                        width: 220
                        height: 330
                        //                            border.color: "red"
                        Image {
                            id: postImage
                            anchors.fill: parent
                            anchors.top: parent.top
                            source:"file:" + modelData.post
                        }
                        Rectangle {
                            id: filmname
                            width: parent.width
                            height: 30
                            anchors.bottom: parent.bottom
                            //                                border.color : "green"
                        }
                        Text {
                            id: postName
                            width: parent.width
                            text: modelData.name
                            font.pixelSize: 15
                            wrapMode: Text.Wrap
                            anchors.top: filmname.top
                        }

                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                //开始记录
                                var d = new Date()
                                var year = d.getFullYear()
                                var month = d.getMonth()+1
                                var day = d.getDate()
                                var hours = d.getHours()
                                var minutes = d.getMinutes()
                                var starttime =
                                        year+"-"+month+"-"+day+"-"
                                        +hours+":"+minutes
                                if(middleArea.startTime === ""){
                                    middleArea.startTime = starttime
                                }else{
                                    middleArea.lastStartTime =
                                            middleArea.startTime
                                    middleArea.startTime = starttime
                                }


                                middleArea.nextName = postName.text
                                middleArea.stopPlay(playName,nextName)

                                playName = postName.text
                                playPost = postImage.source
                                playUrl = modelData.rtspURL

                                middleArea.middleLoader.visible = false
                                middleArea.playLoader.visible = true
                                adverts = JSON.parse(client.advertInfo(playName))
                                if(adverts !== null)
                                {
                                    middleArea.loadAdvert()
                                }
                                else
                                {
                                    console.log(playUrl)
                                    middleArea.startPlay()
                                }
                            }
                        }
                    }
                }

            }
        }
    }

    Component{
        id: typeMenuDelegate
        Rectangle{
            width: 50
            height : 40
            //            color: "red"
            Text {
                id:category
                text: modelData.category
                opacity: 0.5
                font.pixelSize: 17
                color: 	"#808080"
                anchors.horizontalCenter: parent.horizontalCenter
                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.RightButton | Qt.LeftButton
                    hoverEnabled: true
                    enabled: true

                    onEntered: {
                        parent.color = "#00BFFF"
                    }
                    onExited: {
                        parent.color = "#808080"
                    }
                    onClicked: {
                        if(parent.text == "推荐")
                        {
                            middleCatgegory.loadPage(middleCatgegory.pageString)
                        }
                        else
                        {
                            browsePage.showTypeResource =
                                    JSON.parse(client.showType(middleCatgegory.pageString,parent.text))
                            browseLoader.sourceComponent = typeComponent
                        }
                    }
                }
            }
        }
    }
}

