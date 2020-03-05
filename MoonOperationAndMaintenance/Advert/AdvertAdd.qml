/* Author:董梦丹
* Date:2020-02-20
* Note:广告
*/
import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    width: parent.width
    height: parent.height

    property alias advertLoader:advertLoader

    AdvertChoice {
        id: advertChoice
        anchors.right: parent.right
    }

    Loader {
        id: advertLoader
        source: "VideoPage.qml"
        property var currentName:""
        property var currentPost:""
        property var currentType:""
    }

    AdvertDir {
        id: advertDir
    }
}
