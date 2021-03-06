import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Rectangle {
    id:recommendPage
    width: parent.width
    height: parent.height
    property alias showTypeMenu: topMenu.visible
    property alias typeModel: typeMenuRepeater.model

    property var recommendResource

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

            //大海报推荐
            Row{
                id: recommendLayout
                Rectangle{
                    id:recommendPost
                    height: recommendPage.width / 3.5
                    width: recommendPage.width
//                    color: "red"
                    Image {
                        id: post_Image
                        anchors.fill: parent
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            console.log(post_Image)

                        }
                    }

                    Rectangle{
                        id: recommendName   //大海报影视名称
                        height: 40
                        width: parent.width
                        anchors.bottom: parent.bottom
                        opacity: 0.8
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                console.log(recommendName.width)

                            }
                        }

                        ListView{
                            id: recommendNameView
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.right: parent.right
                            orientation: ListView.Horizontal
                            model:recommendResource.firstRecommends
                            delegate: recommendNameDelegate
                        }
                    }
                }
            }
            Rectangle{
                width: parent.width
                height: 15
            }

            //分类推荐 小海报
            ColumnLayout{
                spacing: 25

                Repeater{
                    id: classifiedRecommend
                    model: recommendResource.secondRecommends.resource
                    Rectangle{
                        width: recommendPage.width
                        height: 400
//                        color: "yellow"

                        Rectangle{
                            id: title
                            width: parent.width
                            height: 40
//                            color: "blue"
                            Text{
                                id: recommendTile
                                text: modelData.title
                                font.pixelSize: 24
                            }
                        }

                        Rectangle{
                            width: parent.width
                            height: parent.height - title.height
                            anchors.bottom: parent.bottom
                            color: "red"

                            Component {
                                id: contactDelegate
                                Rectangle {
                                    width: gridView.cellWidth
                                    height: gridView.cellHeight
//                                    color: "red"

                                    Rectangle{
                                        id: postRectangle
//                                        border.color: "green"
                                        width: gridView.cellWidth - 10
                                        height: gridView.cellHeight - 40
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        anchors.verticalCenter: parent.verticalCenter
                                        Rectangle{
                                            id: postImage
//                                            color: "yellow"
                                            width: parent.width
                                            height: parent.height - 30
                                            anchors.top: parent.top
                                            Image {
                                                id:postimage
                                                anchors.fill: parent
                                                source: "file:" + modelData.post
                                            }
                                        }

                                        Text {
                                            id:postName
                                            text: modelData.name//名字
                                            font.pixelSize: 15
                                            wrapMode: Text.Wrap
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            anchors.bottom: parent.bottom
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
                                                playPost = postimage.source
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

                            GridView {
                                id: gridView
                                anchors.fill: parent
                                anchors.left: parent.left
                                cellWidth: parent.width / 5
                                cellHeight: parent.height
                                model: modelData.films
                                delegate: contactDelegate
                                focus: true
                            }
                        }
                    }
                }
            }
        }
    }

    //分类菜单
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
                font.pixelSize: 15
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

    //大海报切换计时器
    Timer {
        id:time
        interval: 3000
        running: true
        repeat: true
        onTriggered:{
            if(recommendNameView.currentIndex ===  4)
            {
                recommendNameView.currentIndex -= 4

            }else{
                recommendNameView.currentIndex += 1
            }
        }
    }

    //大海报动画
    Component{
        id: recommendNameDelegate
        Rectangle{
            id: nameSlide
            height: 40
            width: recommendLayout.width / 5
            color:ListView.isCurrentItem ? "lightblue" : "white"
            onColorChanged: {
                post_Image.source = "file:" + modelData.post
            }
            Text {
                id: movisAndeTelevisionName
                text: modelData.name
                anchors.centerIn: parent
                color: "black"
            }

            MouseArea {
                id:mousearea1
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                hoverEnabled: true
                propagateComposedEvents: true
                enabled: true
                anchors.fill: parent

                onClicked: {
                    console.log(parent.width)
                }

                onEntered: {
                    //鼠标覆盖，显示对应的图片
                    if(nameSlide.ListView.view.currentIndex !== index){
                        nameSlide.ListView.view.currentIndex = index;
                    }
                    time.stop()
                }
                onExited: {
                    time.start()
                }
            }
        }
    }

}

