import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Rectangle {
    id:recommendPage
    width: parent.width
    height: parent.height

    property var recommendResource
    property var message: ""
    property var type
    property bool flage: false
    ScrollView{
        id:scroll
        anchors.fill: parent
        clip: true

        ColumnLayout{
            width: parent.width
            height: parent.height

            Rectangle{
                width: parent.width
                height: 15
            }
            ColumnLayout{
                spacing: 25
                height: recommendPage.height
                width: recommendPage.width
                Component {
                    id: contactDelegate
                    Rectangle {
                        id:f
                        width: gridView.cellWidth
                        height: gridView.cellHeight
                        color: "red"
                        property bool tvChecked: false
                        property var name:modelData.name
                        Rectangle{
                            id: postRectangle
                            border.color: "green"
                            width: gridView.cellWidth - 10
                            height: gridView.cellHeight - 40
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter

                            Rectangle{
                                id: postImage
                                color: "yellow"
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
                            CheckBox{
                                id:check
                                checked: f.tvChecked
                                width: 30
                                height: 30
                                anchors.left: postName.right
                                anchors.bottom: parent.bottom
                                onClicked: {
                                    flage = true
                                    f.tvChecked = !f.tvChecked

//                                    if(check.checked === true){
//                                        tvName = postName.text
//                                    }
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
                    cellHeight: parent.width / 5+150
                    model: recommendResource.resource.films
                    delegate: contactDelegate
                    focus: true
                }

            }
        }
    }

        Rectangle{
            id:deleteRec
            width: parent.width
            height: 40//parent.height * 1 / 2
//            anchors.top: scroll.bottom
            anchors.top: parent.top
            anchors.topMargin: 20
            visible:flage ? true:false
            Button{
                id:delectBut
                text: "删除"
                anchors.centerIn: parent
                onClicked: {
                    dd.open()
//                    console.log(tvName)
                    commit()

                    console.log(message)
                    client.deleteMovie(message,type)
                    typeResource(type)
                }
            }
        }

        function commit() {
            message = ""

            for(var i = 0;i !== gridView.model.length;i++){
                console.log(i+" "+gridView.itemAtIndex(i).name+" "+gridView.itemAtIndex(i).tvChecked)
                if(gridView.itemAtIndex(i).tvChecked === true){
                    console.log(gridView.itemAtIndex(i).name)
                    message += gridView.itemAtIndex(i).name
                    message += "/"
                    console.log(message)
//                    break
                }else{
//                    console.log(i+" "+gridView.itemAtIndex(i).name+" "+gridView.itemAtIndex(i).tvChecked)
                }
            }

        }
        function typeResource(type){
            if("电影"===type){
                recommendResource = JSON.parse(client.showRecommend("电影"))
            }else if("剧集"===type){
                  recommendResource = JSON.parse(client.showRecommend("剧集"))
            }else if("动漫"===type){
                  recommendResource = JSON.parse(client.showRecommend("动漫"))
            }else if("综艺"===type){
                  recommendResource = JSON.parse(client.showRecommend("综艺"))
            }
        }

        PopupDialog
        {
            id:dd
        }

}

