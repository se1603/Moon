import QtQuick 2.0
import QtQuick.Controls 2.2
import Qt.labs.folderlistmodel 2.2
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2
Popup {
    id: root
    width: 500 //1 / 3 * mainWindow.width
    height: 500//1 / 2 * mainWindow.height

    x:100// 1 / 2 * (mainWindow.width - root.width)
    y: 100//1 / 5 * mainWindow.height


    property string changePathName
    property string updateFileSource
    property alias adress: fds.fileUrl
    property string imagename
    Rectangle {
        id: folderRec
        width: parent.width
        height: 3 / 4 * parent.height

        FolderListModel
        {
            id:folderModel
            folder:"qrc:///image/avatar"
            showDirs: true
            showFiles: true
            showDirsFirst: true
            showDotAndDotDot: false
            nameFilters: ["*.jpg","*.png","*.jpeg"]
            showOnlyReadable: true
            sortField: FolderListModel.Type
        }

        Component {
            id: fileDelegate

            Rectangle {
                width:grid.cellWidth-10//1 / 3 * folderRec.width
                height: grid.cellHeight-20//1 / 3 * folderRec.width
                Image {
                    width: parent.width
                    height: parent.height
                    source: "../image/avatar/"+fileName
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
                                updateFileSource = parent.source
                                imagename = fileName
                                choose_title.text = "确定保存 "+fileName+" 吗？"
                                console.log(updateFileSource)
                            }
                        }
                    }
                }
            }
        }
    }

    GridView {
        id:grid
        width: parent.width
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 1 / 6 * parent.height
//        spacing: 10
        cellHeight: 160
        cellWidth: 140
        model: folderModel
        delegate: fileDelegate
        clip: true
    }


    Rectangle {
        id: chooseRec
        width: parent.width
        height: 1 / 4 * parent.height
        anchors.top: folderRec.bottom
        border.color: "gray"

        Column {
            spacing: 1 / 6 * parent.height
            anchors.centerIn: parent

            Text {
                id: choose_title
                text:"请选择要保存的图片："
                font.pixelSize: 12
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Row {
                spacing: 1 / 3 * chooseRec.height
                Button {
                    text:"保存"
                    onClicked: {
                        if(updateFileSource === ""){
                            choose_title.text = "没有选择图片！"
                        }else{
                            listModel.set(index1,{"source":imgPup.updateFileSource
                                           })
                            console.log(index1+"insert"+imgPup.updateFileSource)
                             imgPup.close()
                            fds.open()
//                            client.updateAvatar(updateFileSource,audienceInterface.audienceName)
                        }
                    }
                }
                Button {
                    text:"取消"
                    onClicked: {
                        choose_title.text = "请选择要保存的图片："
                        updateFileSource = ""
                        imgPup.close()
                    }
                }
            }
        }
    }
    Label {
        id: labels
        text: qsTr("")
        height: 25
//        anchors.left:openBtn.right
        anchors.leftMargin: 10
    }


    FileDialog {
        id:fds
        title: "选择文件"
        folder: shortcuts.desktop
        selectExisting: false//true
        selectFolder: true//false
        selectMultiple: false
        nameFilters: ["Image files (*.jpg*.png*.svg)", "All files (*)" ]
//        fileMode: FileDialog.SaveFile
        onAccepted: {
            labels.text = fds.fileUrl;
            console.log("You chose: " + fds.fileUrl);
        }

        onRejected: {
            labels.text = "";
            console.log("Canceled");
            Qt.quit();
        }

    }
}
