/* Author:董梦丹
* Date:2020-04-27
* Note:广告
*/
import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4

Rectangle {
    id:adjustpage
    width: parent.pagewidth
    height: parent.pageheight

    property alias advertLoader: adjustpage.parent

    property var commitadvertname: ""
    property var commitvideoname: ""
    property var commitduetime: ""

    property var backmessage: ""

    property var diff:""
    property var date: new Date()

    property var locationdiff: ""

    Connections {
        target: client
        onChangeAdvertTimeSucceed: {
            backmessage = "Succeed!"
            messageDialog.open()
        }
        onChangeAdvertTimeFailed: {
            backmessage = "Failed!"
            messageDialog.open()
        }
        onChangeAdvertLocationSucceed: {
            backmessage = "Succeed!"
            messageDialog.open()
        }
        onChangeAdvertLocationFailed: {
            backmessage = "Failed!"
            messageDialog.open()
        }
        onChangeAdvertLocationNotFound: {
            backmessage = "无法修改投放位置，您填写的影视不存在"
            messageDialog.open()
        }
    }


    Image {
        id: button
        width: 1 / 20 * parent.width
        height: 1 / 20 * parent.width
        source: "../image/advert/left.png"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                advertLoader.source = "../ManageAdvertPage.qml"
            }
        }
    }

    Row{
        id: titleRow
        height: button.height
        anchors.left: button.right
        spacing: 2 / 3 * parent.width
        Text {
            id: title1
            text: "已投放的映前广告："
            font.pixelSize: 16
            color: "#6495ED"
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            id: title2
            text: "操作选项："
            font.pixelSize: 16
            color: "#6495ED"
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Rectangle {
        id: listRec
        width: 4 / 5 * parent.width
        height: parent.height - button.height - 10
        anchors.top: button.bottom
        anchors.topMargin: 10
        anchors.left: button.right

        ScrollView {
            anchors.fill: parent
            clip: true
            verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff

            ColumnLayout {

                Text {
                    text: "请选择待调整的广告（单选）："
                    font.pixelSize: 16
                    color: "#99CCFF"
                }

                Repeater {
                    id: advertList
                    model: JSON.parse(client.showAdvertising())

                    Rectangle {
                        id: listRow
                        width: listRec.width
                        height: 1 / 10 * listRec.height

                        property var name: modelData.name
                        property var company: modelData.company
                        property var duetime: modelData.duetime
                        property var videoname: modelData.videoname
                        property var check: false

                        Row {
                            spacing: 20
                            anchors.verticalCenter: parent.verticalCenter

                            Text {
                                width: 1 / 6 * listRow.width
                                text: "名称："+ listRow.name
                                wrapMode: Text.Wrap
                                font.pixelSize: 14
                            }

                            Text {
                                width: 1 / 6 * listRow.width
                                text: "公司：" + listRow.company
                                wrapMode: Text.Wrap
                                font.pixelSize: 14
                            }

                            Text {
                                width: 1 / 6 * listRow.width
                                text: "到期时间：" + listRow.duetime
                                wrapMode: Text.Wrap
                                font.pixelSize: 14
                            }

                            Text {
                                width: 1 / 6 * listRow.width
                                text: "投放位置：" + listRow.videoname
                                wrapMode: Text.Wrap
                                font.pixelSize: 14
                            }

                            Text {
                                width: 1 / 6 * listRow.width
                                text: "投放内容：映前广告"
                                wrapMode: Text.Wrap
                                font.pixelSize: 14
                            }


                            CheckBox {
                                property var myname: parent.name
                                style:
                                    CheckBoxStyle {
                                    indicator: Rectangle {
                                        implicitWidth: 20
                                        implicitHeight: 20
                                        radius: 3
                                        border.color: control.activeFocus ? "blue" : "gray"
                                        border.width: 1
                                        Rectangle {
                                            visible: control.checked === true
                                            color: "#6495ED"
                                            border.color: "#333"
                                            radius: 1
                                            anchors.margins: 4
                                            anchors.fill: parent
                                        }
                                    }
                                }
                                checked: listRow.check
                                onClicked: {
                                    listRow.check = checked
                                    judgeBeSelected()
                                    judgeToSelect()
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Column {
        anchors.left: titleRow.left
        anchors.leftMargin: title1.width + titleRow.spacing
        anchors.top: listRec.top

        spacing: 60

        Button {
            id: time
            text: "修改到期时间"
            onClicked: {
                changetime()
            }
        }

        Button {
            id: location
            text: "修改投放位置"
            onClicked: {
                changelocation()
            }
        }

        Button {
            id: content
            text: "修改投放内容"
            enabled: false
        }
    }

    Dialog {
        id: timeDialog
        width: 1 / 3 * parent.width
        height: 1 / 3 * parent.height
        visible: false
        anchors.centerIn: parent

        Rectangle {
            id: txtRec
            width: 3 / 4 * parent.width
            height: 2 / 3 * parent.height
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter

            Column {
                anchors.fill: parent
                spacing: 12

                Text {
                    text: "待修改到期时间的广告："
                    font.pixelSize: 14
                    color: "#6495ED"
                }

                Text {
                    text: commitadvertname+"/"+commitduetime+"/"
                    font.pixelSize: 14
                }

                Text {
                    text: "修改到期时间："
                    font.pixelSize: 14
                    color: "#6495ED"
                }

                Row {
                    spacing: 15

                    ComboBox {
                        id: year
                        model: ["2019","2020","2021","2022","2023","2024","2025",
                                "2026","2027","2028","2029"]
                    }

                    ComboBox {
                        id: month
                        model: ["01","02","03","04","05","06","07","08","09",
                                "10","11","12"]
                    }

                    ComboBox {
                        id: oneday
                        model: ["01","02","03","04","05","06","07","08","09",
                                "10","11","12","13","14","15","16","17","18",
                                "19","20","21","22","23","24","25","26","27",
                                "28","29","30","31"]
                    }
                }
            }
        }

        Row {
            spacing: 30
            anchors.top: txtRec.bottom
            anchors.topMargin: 12
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                text: "Confirm"
                onClicked: {
                    var newdate = year.currentText+month.currentText+oneday.currentText
                    if(newdate === commitduetime){
                        backmessage = "当前广告日期并未修改"
                        timeDialog.close()
                        messageDialog.open()
                    }else{
                        judgeDate(year.currentText,month.currentText,oneday.currentText)
                        if(diff === "success"){
                            client.changeAdvertTime(commitadvertname, newdate)
                            advertLoader.source = "AdvertisingMaintenance.qml"
                        }else if(diff === "error"){
                            backmessage = "修改的日期距今不足一个月，请重新选择"
                            timeDialog.close()
                            messageDialog.open()
                        }
                    }
                }
            }
            Button {
                text: "Cancel"
                onClicked: {
                    timeDialog.close()
                }
            }
        }
    }

    Dialog {
        id: locationDialog
        width: 1 / 3 * parent.width
        height: 1 / 3 * parent.height
        visible: false
        anchors.centerIn: parent

        Rectangle {
            id: locationRec
            width: 3 / 4 * parent.width
            height: 2 / 3 * parent.height
            anchors.horizontalCenter: parent.horizontalCenter

            Column {
                anchors.fill: parent
                spacing: 12

                Text {
                    text: "待修改投放位置的广告："
                    font.pixelSize: 14
                    color: "#6495ED"
                }

                Text {
                    text: commitadvertname+"/"+commitvideoname+"/"
                    font.pixelSize: 14
                }

                Text {
                    text: "修改投放位置："
                    font.pixelSize: 14
                    color: "#6495ED"
                }

                TextField {
                    id: newlocation
                }
            }
        }

        Row {
            spacing: 30
            anchors.top: locationRec.bottom
            anchors.topMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                text: "Confirm"
                onClicked: {
                    locationdiff = ""
                    judgelocation(newlocation.text)

                    if(newlocation.text === ""){
                        backmessage = "投放位置为空，请填写"
                        messageDialog.open()
                    }else if(newlocation.text === commitvideoname || locationdiff === "true"){
                        backmessage = "投放位置重复，请重新修改"
                        messageDialog.open()
                    }else{
                        client.changeAdvertLocation
                                (commitadvertname, commitvideoname, newlocation.text)
                        advertLoader.source = "AdvertisingMaintenance.qml"
                    }
                }
            }
            Button {
                text: "Cancel"
                onClicked: {
                    locationDialog.close()
                }
            }
        }
    }

    Dialog {
        id: messageDialog
        width: 1 / 2 * timeDialog.width
        height: 1 / 2 * timeDialog.height
        visible: false
        anchors.centerIn: parent

        Column {
            spacing: 30
            anchors.centerIn: parent

            Text {
                text: backmessage
                width: 2 / 3 * messageDialog.width
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

    function judgeBeSelected(){
        var index = 0
        for(var i = 0; i != advertList.model.length; i++){
            if(advertList.itemAt(i).check === true){
                index = i
            }
        }
        for(var j = 0; j != advertList.model.length; j++){
            if(j !== index){
                advertList.itemAt(j).enabled = false
            }
        }
    }

    function judgeToSelect(){
        var flag = 0
        for(var i = 0; i != advertList.model.length; i++){
            if(advertList.itemAt(i).check === false){
                flag++
            }
        }

        if(flag === advertList.model.length){
            for(var j = 0; j != advertList.model.length; j++){
                advertList.itemAt(j).enabled = true
            }
        }
    }

    function getdetail(){
        commitadvertname = ""
        commitvideoname = ""
        commitduetime = ""

        for(var i = 0; i != advertList.model.length; i++){
            if(advertList.itemAt(i).check === true){
                commitadvertname = advertList.itemAt(i).name
                commitvideoname = advertList.itemAt(i).videoname
                commitduetime = advertList.itemAt(i).duetime
            }
        }
    }

    function judgeTime(duetime){
        var year = date.getFullYear()
        var month = date.getMonth()+1
        var day = date.getDate()

        var str = year+"-"+month+"-"+day
        var newstr = client.cliptime(str)
        console.log(newstr)
    }

    function judgeDate(advertyear,advertmonth,advertday){
        var year = date.getFullYear()
        var month = date.getMonth()+1
        var day = date.getDate()
        //                        console.log(year+"--"+month+"=="+day)
        var dueyear = advertyear
        var duemonth = advertmonth
        var dueday = advertday

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

    function changetime(){
        getdetail()

        if(commitadvertname !== "" && commitvideoname !== "" && commitduetime !== ""){
            timeDialog.open()
        }
    }

    function changelocation(){
        getdetail()

        if(commitadvertname !== "" && commitvideoname !== "" && commitduetime !== ""){
            locationDialog.open()
        }
    }

    function judgelocation(newlocation){
        locationdiff = "false"

        for(var i = 0; i != advertList.model.length; i++){
            if(advertList.itemAt(i).name === commitadvertname &&
                    advertList.itemAt(i).videoname === newlocation){
                locationdiff = "true"
            }
        }
    }
}
