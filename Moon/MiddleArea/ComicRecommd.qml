//time：2019.5.6
//内容：动漫推荐界面填充post
//Autor：徐丹
import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    id:comic_recommend
    width: page_display.width
    height: page_display.height


    ScrollView{
        anchors.fill: parent
        clip: true
        ColumnLayout{
            width: parent.width
            height: parent.height

            Row{
                id: row_comic_menu
                anchors.left:parent.left
                spacing: 50
                Repeater {
                    model:7//请求目录JSON.parse(client.showCategory(3))
                    delegate: category_comic_dele
                }
            }
            RecommdModel{
                width: page_display.width//parent.width
                height: page_display.width>1200?4600:3200
//                anchors.fill: parent
//                color: "red"
                anchors.top: row_comic_menu.bottom
            }

        }
    }

    Component{
        id:category_comic_dele
        Rectangle {
            width: 50
            height : 40
            Text {
                id:category
                text: modelData//modelData.category
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


                        console.log("recommend"+category.text)
                        load_comic_page(category.text)
                    }
                }
            }
        }
    }


    function load_comic_page(page){
        switch(page){
        case "1":
            comic_stack.push(comicRecommend_page,StackView.Immediate)
            break
        default:
            comic_stack.push(comictype_page,StackView.Immediate)
            break
        }
    }
}


