/* Author:徐丹
* Date:2020-02-25
* Note:下架界面
*/
import QtQuick 2.0

Item {
    property var showTypeResource
    property var typeString

    UnderMenu{
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
            sourceComponent: filmComponent//mainRecommend
        }
    }

    Component{
        id: filmComponent
        UnderType{
            recommendResource: JSON.parse(client.showRecommend("电影"))
            type: "电影"
//            typeModel: typeString
//            showTypeMenu: true
        }
    }

    Component{
        id: comicComponent
        UnderType{
            recommendResource: JSON.parse(client.showRecommend("动漫"))
            type: "动漫"
        }
    }

    Component{
        id: dramaComponent
        UnderType{
            recommendResource: JSON.parse(client.showRecommend("剧集"))
            type: "剧集"

        }
    }

    Component{
        id: varietyshowComponent
        UnderType{
            recommendResource: JSON.parse(client.showRecommend("综艺"))
            type: "综艺"

        }
    }
}
