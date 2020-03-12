/* Author:董梦丹
* Date:2020-02-19
* Note:广告
*/
import QtQuick 2.0

Rectangle {
    width: 4 / 5 * advertMiddle.width
    height: advertMiddle.height

    VideoTypeMenu {
        id: videoTypeMenu
        anchors.horizontalCenter: parent.horizontalCenter
    }

    VideoChoice {
        id: videoChoice
        anchors.top: videoTypeMenu.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
