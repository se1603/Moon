/* Author:徐丹
* Date:2020-02-12
* Note:编辑影视信息界面
*/
import QtQuick 2.0
import QtLocation 5.13
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

Rectangle {

    id:groundPage
    property int index1:0
    property var messagesName:""
    width: parent.width
    height: parent.height
    //    color: "#737373"
    Rectangle{
        id:upRtn
        width: parent.width/5
        height: 80
        z:3
        anchors.left: parent.Left
        //        border.color: "#303030"
        Text {
            id: name
            anchors.centerIn: parent
            font.pixelSize: 18
            //            font.family: "宋体"
            text: qsTr("「  上传   」")
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                client.upServer()
                up.open()
            }
            onEntered: {
                name.font.pixelSize = 20
            }
            onExited: {
                name.font.pixelSize = 18
            }
        }
    }
    Connections {
        target: client
        onFilmEmpty:{
            empt.open()
        }
    }
    EmptyDialog{
        id:empt

    }
    UpDialog{
        id:up
    }

    Component.onCompleted: {
        messages()
    }

    function messages(){
        var v = JSON.parse(client.getLocalMessages())
        var s = v["empty"]
        if(s === "EMPTY"){
            console.log(s)
        }else{
            listModel.clear()
            var json = v["resources"]
            for(var i in json){
                //            listModel.clear()
                console.log(json[i]["bigType"]+"  hh"+i)
                listModel.append({"typ": json[i]["type"], "region":json[i]["region"],"bigType":json[i]["bigType"],"introduction":json[i]["introduction"],
                                     "actor":json[i]["actor"],"dictor":json[i]["director"],"name":json[i]["name"],"episode":json[i]["episode"],"imgSource":json[i]["image"],"imagePath":json[i]["imagePath"],"recommend":json[i]["recommmd"],"about":"相关影视"
                                 })
            }
        }
    }

    ListModel {
        id:listModel
        ListElement {
            name: "XXX"
            episode: " "
            typ:"悬疑"
            region:"中国"
            bigType:"电影"
            introduction:"简介"
            actor:"演员"
            dictor:"导演"
            about:"相关影视"
            imgSource:" "
            imagePath:" "
            recommend:"否"
        }

    }
    Rectangle{
        id:listBtn
        anchors.left: parent.left
        anchors.top: upRtn.bottom
        width: parent.width/5
        height: 500//parent.height*4/5
//                color: "#E3E3E3"

        ListView {
            id:recommendNameView
            width: groundPage.width/5; height: 200

            model: listModel
            delegate: delegateView
        }


        Component{
            id:delegateView
            Rectangle{
                id: nameSlide
                height: 40
                width: recommendNameView.width
                color:ListView.isCurrentItem ? "#00FFFF" : "white"
                onColorChanged: {
                    name1.text = name
                    type1.text = typ
                    region1.text = region
                    typeMo.text = bigType
                    infoma.text = introduction
                    actorEdit.text = actor
                    dictorEdit.text = dictor
                    //                    aboutEdit.text = about
                    imgPup.updateFileSource = imgSource
                    imgPup.adress = imagePath
                    esd.text = episode
                    recc.text = recommend
                    //                    post_Image.source = "file:" + modelData.post
                }
                Text {
                    id: movisAndeTelevisionName
                    text: name
                    anchors.centerIn: parent
                    font.pixelSize: 16
                    //                    color: "black"
                }

                MouseArea {
                    id:mousearea1
                    acceptedButtons: Qt.RightButton | Qt.LeftButton
                    hoverEnabled: true
                    propagateComposedEvents: true
                    enabled: true
                    anchors.fill: parent

                    onClicked: {
                        console.log(parent.width)
                    }

                    onEntered: {
                        movisAndeTelevisionName.font.pixelSize = 18
                        //鼠标覆盖，显示对应的图片
                        if(nameSlide.ListView.view.currentIndex !== index){
                            nameSlide.ListView.view.currentIndex = index;
                        }
                    }
                    onExited: {
                        movisAndeTelevisionName.font.pixelSize = 16
                        index1 = index
                        console.log(index1)
                    }
                }
            }
        }
    }
    Rectangle{
        id:btnF
        anchors.right: parent.right
        anchors.left: listBtn.right
        anchors.leftMargin: 10
        width: parent.width*4/5-15
        height: parent.height
        //        color: "#E3E3E3"
        //        border.color: "black"
        Rectangle{
            id:add
            anchors.left: parent.left
            width: 220
            height: 320
            border.color: "lightblue"
            //            color: "lightblue"
            Text{
                text: "添加图片"
                anchors.centerIn: parent
                font.family: "Helvetica"
                font.pointSize: 18
                color: "blue"
            }
            Image {
                id: img
                source: /*imgSource//*/imgPup.updateFileSource
                width: parent.width
                height: parent.height
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    console.log(img.source+"iiii")
                    imgPup.open()
                }
            }

        }
        Text {
            id: nameLabel
            text: qsTr("名字：")
            anchors.left: add.right
            anchors.leftMargin: 20
            //            font.family: "Helvetica"
            font.pointSize: 16
            //            color: "blue"
        }
        TextField{
            id:name1
            anchors.left: nameLabel.right
            //            font.family: "Helvetica"
            font.pointSize: 16
            //            color: "blue"

        }
        Text {
            id:typeMo1
            text: "类别："
            //            font.family: "Helvetica"
            font.pointSize: 16
            focus: true
            anchors.top: name1.bottom
            anchors.topMargin: 20
            anchors.left: add.right
            anchors.leftMargin: 20
        }
        TextField {
            id:typeMo
            width: 240
            text: "<b>bigType</b>"
            font.family: "Helvetica"
            font.pointSize: 16
            //            color: "blue"
            focus: true
            anchors.top: name1.bottom
            anchors.topMargin: 20
            anchors.left: typeMo1.right
        }
        Text{
            id:type
            text: "类型:"
            anchors.top: typeMo1.bottom
            anchors.topMargin: 20
            anchors.left: add.right
            anchors.leftMargin: 20
            //            font.family: "Helvetica"
            //            color: "blue"
            font.pointSize: 16
        }
        TextField {
            id:type1
            width: 240
            text: "<b>type</b>"
            //            font.family: "Helvetica"
            font.pointSize: 16
            //            color: "blue"
            focus: true
            anchors.top: typeMo.bottom
            anchors.topMargin: 20
            anchors.left: type.right
            anchors.leftMargin: 20
        }
        Text{
            id:region
            text: "地域："
            anchors.top: type.bottom
            anchors.topMargin: 20
            anchors.left: add.right
            anchors.leftMargin: 20
            //            text: "<b>region</b>"
            //            font.family: "Helvetica"
            font.pointSize: 16
            //            color: "blue"
        }

        TextField {
            id:region1
            width: 240
            text: "<b>region</b>"
            //            font.family: "Helvetica"
            font.pointSize: 16
            //            color: "blue"
            focus: true
            anchors.top: type1.bottom
            anchors.topMargin: 20
            anchors.left: region.right
        }


        Text{
            id:ed
            text: "集数："
            //            font.family: "Helvetica"
            font.pointSize: 16
            //            color: "blue"
            focus: true
            anchors.top: region.bottom
            anchors.topMargin: 30
            anchors.left: add.right
            anchors.leftMargin: 20
        }
        TextField{
            id:esd
            width:100
            height: 35
            //            font.family: "Helvetica"
            font.pointSize: 16
            //            Layout.preferredWidth: 150
            //            color: "blue"
            focus: true
            anchors.top: region1.bottom
            anchors.topMargin: 20
            anchors.left: ed.right
        }
        Text {
            id: e
            text: qsTr("集")
            //            font.family: "Helvetica"
            font.pointSize: 16
            //            color: "blue"
            focus: true
            anchors.top: region1.bottom
            anchors.topMargin: 20
            anchors.left: esd.right
        }

        Text {
            id: rec
            text: qsTr("是否推荐：")
            //            font.family: "Helvetica"
            font.pointSize: 16
            //            color: "blue"
            focus: true
            anchors.top: ed.bottom
            anchors.topMargin: 30
            anchors.left: add.right
            anchors.leftMargin: 20
        }
        TextField{
            id:recc
            //            font.family: "Helvetica"
            font.pointSize: 16
            //            color: "blue"
            focus: true
            anchors.top: esd.bottom
            anchors.topMargin: 20
            anchors.left: rec.right
            text: "fff"
        }


        Rectangle{
            id:actor1
            width: parent.width
            height: 40
            anchors.top: add.bottom
            anchors.topMargin: 10
            border.color: "lightblue"
            Text {
                id: actorEdit1
                text: qsTr("演员:")
                //                font.family: "Helvetica"
                font.pointSize: 16
                //                color: "blue"
                anchors.top: actor1.top
                anchors.left: actor1.left
            }
            TextEdit{
                id:actorEdit
                anchors.top: actor1.top
                anchors.left: actorEdit1.right
                anchors.leftMargin: 15
                //                font.family: "Helvetica"
                font.pointSize: 16
                //                color: "blue"
                focus: true
                text: "演员"
            }
        }

        Rectangle{
            id:derector
            width: parent.width
            height: 50
            anchors.top: actor1.bottom
            anchors.topMargin: 10
            border.color: "lightblue"
            Text{
                id:dictorEdit1
                //                font.family: "Helvetica"
                font.pointSize: 16
                //                color: "blue"
                focus: true
                text: "导演:"
                anchors.top: derector.top
                anchors.left: derector.left
            }
            TextEdit{
                id:dictorEdit
                //                font.family: "Helvetica"
                font.pointSize: 16
                anchors.top: derector.top
                anchors.left: dictorEdit1.right
                anchors.leftMargin: 15
                //                color: "blue"
                focus: true
                text: "导演"
            }
        }

        Rectangle{
            id:info
            width: parent.width-10
            height: 150
            clip: true
            anchors.top: derector.bottom
            anchors.topMargin: 10
            border.color: "lightblue"
            Text {
                id: infoma1
                text: qsTr("简介：")
                anchors.top: info.top
                anchors.left: info.left
                font.pointSize: 16

            }
            TextEdit{
                id:infoma
                width: parent.width-100
                height: parent.height
                wrapMode: TextEdit.Wrap
                anchors.top: info.top
                anchors.left: infoma1.right
                anchors.leftMargin: 10
                //                font.family: "Helvetica"
                font.pointSize: 16
                //                color: "blue"
                focus: true
                text: "  "
//                height: contentHeight
//                width: info.width - vbar.width-100
//                y: -vbar.position * infoma.height
//                //                                   wrapMode: TextEdit.Wrap
////                selectByKeyboard: true
//                selectByMouse: true

//                MouseArea{
//                    anchors.fill: parent
//                    onWheel: {
//                        if (wheel.angleDelta.y > 0) {
//                            vbar.decrease();
//                        }
//                        else {
//                            vbar.increase();
//                        }
//                    }
//                    onClicked: {
//                        infoma.forceActiveFocus();
//                    }
//                }
            }

//            ScrollBar {
//                id: vbar
//                hoverEnabled: true
//                active: hovered || pressed
//                orientation: Qt.Vertical
//                size: info.height / infoma.height
//                width: 10
//                anchors.top: parent.top
//                anchors.right: parent.right
//                anchors.bottom: parent.bottom
//            }
        }
        //        Rectangle{
        //            id:about1
        //            width: parent.width
        //            height: 40
        //            anchors.top: derector.bottom
        //            anchors.topMargin: 10
        //            Text {
        //                id: aboutEdit1
        //                text: qsTr("相关影视：")
        //                anchors.top: about1.top
        //                anchors.left: about1.left
        ////                font.family: "Helvetica"
        //                font.pointSize: 16
        ////                color: "blue"
        //            }
        //            TextEdit{
        //                id:aboutEdit
        ////                font.family: "Helvetica"
        //                font.pointSize: 16
        ////                color: "blue"
        //                focus: true
        //                text: "相关影视"
        //                anchors.top: about1.top
        //                anchors.left: aboutEdit1.right
        //            }
        //        }

        Button{
            id:save
            //            anchors.top: about1.bottom
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 200
            text: "保存"
            onClicked: {
                listModel.set(index1,{"typ": type1.text, "region":region1.text,"bigType":typeMo.text,"introduction":infoma.text,
                                  "actor":actorEdit.text,"dictor":dictorEdit.text,"episode":esd.text
                              })
                //                console.log(type1.text)
                var message = typeMo.text+" "+name1.text+" "+type1.text+" "+" "+region1.text+" "+esd.text+" "+dictorEdit.text+" "+actorEdit.text+" "+infoma.text+" "+recc.text+" "+imgPup.updateFileSource+" "+imgPup.adress

                var adress = "../MoonOperationAndMaintenance/image/avatar/"+imgPup.imagename
                client.getMovieInfo(name1.text,"c",message,adress,imgPup.adress)

                messages()
            }
        }
        Button{
            text: "添加"
            anchors.left: save.right
            //            anchors.top: about1.bottom
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.leftMargin: 50
            onClicked:{
                imgPup.flag = true
                addDig.open()

            }
        }
    }
    AddDialog{
        id:addDig
    }
    ImagePup{
        id:imgPup
    }
}
