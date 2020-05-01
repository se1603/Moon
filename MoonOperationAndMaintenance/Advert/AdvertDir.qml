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

    property string file:"file:///"
    property string folderPathName: file+"root"
    property string changePathName
    property string absolutePath: "/root"
    property string advertname:""

    property alias folder:folderModel.folder


    Rectangle {
        id: folderRec
        width: parent.width
        height: parent.height

        FolderListModel
        {
            id:folderModel
            folder:folderPathName
            nameFilters: ["*.ts"]
            showDirs: true
            showFiles: true
            showDirsFirst: true
            showDotAndDotDot: true
            showOnlyReadable: false
        }

        Component {
            id: fileDelegate
            Text {
                text: folderModel.isFolder(index) === true ? "目录： " + fileName
                                                           : "文件： " + fileName
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
                            folderPathName =  changePathName + "/" + fileName
                            absolutePath += "/"
                            absolutePath += fileName
                            folderModel.folder = folderPathName
                        }else{
                            root.absolutePath += "/"+fileName
                            root.advertname = fileName
                            advertChoice.advertName = root.advertname
                            advertChoice.path = root.absolutePath
                            advertDir.close()
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
        anchors.bottomMargin: 1 / 10 * parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 1 / 20 * parent.height
        model: folderModel
        delegate: fileDelegate
        clip: true
    }

    Image {
        width: 50
        height: 50
        source: "../image/advert/left.png"
        anchors.top: parent.top
        anchors.right: parent.right
        MouseArea {
            anchors.fill: parent
            onClicked: {
                advertDir.close()
            }
        }
    }

//    Rectangle {
//        id: chooseRec
//        width: parent.width
//        height: 1 / 4 * parent.height
//        anchors.top: folderRec.bottom

//        Text {
//            id: choose_title
//            text: "请选择要插入的广告:"
//            font.pixelSize: 14
//            anchors.top: parent.top
//            anchors.topMargin: 1 / 10 * parent.height
//            anchors.horizontalCenter: parent.horizontalCenter
//        }

//        Row {
//            spacing: chooseRec.height
//            anchors.top: choose_title.bottom
//            anchors.topMargin: 1 / 5 * parent.height
//            anchors.horizontalCenter: parent.horizontalCenter

//            Text {
//                text: "确认"
//                font.pixelSize: 14
//                opacity: 0.5

//                MouseArea {
//                    anchors.fill: parent
//                    hoverEnabled: true
//                    enabled: true
//                    onEntered: {
//                        parent.opacity = 1
//                    }
//                    onExited: {
//                        parent.opacity = 0.5
//                    }
//                    onClicked: {
//                        if(updateFileSource === ""){
//                            choose_title.text = "没有选择文件！"
//                        }else{
//                            advertChoice.advertName = root.advertname
//                            advertChoice.path = root.absolutePath
//                            root.close()
//                        }
//                        advertDir.folderPathName = "file:///root"
//                        advertDir.choose_title = "确定插入' '这个广告吗？"
//                    }
//                }
//            }

//            Text {
//                text: "关闭"
//                font.pixelSize: 14
//                opacity: 0.5

//                MouseArea {
//                    anchors.fill: parent
//                    hoverEnabled: true
//                    enabled: true
//                    onEntered: {
//                        parent.opacity = 1
//                    }
//                    onExited: {
//                        parent.opacity = 0.5
//                    }
//                    onClicked: {
//                        choose_title.text = "请选择要插入的广告:"
//                        advertDir.close()
//                    }
//                }
//            }
//        }
//    }
}
