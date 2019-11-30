import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    id:browsePage
    width: parent.width
    height: parent.height

    property var showTypeResource
    property var typeString

    MiddleMenu{
        id: middleCatgegory
    }

    Rectangle{
        width: parent.width - 75
        height: parent.height

        anchors.right: parent.right
        color: "yellow"

        Loader{
            id: browseLoader
            anchors.fill: parent
            sourceComponent: mainRecommend
        }
    }

    Component{
        id: mainRecommend
        RecommendPage{
            recommendResource: JSON.parse(client.showRecommend("精选"))
            showTypeMenu: false
        }
    }

    Component{
        id: filmComponent
        RecommendPage{
            recommendResource: JSON.parse(client.showRecommend("电影"))
            typeModel: typeString
            showTypeMenu: true
        }
    }

    Component{
        id: comicComponent
        RecommendPage{
            recommendResource: JSON.parse(client.showRecommend("动漫"))
            typeModel: typeString
            showTypeMenu: true
        }
    }

    Component{
        id: dramaComponent
        RecommendPage{
            recommendResource: JSON.parse(client.showRecommend("剧集"))
            typeModel: typeString
            showTypeMenu: true
        }
    }

    Component{
        id: varietyshowComponent
        RecommendPage{
            recommendResource: JSON.parse(client.showRecommend("综艺"))
            typeModel: typeString
            showTypeMenu: true
        }
    }
    Component{
        id: typeComponent
        TypePage{
            typeModel: typeString
        }
    }
}
