import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    id:browsePage
    width: parent.width
    height: parent.height

    property alias browseInterface: recommendPage
    //    property alias loader: browseLoader

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
            source: recommendPage
        }

//        QtObject{
//            id: internalSettings
////            property  recommendResource: JSON.parse(client.showRecommend("精选"))
//            property  name: value
//        }


//        Component{
//            id: recommendComponent
            RecommendPage{
                id: recommendPage
                recommendResource: /*internalSettings*/JSON.parse(client.showRecommend("精选"))
            }
//        }

        //        Component{
        //            id: recommendComponent
        //            RecommendPage{
        //                id: recommendPage
        //                recommendResource: JSON.parse(client.showRecommend("精选"))
        //            }
        //        }

        //        StackView{
        //            id: browseStack
        //            anchors.fill: parent
        //            initialItem: recommendPage
        //        }


    }
}
