import QtQuick 2.12
import QtQuick.Window 2.12
import Moon 1.0

Window {
    id: mainWindow
    visible: true
    width: 1075
    height: 716
    title: qsTr("MoonOperationAndMaintenance")

    Client{
        id: client
    }

    MainItem{
        id: mainItem
    }
}
