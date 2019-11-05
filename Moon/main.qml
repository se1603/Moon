import QtQuick 2.13
import QtQuick.Window 2.13
import Moon 1.0

Window {
    visible: true
    color: "#F5F5F5"
    minimumHeight: 670
    minimumWidth: 1075
    title: qsTr("Moon")

    flags: fullScreenFlag ? Qt.Window : Qt.FramelessWindowHint

    property bool fullScreenFlag: true

    Client{
        id: client
    }

    MainItem{
        id:mainItem
    }
}
