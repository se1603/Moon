/* Author:徐丹
* Date:2020-03-17
* Note:搜索界面
*/
import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle {
    width: parent.width
    height: parent.height

    property var nameq
    property var post
    property var intro
    property var types
    property var esd
    property var catagory
    property var region
    Row {
        id: row
        anchors.top: parent.top
        anchors.topMargin: 1 / 2 * spacing
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 1 / 20 * parent.width
        Text {
            text: "搜索名称："
            font.pixelSize: 16
            anchors.verticalCenter: parent.verticalCenter
        }

        TextField {
            id: txtInput
        }

        Image {
            id: searchbutton
            source: "qrc:/image/advert/search.png"
            anchors.verticalCenter: parent.verticalCenter
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(txtInput.text !== ""){
                        var ta
                        ta = JSON.parse(client.search(txtInput.text))
                        post = ta.resource.post
                        nameq = ta.name
                        types = ta.resource.videotype
                        intro = ta.resource.introduction
                        esd = ta.resource.esipode
                        console.log(post+intro)
                        var d = ta.resource.category
                        for(var i in types){
//                            rec.check = true
                            console.log(types[i].type)
                            listM.append({"type":types[i].type})
                            date.type += types[i].type
                        }
                        if(d==="1"){
                            catagory="电影"
                        }else if(d==="2"){
                            catagory="剧集"
                        }else if(d==="3"){
                            catagory="动漫"
                        }else if(d==="4"){
                            catagory="综艺"
                        }
                        date.typeMo = catagory
                        date.name = nameq
                        date.post ="file:"+ post
                        date.infoma =intro
                        date.esd = esd
                        date.region = ta.resource.region
                        region = ta.resource.region
                        console.log(catagory)
                    }
                }
            }
        }
    }

    ListModel{
        id:listM
    }

    UpdateDialog{
        id:date
    }

    Rectangle {
        id: search
        width: parent.width
        height: parent.height - row.height
        anchors.top: row.bottom
        anchors.left: parent.left
        anchors.leftMargin: 130
        ScrollView {
            anchors.fill: parent
            clip: true
            GridLayout {
                anchors.top: parent.top
                anchors.topMargin: 1 / 4 * row.height
                columns: mainWindow.width < 1100 ? 4 : 5
                columnSpacing: 1 / 2 * row.height
                rowSpacing: 1 / 2 * row.height

                Repeater {
                    id: modelDelegate
                    model: 1
                    Rectangle {
                        id:rec
                        width: parent.width
                        height: parent.height
                        property var name:nameq
                        property var source:post
                        property bool check:false
                        Rectangle{
                            id:postRec
                            width: 200
                            height: 350
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.leftMargin: 20
//                            border.color: "red"
                            Image {
                                id: videoPost
                                width: parent.width
                                height: 5 / 6 * parent.height
                                source: "file:" + rec.source
                            }
                        }
                        Text{
                            id:name
                            anchors.left: postRec.right
                            anchors.leftMargin: 20
                            anchors.top: parent.top
                            text: rec.name
                            font.pixelSize: 16
                        }
                        Row{
                            id:typeRow
                            anchors.left: postRec.right
                            anchors.leftMargin: 20
                            anchors.top: name.bottom
                            anchors.topMargin: 15
                            Repeater {
                                model: listM

                                Text {
                                    font.pixelSize: 16
                                    text: modelData
                                }
                            }
                        }

                        Text {
                            id: regi
                            anchors.left: postRec.right
                            anchors.leftMargin: 20
                            anchors.top: typeRow.bottom
                            anchors.topMargin: 10
                            text: region
                            font.pixelSize: 16
                        }
                        Rectangle{
                            id:intRec
                            anchors.left: postRec.right
                            anchors.leftMargin: 20
                            anchors.top: regi.bottom
                            anchors.topMargin: 10
                            width: 600//parent.width-200
                            height: 150
//                            border.color: "red"
                            Text {
                                width: parent.width
                                height: parent.height
                                wrapMode: TextEdit.Wrap
                                font.pixelSize: 16
                                text: intro
                            }
                        }
                        Row{
                            id:esdRow
                            anchors.top: intRec.bottom
                            anchors.topMargin: 10
                            anchors.left: postRec.right
                            anchors.leftMargin: 20
                            Repeater {
                                model: esd

                                Rectangle{
                                    width: 30
                                    height: 30
                                    color: "grey"
                                    Text {
                                        font.pixelSize: 16
                                        text: modelData+1
                                        anchors.centerIn: parent
                                    }
                                }
                            }
                        }
                        Rectangle{
                            id:recc
                            width: 100
                            height: 50
//                            color: "grey"
                            visible: nameq?true:false
                            anchors.top: postRec.bottom
                            anchors.topMargin: 140
                            anchors.left: parent.left
                            anchors.leftMargin: 20
                            Text {
                                id:updar
                                text: qsTr("「 更新 」")
                                font.pixelSize: 18
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    date.open()
//                                    date.name = nameq
                                }
                            }
                        }
                        Rectangle{
                            width: 100
                            height: 50
//                            color: "grey"
                            visible: nameq?true:false
                            anchors.top: postRec.bottom
                            anchors.topMargin: 140
                            anchors.left: recc.right
                            anchors.leftMargin: 120
                            Text {
                                id:clean
                                text: qsTr("「 删除 」")
                                font.pixelSize: 18
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    client.deleteMovie(nameq,catagory)
                                }
                            }
                        }
                    }
                }
            }
        }
    }

//    DeleteDialog{
//        id:dele
//    }

    Connections{
        target: client
        onDelectSucceed:{
//            dele.open()
        }
        onSeachEmpty:{
            messageDialog.open()
        }
    }

    Dialog {
        id: messageDialog
        width:200 //1 / 2 * deleteDialog.width
        height: 200//1 / 2 * deleteDialog.height
        visible: false
        anchors.centerIn: parent

        Column {
            spacing: 1 / 6 * parent.width
            anchors.centerIn: parent

            Text {
                text: "暂无此影视资源！"
            }

            Button {
                text: "Close"
                onClicked: {
                    messageDialog.close()
                }
            }
        }
    }
}
