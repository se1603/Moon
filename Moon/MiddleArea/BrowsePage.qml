import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    id:browsePage
    width: parent.width
    height: parent.height

    property alias recommendInterface: recommendPage

    MiddleMenu{
        id: middleCatgegory
    }

    Rectangle{
        width: parent.width - 75
        height: parent.height

        anchors.right: parent.right
        color: "yellow"

        RecommendPage{
            id: recommendPage
            recommendResource: JSON.parse(client.showRecommend("精选"))
        }
    }
}
