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
    //    color: "red"
    Rectangle{
        id:upRtn
        width: parent.width/5
        height: 100
        anchors.left: parent.Left
        color: "green"
        Text {
            id: name
            anchors.centerIn: parent
            font.pixelSize: 24
            font.family: "宋体"
            text: qsTr("上传")
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                client.upServer()
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
            typ:"type"
            region:"region1"
            bigType:"bigType"
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
        height: parent.height
        color: "red"


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
                color:ListView.isCurrentItem ? "lightblue" : "white"
                onColorChanged: {
                    name1.text = name
                    type1.text = typ
                    region1.text = region
                    typeMo.text = bigType
                    infoma.text = introduction
                    actorEdit.text = actor
                    dictorEdit.text = dictor
                    aboutEdit.text = about
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
                        //鼠标覆盖，显示对应的图片
                        if(nameSlide.ListView.view.currentIndex !== index){
                            nameSlide.ListView.view.currentIndex = index;
                        }
                    }
                    onExited: {
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
        width: parent.width*4/5
        height: parent.height
        color: "yellow"
        Rectangle{
            id:add
            anchors.left: parent.left
            width: 200
            height: 300
            color: "lightblue"
            Text{
                text: "添加图片"
                anchors.centerIn: parent
                font.family: "Helvetica"
                font.pointSize: 20
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
            font.family: "Helvetica"
            font.pointSize: 20
            color: "blue"
        }
        TextEdit{
            id:name1
            anchors.left: nameLabel.right
            font.family: "Helvetica"
            font.pointSize: 20
            color: "blue"

        }
        Text{
            id:type
            text: "类型:"
            anchors.top: name1.bottom
            anchors.topMargin: 20
            anchors.left: add.right
            font.family: "Helvetica"
            color: "blue"
            font.pointSize: 20
        }
        TextEdit {
            id:type1
            width: 240
            text: "<b>type</b>"
            font.family: "Helvetica"
            font.pointSize: 20
            color: "blue"
            focus: true
            anchors.top: name1.bottom
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
            //            text: "<b>region</b>"
            font.family: "Helvetica"
            font.pointSize: 20
            color: "blue"
        }

        TextEdit {
            id:region1
            width: 240
            text: "<b>region</b>"
            font.family: "Helvetica"
            font.pointSize: 20
            color: "blue"
            focus: true
            anchors.top: type1.bottom
            anchors.topMargin: 20
            anchors.left: region.right
        }

        Text {
            id:typeMo1
            //            width: 240
            text: "类别："
            font.family: "Helvetica"
            font.pointSize: 20
            color: "blue"
            focus: true
            anchors.top: region.bottom
            anchors.topMargin: 20
            anchors.left: add.right
        }
        TextEdit {
            id:typeMo
            width: 240
            text: "<b>bigType</b>"
            font.family: "Helvetica"
            font.pointSize: 20
            color: "blue"
            focus: true
            anchors.top: region1.bottom
            anchors.topMargin: 20
            anchors.left: typeMo1.right
        }
        Text{
            id:ed
            text: "集数："
            font.family: "Helvetica"
            font.pointSize: 20
            color: "blue"
            focus: true
            anchors.top: typeMo1.bottom
            anchors.topMargin: 20
            anchors.left: add.right
        }
        TextField{
            id:esd
            font.family: "Helvetica"
            font.pointSize: 20
            Layout.preferredWidth: 50
            //            color: "blue"
            focus: true
            anchors.top: typeMo.bottom
            anchors.topMargin: 20
            anchors.left: ed.right
        }
        Text {
            id: e
            text: qsTr("集")
            font.family: "Helvetica"
            font.pointSize: 20
            //            color: "blue"
            focus: true
            anchors.top: typeMo.bottom
            anchors.topMargin: 20
            anchors.left: esd.right
        }

        Text {
            id: rec
            text: qsTr("是否推荐：")
            font.family: "Helvetica"
            font.pointSize: 20
            color: "blue"
            focus: true
            anchors.top: ed.bottom
            anchors.topMargin: 20
            anchors.left: add.right
        }
        TextEdit{
            id:recc
            font.family: "Helvetica"
            font.pointSize: 20
            color: "blue"
            focus: true
            anchors.top: esd.bottom
            anchors.topMargin: 20
            anchors.left: rec.right
            text: "fff"
        }

        Rectangle{
            id:info
            width: parent.width
            height: 100
            anchors.top: add.bottom
            anchors.topMargin: 10
            Text {
                id: infoma1
                text: qsTr("简介：")
                anchors.top: info.top
                anchors.left: info.left
                font.family: "Helvetica"
                font.pointSize: 20
                color: "blue"
            }
            TextEdit{
                id:infoma
                width: parent.width
                wrapMode: TextEdit.Wrap
                anchors.top: info.top
                anchors.left: infoma1.right
                font.family: "Helvetica"
                font.pointSize: 20
                color: "blue"
                focus: true
                text: "  "
            }
        }
        Rectangle{
            id:actor1
            width: parent.width
            height: 40
            anchors.top: info.bottom
            anchors.topMargin: 10
            Text {
                id: actorEdit1
                text: qsTr("演员:")
                font.family: "Helvetica"
                font.pointSize: 20
                color: "blue"
                anchors.top: actor1.top
                anchors.left: actor1.left
            }
            TextEdit{
                id:actorEdit
                anchors.top: actor1.top
                anchors.left: actorEdit1.right
                font.family: "Helvetica"
                font.pointSize: 20
                color: "blue"
                focus: true
                text: "演员"
            }
        }

        Rectangle{
            id:derector
            width: parent.width
            height: 40
            anchors.top: actor1.bottom
            anchors.topMargin: 10
            Text{
                id:dictorEdit1
                font.family: "Helvetica"
                font.pointSize: 20
                color: "blue"
                focus: true
                text: "导演:"
                anchors.top: derector.top
                anchors.left: derector.left
            }
            TextEdit{
                id:dictorEdit
                font.family: "Helvetica"
                font.pointSize: 20
                anchors.top: derector.top
                anchors.left: dictorEdit1.right
                color: "blue"
                focus: true
                text: "导演"
            }
        }
        Rectangle{
            id:about1
            width: parent.width
            height: 40
            anchors.top: derector.bottom
            anchors.topMargin: 10
            Text {
                id: aboutEdit1
                text: qsTr("相关影视：")
                anchors.top: about1.top
                anchors.left: about1.left
                font.family: "Helvetica"
                font.pointSize: 20
                color: "blue"
            }
            TextEdit{
                id:aboutEdit
                font.family: "Helvetica"
                font.pointSize: 20
                color: "blue"
                focus: true
                text: "相关影视"
                anchors.top: about1.top
                anchors.left: aboutEdit1.right
            }
        }

        Button{
            id:save
            anchors.top: about1.bottom
            anchors.left: parent.left
            anchors.leftMargin: 200
            text: "save"
            onClicked: {
                listModel.set(index1,{"typ": type1.text, "region":region1.text,"bigType":typeMo.text,"introduction":infoma.text,
                                  "actor":actorEdit.text,"dictor":dictorEdit.text,"about":aboutEdit.text,"episode":esd.text
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
            anchors.top: about1.bottom
            anchors.leftMargin: 20
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
