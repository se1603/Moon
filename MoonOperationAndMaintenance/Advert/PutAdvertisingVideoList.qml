/* Author:董梦丹
* Date:2020-02-20
* 最后修改: 04-26
* Note:广告
*/
import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: videochoice
    width: parent.width
    height: parent.height - videoTypeMenu.height

    property var menus: JSON.parse(client.showDetailCategory(videoTypeMenu.types))
    property var detail: menus[0].name

    property alias modelDelegate: modelDelegate

    property var selectmessage: ""
    property var selecttype: ""
    property var selectcategory: ""

    //    property var advertName: ""
    //    property var advertPath: ""

    property var backmessage: ""

    property var videotype: videoTypeMenu.types

    property var categoryStatus:""

    property var date:new Date()
    property var diff:""

    property alias videodetail: videoDetail

    signal cancelAllSelect(var cancelname)
    signal uncheckdetail(var detailtype)
    signal checkdetail(var name)
    signal alltypecheck()
    signal alltypeuncheck()
    signal allvideocheck()
    signal allvideouncheck()
    signal sendcategorycheck(var value,var category)
    signal categorystate()

    Connections {
        target: advertisingButton
        onClicked: {
            selectcategory = ""
            categorystate()
        }
    }

    Connections {
        target: client
        onAddAdvertSucceed: {
            commitDialog.close()
            backmessage = "Succeed!"
            messageDialog.open()
        }
        onAddAdvertFailed: {
            commitDialog.close()
            backmessage = "Failed!"
            messageDialog.open()
        }
    }

    Connections {
        target: videoTypeMenu
        onSelectAll: {
            categoryStatus = typename
            judgeSelectedAll(categoryStatus)
        }
        onCancelSelect: {
            categoryStatus = ""
            judgeCancelSelected(cancelname)
        }
        onSendBack: {
            if(typename !== " "){
                commitCategoryAdd(typename)
            }else{
                commitAdd()
            }
        }
    }

    //    property var wid: mainWindow.width < 1100
    //                      ? (videoBlock.width - 3.2*videoGrid.columnSpacing) / 4
    //                      : (videoBlock.width - 4*videoGrid.columnSpacing) / 5
    //    property var hei: 4 * videoTypes.height

    Rectangle {
        id: videoTypes
        width: parent.width
        height: 1 / 12 * parent.height
        Row{
            height: parent.height
            spacing: 1 / 20 * parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            Repeater {
                id: menudelegate
                model: menus
                Row{
                    property bool checks:false
                    property var name:modelData.name

                    CheckBox {
                        id: box
                        checked: parent.checks

                        property var thename:parent.name
                        style:
                            CheckBoxStyle {
                            indicator: Rectangle {
                                implicitWidth: 18
                                implicitHeight: 18
                                border.color: control.activeFocus ? "blue" : "gray"
                                border.width: 1
                                Rectangle {
                                    visible: control.checked
                                    color: "#649ccc"
                                    radius: 1
                                    anchors.margins: 4
                                    anchors.fill: parent
                                }
                            }
                        }
                        onClicked : {
                            parent.checks = checked
                            if(parent.checks === true && parent.name === detail){
                                allBeChoosen(true)
                            }else if(parent.checks === false && parent.name === detail){
                                allBeChoosen(false)
                            }
                            categorycheck(videotype)
                        }
                        Connections {
                            target: videochoice
                            onUncheckdetail: {
                                if(box.thename === detailtype){
                                    box.checked = false
                                    box.parent.checks = box.checked
                                }
                            }
                            onCheckdetail: {
                                if(box.thename === name){
                                    box.checked = true
                                    box.parent.checks = box.checked
                                }
                            }
                            onAlltypecheck: {
                                box.checked = true
                                box.parent.checks = box.checked
                            }
                            onAlltypeuncheck: {
                                box.checked = false
                                box.parent.checks = box.checked
                            }
                        }
                    }
                    Text {
                        text: modelData.name
                        font.pixelSize: 14
                        anchors.verticalCenter: parent.verticalCenter
                        opacity: 0.7
                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            enabled: true
                            opacity: 0.7
                            onEntered: {
                                parent.opacity = 1
                            }
                            onExited: {
                                parent.opacity = 0.7
                            }
                            onClicked: {
                                detail = modelData.name
                                modelDelegate.model = JSON.parse(client.showVideos(
                                                                     videoTypeMenu.types, detail))
                            }
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        id: videoBlock
        width: 3 / 4 * parent.width
        height: parent.height - videoTypes.height
        anchors.top: videoTypes.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        ScrollView {
            anchors.fill: parent
            clip: true
            GridLayout {
                anchors.top: parent.top
                columns: mainWindow.width < 1100 ? 5 : 6
                columnSpacing: 1 / 2 * videoTypes.height
                rowSpacing: 1 / 2 * videoTypes.height

                Repeater {
                    id: modelDelegate
                    model: JSON.parse(client.showVideos(videoTypeMenu.types, detail))

                    Rectangle {
                        id: videoRec
                        width: 130
                        height: 200
                        property var name:modelData.name
                        property var source:modelData.post
                        property bool check:false
                        property var detailtype:detail

                        Image {
                            id: videoPost
                            width: parent.width
                            height: 5 / 6 * parent.height
                            source: "file:" + parent.source
                            Text {
                                id: notes
                                visible: false
                                text: "点击查看详情"
                                font.pixelSize: 14
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                                color: "white"
                            }
                            MouseArea {
                                anchors.fill: parent
                                hoverEnabled: true
                                enabled: true
                                onEntered: {
                                    parent.opacity = 0.5
                                    notes.visible = true
                                }
                                onExited: {
                                    parent.opacity = 1
                                    notes.visible = false
                                }
                                onClicked: {
                                    videoDetail.currentName = videoRec.name
                                    videoDetail.currentPost = videoRec.source
                                    videoDetail.visible = true
                                }
                            }
                        }
                        CheckBox {
                            id: videoCheck
                            text: parent.name
                            anchors.top: videoPost.bottom
                            anchors.topMargin: 15
                            checked: parent.check

                            onClicked: {
                                parent.check = checked
                                if(parent.check === false){
                                    uncheck(parent.detailtype)
                                    categorycheck(videotype)
                                }else{
                                    judgedetail(parent.detailtype)
                                }
                            }

                            Connections {
                                target: videochoice
                                onAlltypecheck: {
                                    videoCheck.checked = true
                                    videoCheck.parent.check = videoCheck.checked
                                }
                                onAllvideocheck: {
                                    videoCheck.checked = true
                                    videoCheck.parent.check = videoCheck.checked
                                }
                                onAllvideouncheck: {
                                    videoCheck.checked = false
                                    videoCheck.parent.check = videoCheck.checked
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Popup {
        id: commitDialog
        width: 1 / 3 * mainWindow.width
        height: 1 / 2 * mainWindow.height
        visible: false
        anchors.centerIn: parent

        ColumnLayout {
            width: 3 / 4 * parent.width
            height: parent.height
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10

            Text {
                text: "待投放的广告信息：\n"
                      + advertname + "," + advertcompany + "," + advertduetime
                font.pixelSize: 12
            }

            Text {
                id: categorytxt
                text: "待插播目录：\n" + selectcategory
                visible: (selectcategory === "") ? false : true
            }

            Rectangle {
                id: txtRec
                width: parent.width
                height: 70
                visible: (categorytxt.visible === true) ? false : true
                ScrollView{
                    anchors.fill: parent
                    clip: true
                    Column{
                        Text {
                            id: typetxt
                            text: "待插播类别：\n" + selecttype + "\n"
                            font.pixelSize: 12
                            width: 6 / 7 * txtRec.width
                            wrapMode: Text.Wrap
                        }
                        Text {
                            id: messagetxt
                            text: "待插播视频：\n" + selectmessage
                            font.pixelSize: 12
                            width: 6 / 7 * txtRec.width
                            wrapMode: Text.Wrap
                        }
                    }
                }
            }

            Row{
                spacing: 50
                Button {
                    text: qsTr("Commit")
                    onClicked: {
                        judgeDate()
                        if(diff === "success"){
                            if(categorytxt.visible === true){
                                client.addAdvertToCategory(advertname, advertcompany,
                                                           advertduetime, selectcategory)
                            }else{
                                client.addAdvertToVideos(advertname, advertcompany,
                                                         advertduetime, selectmessage,
                                                         videoTypeMenu.types,
                                                         selecttype)
                            }
                        }else if(diff === "error"){
                            backmessage = "该广告到期时间不足一月，请重新选择"
                            messageDialog.open()
                        }
                    }
                }

                Button {
                    text: qsTr("CLose")
                    onClicked: {
                        commitDialog.close()
                    }
                }
            }
        }
    }

    Dialog {
        id: messageDialog
        width: 1 / 2 * commitDialog.width
        height: 1 / 2 * commitDialog.height
        visible: false
        anchors.centerIn: parent

        Column {
            spacing: 1 / 6 * parent.width
            anchors.centerIn: parent

            Text {
                text: backmessage
                width: parent.width
                wrapMode: Text.Wrap
            }

            Button {
                text: "Close"
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    messageDialog.close()
                }
            }
        }
    }

    PutAdvertisingVideoDetail {
        id: videoDetail
        visible: false
    }

    function allBeChoosen(checkState) {
        if(checkState === true)
            allvideocheck()
        else
            allvideouncheck()
    }

    function commitCategoryAdd(category) {
        selectcategory = category
        //        advertName = advertChoice.advertName
        //        advertPath = advertChoice.path
        commitDialog.open()
    }

    function commitAdd() {
        selecttype = ""
        selectmessage = ""
        //        advertPath = advertChoice.path
        //        advertName = advertChoice.advertName

        for(var i = 0; i !== menudelegate.model.length; i++){
            if(menudelegate.itemAt(i).checks === true){
                selecttype += menudelegate.itemAt(i).name
                selecttype += "/"
            }
        }

        var flag = 0
        for(var i = 0; i !== modelDelegate.model.length; i++){
            if(modelDelegate.itemAt(i).check === true){
                selectmessage += modelDelegate.itemAt(i).name
                selectmessage += "/"
                flag++
            }
        }

        console.log(flag)

        if(flag === modelDelegate.model.length && flag !== 1){
            selectmessage = ""
        }else if(flag === modelDelegate.model.length && flag === 1){
            selecttype = ""
        }

        if(selecttype !== "" || selectmessage !== ""){
            commitDialog.open()
        }
    }

    function judgeSelectedAll(category){
        if(category === videotype){
            alltypecheck()
            allBeChoosen(true)
        }
    }

    function judgeCancelSelected(category){
        if(category === videotype){
            alltypeuncheck()
            allBeChoosen(false)
        }
    }

    function uncheck(detailtype){
        console.log(detailtype)
        for(var i = 0; i != menudelegate.model.length;i++){
            if(menudelegate.itemAt(i).name === detailtype){
                menudelegate.itemAt(i).checks = false
                uncheckdetail(detailtype)
            }
        }
    }

    function judgedetail(detailname){
        var flag = 0
        for(var i = 0;i != modelDelegate.model.length;i++){
            if(modelDelegate.itemAt(i).check === false){
                flag = 1
            }
        }

        if(flag === 0){
            checkdetail(detailname)
            categorycheck(videotype)
        }
    }

    function categorycheck(category){
        var flag = 0
        for(var i = 0; i != menudelegate.model.length;i++){
            if(menudelegate.itemAt(i).checks === true){
                flag++
            }
        }

        if(flag === menudelegate.model.length){
            sendcategorycheck("check",category)
        }else{
            sendcategorycheck("uncheck",category)
        }
    }

    function judgeDate(){
        var year = date.getFullYear()
        var month = date.getMonth()+1
        var day = date.getDate()
        //                        console.log(year+"--"+month+"=="+day)
        var dueyear = advertduetime.slice(0,4)
        var duemonth = advertduetime.slice(4,6)
        var dueday = advertduetime.slice(6,8)

        if(duemonth[0] === "0"){
            duemonth = duemonth[1]
        }
        if(dueday[0] === "0"){
            dueday = dueday[1]
        }
        //        console.log(dueyear+"@")
        //        console.log(duemonth+"#")
        //        console.log(dueday+"$")
        //        var advertyear = Number(dueyear)
        //        var advertmonth = Number(duemonth)
        //        var advertday = Number(dueday)

        //        var currentyear = Number(year)
        //        var currentmonth = Number(month)
        //        var currentday = Number(day)

        diff = client.judgedate(year,month,day,dueyear,duemonth,dueday)
        //        console.log(diff)
    }
}
