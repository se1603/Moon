
import QtQuick 2.0
import QtQuick.Controls 2.2
//import "./RecommendPage.qml"

Rectangle {
    id: middleMenu
    width: 75 //1 / 14 * parent.width
    height: parent.height

    border.color: "grey"
    property var pageString

    property var typeName
    Rectangle{
        id: topMenu
        width: parent.width
        height: parent.height * 1 / 2
        anchors.top: parent.top
        //        color: "red"

        ListView{
            id: categoryView
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            model: JSON.parse(client.showCategory("HomePage"))
            delegate: categoryDelegate
        }

        Component{
            id: categoryDelegate
            Rectangle{
                width: middleMenu.width - 10
                height : 67
                //            color: "red"
                anchors.left: parent.left
                Text {
                    id: menuText
                    text:modelData.category
                    opacity: 0.5
                    font.pixelSize: 16
                    anchors.horizontalCenter: parent.horizontalCenter
                    MouseArea {
                        anchors.fill: parent
                        acceptedButtons: Qt.RightButton | Qt.LeftButton
                        hoverEnabled: true
                        enabled: true

                        onEntered: {
                            parent.opacity = 1
                        }
                        onExited: {
                            parent.opacity = 0.5
                        }
                        onClicked: {
                            loadPage(parent.text)
                            typeName = parent.text
                        }
                    }
                }
            }
        }
    }


    function loadPage(page)
    {
        if(page === "电影")
        {
            browseLoader.sourceComponent = filmComponent
        }
        else if(page === "动漫")
        {
            browseLoader.sourceComponent = comicComponent
        }
        else if(page === "剧集")
        {
            browseLoader.sourceComponent = dramaComponent
        }
        else if(page === "综艺")
        {
            browseLoader.sourceComponent = varietyshowComponent
        }
    }

}
