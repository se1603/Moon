import QtQuick 2.0
import QtQuick.Controls 2.12
import "Advert"

Item {
    anchors.fill: parent

    property alias advertAdd:advertAdd
    property alias advertCalculation:advertCalculation
    property alias advertStack:advertStack
    property alias advertMiddle:advertMiddle


    AdvertMenu {
        id: advertMenu
    }

    Rectangle {
        id: advertMiddle
        width: parent.width - advertMenu.width
        height: parent.height
        anchors.left: advertMenu.right
        anchors.top: parent.top

        StackView {
            id: advertStack
            anchors {
                top: parent.top
                bottom: parent.bottom
                fill: parent
            }

            initialItem: advertAdd
        }
    }

    Component {
        id: advertAdd
        AdvertAdd {
        }
    }

    Component {
        id: advertCalculation
        AdvertCalculation {
        }
    }
}
