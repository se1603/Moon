/* Author:董梦丹
* Date:2020-02-10
* Note:广告
*/
import QtQuick 2.0
import QtQuick.Controls 2.2
import Qt.labs.folderlistmodel 2.2

Popup {
    id: root
    width: 1 / 2 * mainWindow.height
    height: 1 / 2 * mainWindow.height

    x: 1 / 5 * mainWindow.width
    y: 1 / 4 * mainWindow.height

    property string folderPathName: "file:///root"
    property string changePathName
    property string updateFileSource
    property string filename: ""

    Rectangle {
        id: folderRec
        width: parent.width
        height: 3 / 4 * parent.height

        FolderListModel
        {
            id:folderModel
            folder:folderPathName
            showDirs: true
            showFiles: true
            showDirsFirst: true
            showDotAndDotDot: true
            showOnlyReadable: false
//            sortField: FolderListMode.Type
        }

        Component {
            id: fileDelegate
            Text {
                text: fileName
                width: storageList.width
                wrapMode: Text.WordWrap
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        parent.opacity = 0.7
                    }
                    onExited: {
                        parent.opacity = 1
                    }
                    onClicked: {
                        if(folderModel.isFolder(index) === true){
                            changePathName = folderPathName
                            folderPathName =  changePathName + "/" + parent.text
                            folderModel.folder = folderPathName
                        }else{
                            updateFileSource = parent.text
                            choose_title.text = "确定插入'"+fileName+"'这个广告吗？"
                            root.filename = fileName
                        }
                    }
                }
            }
        }
    }

    ListView {
        id: storageList
        width: 3 / 4 * parent.width
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 1 / 3 * parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 1 / 30 * parent.height
        model: folderModel
        delegate: fileDelegate
        clip: true
    }

    Rectangle {
        id: chooseRec
        width: parent.width
        height: 1 / 4 * parent.height
        anchors.top: folderRec.bottom

        Text {
            id: choose_title
            text: "请选择要插入的广告:"
            font.pixelSize: 14
            anchors.top: parent.top
            anchors.topMargin: 1 / 10 * parent.height
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Row {
            spacing: chooseRec.height
            anchors.top: choose_title.bottom
            anchors.topMargin: 1 / 5 * parent.height
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                text: "确认"
                font.pixelSize: 14
                opacity: 0.5

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    enabled: true
                    onEntered: {
                        parent.opacity = 1
                    }
                    onExited: {
                        parent.opacity = 0.5
                    }
                    onClicked: {
                        if(updateFileSource === ""){
                            choose_title.text = "没有选择文件！"
                        }else{
                            advertChoice.advertName = root.filename
                            root.close()
                        }
                    }
                }
            }

            Text {
                text: "关闭"
                font.pixelSize: 14
                opacity: 0.5

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    enabled: true
                    onEntered: {
                        parent.opacity = 1
                    }
                    onExited: {
                        parent.opacity = 0.5
                    }
                    onClicked: {
                        choose_title.text = "请选择要插入的广告:"
                        updateFileSource = ""
                        advertDir.close()
                    }
                }
            }
        }
    }
}
