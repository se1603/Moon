import QtQuick 2.0
import "../Audience"
import "../PlayArea"
Rectangle {
    width: parent.width
    height: parent.height - 38//17/18 * parent.height
    anchors.bottom: parent.bottom
    color: "green"

    property alias audienceInterface: audienceInterface

    property alias middleLoader: loader
    property alias browsePage: browseComponent
    property alias playPage: playComponent

    property string playPost
    property string playName

    Loader{
        id: loader
        anchors.fill: parent
        sourceComponent: browseComponent
    }

    Component{
        id: browseComponent
        BrowsePage{

        }
    }

    //用户主页
    AudienceInterface {
        id: audienceInterface
        visible: false
    }
    Component{
        id: playComponent
        Play{
            //            id:play
            //            visible: false
        }
    }

}
