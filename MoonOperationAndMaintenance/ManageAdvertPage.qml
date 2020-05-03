import QtQuick 2.0
import QtQuick.Controls 2.12
import "Advert"

Item {
    width: parent.width
    height: parent.height

    Loader {
        id: advertLoader
        source: "../Advert/AdvertisingMaintenance.qml"
        property var pagewidth: mainWindow.width
        property var pageheight: mainWindow.height
    }
}
