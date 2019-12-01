import QtQuick 2.0
import "../Audience"
import "../PlayArea"
Rectangle {
    width: parent.width
    height: parent.height - 38//17/18 * parent.height
    anchors.bottom: parent.bottom
    color: "green"
    //用户页
    property alias audienceInterface:audienceInterface

    BrowsePage{

    }
    //用户主页
    AudienceInterface {
        id: audienceInterface
        visible: false
    }

    Play{
        id:play
        visible: false
    }
}
