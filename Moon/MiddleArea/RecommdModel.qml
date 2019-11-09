import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
Rectangle {

    width: parent.width
//    height: parent.height
    height: page_display.width>1200?3600:2600
//    color: "red"
    Row{
        id:row_image_comic
        Rectangle{
            id:slide_comic_image
            width: comic_recommend.width
            height: page_display.width < 1200 ? 342 : 442
            color: "red"
            Image {
                id: film_comic_image
                anchors.fill: parent
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {

                }
            }
        }
    }

    ListView{
        id: slide_comic
        width:  page_display.width < 1200 ? 1000 : 1200
        height: 40
        opacity: 0.8
        anchors.top: row_image_comic.top
        anchors.left: row_image_comic.left
        anchors.right: row_image_comic.right
        anchors.topMargin: page_display.width < 1200 ? 302 : 404
        orientation: ListView.Horizontal
        z:5
        model:5//推介图片recommendComics.firstRecommends
        delegate: show_comic_slide
    }

    ColumnLayout{
        anchors.top:row_image_comic.bottom
        anchors.topMargin: 20
        spacing: page_display.width < 1000 ? 10 : 60

        Repeater{
            id:show_comic_film
            model:6//推介内容recommendComics.secondRecommends.resource
            Rectangle{
                width: page_display.width
                height: page_display.width < 1000 ? 355 : 400
                Text {
                    id:comic_title
                    text: "标题"//
                    font.pixelSize: 24
                }

                Row {
                    id: comic_grid
                    anchors.top: comic_title.bottom
                    anchors.topMargin: 15
                    anchors.left: parent.left
//                            spacing: page_display.width < 1200 ? 15 : 50
                    Repeater {
                        model: 5//modelData.films
                        Rectangle {
                            width:  page_display.width/5// < 1200 ? 175 : 197
                            height:  page_display.width < 1000 ? 290 : 326
                            Rectangle {
                                id: collectiob_img_comic
                                width: parent.width-15
                                color:"red"
                                height:  page_display.width < 1000 ? 263 : 296
                                Image {
                                    anchors.fill: parent
                                    anchors.top: parent.top
//                                            source:"file:" + modelData.post
                                }

                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {

                                    }
                                }
                            }
                            Text {
                                id: collectiob_text_comic
                                width: parent.width
                                text: "名字"//modelData.name
                                wrapMode: Text.Wrap
                                anchors.top: collectiob_img_comic.bottom
                            }
                        }
                    }
                }
            }
        }
    }

    Timer {
        id:time_comic
        interval: 3000
        running: true
        repeat: true
        onTriggered:{
            if(slide_comic.currentIndex ===  4)
            {
                slide_comic.currentIndex -= 4

            }else{
                slide_comic.currentIndex += 1
            }
        }
    }

    Component{
        id:show_comic_slide
        Rectangle{
            id: slideRect_comic
            height: 40
            width: row_image_comic.width/5
            color:ListView.isCurrentItem ? "lightblue" : "white"
            onColorChanged: {
                film_comic_image.source = "file:" + modelData.post
            }
            Text {
                id: slideComic_name
                text: "名字"//modelData.name
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
                    if(slideRect_comic.ListView.view.currentIndex !== index){
                        slideRect_comic.ListView.view.currentIndex = index;
                    }
                    time_comic.stop()
                }
                onExited: {
                    time_comic.restart()
                }
            }
        }
    }

}
