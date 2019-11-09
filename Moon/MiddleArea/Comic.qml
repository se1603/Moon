import QtQuick 2.0

Rectangle {

    width: parent.width
    height: parent.height
//    color: "red"
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
    Rectangle{
        anchors.top: parent.top
        width: parent.width
        //        color: "black"
        height: 40
        opacity: 1
        Row{
            id: row_menu1
            anchors.left:parent.left
            spacing: 50
            Repeater {
                model:7//JSON.parse(client.showCategory(3))
                delegate: comicDelegate
            }
        }
        z:3
    }

    Component{
        id:comicDelegate
        Rectangle {
            width: 50
            height : 40
            Text {
                id:category
                text: modelData
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
                        console.log(category.text)
                        load_comic_page(category.text)
                    }
                }
            }
        }
    }

    MovieModel{
    }
}
