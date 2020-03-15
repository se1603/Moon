import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Window 2.12
import Moon 1.0

Rectangle {
    id: player
    width: parent.width
    height: parent.height
    color: "black"

    property bool isPlayingAdvert: false
    property bool isPlaying: false
    property string videoPath: ""
    property bool isFirstPlay: true
    property bool volumeOff: false
    property bool isFullScreen: false

    property var previousWidth: 1075
    property var previousHeight: 670

    property var advertsPlaying
    property var allAdvertsTime: 30

    property var clickAvert: 0

    property var lastName:middleArea.playName
    property var lastPost:middleArea.playPost
    property var lastType:middleArea.playType
    property var startTime:""
    property var lastStartTime:""

    property var date:new Date()
    property var collections: (audienceInterface.audienceName === "") ? ""
                                                                      :        JSON.parse(client.audienceCollection(audienceInterface.audienceName))

    Connections {
        target: middleArea
        onStopPlay: {
            if(newName !== lastName){
                cplayer.stop()
                if(lastName !== "" && lastStartTime !== "" && lastPost !== ""){
                    //终止记录
                    var stop = new Date()
                    var hours = stop.getHours()
                    var minutes = stop.getMinutes()
                    var seconds = stop.getSeconds()
                    var time = hours+":"+minutes+":"+seconds
                    client.addBrowseRecord(lastName, startTime, time, lastPost)
                }

                //                if(audienceInterface.audienceName === ""){
                //                    client.addBrowseRecord(lastName, startTime, stopTime, lastPost)
                //                }
                //                else{
                //                    client.addRecord(audienceInterface.audienceName,
                //                                     lastName, startTime, stopTime, lastType)
                //                    client.addBrowseRecord(lastName, startTime, stopTime, lastPost);
                //                }
            }
        }
        onRecordTime: {
            //get
            var year = date.getFullYear()
            var month = date.getMonth()+1
            var day = date.getDate()
            var hours = date.getHours()
            var minutes = date.getMinutes()
            var seconds = date.getSeconds()
            var starttime = year+"-"+month+"-"+day+"-"+hours+":"+minutes+":"+seconds
            if(startTime === ""){
                startTime = starttime
                lastStartTime = ""
            }else{
                lastStartTime = startTime
                startTime = starttime
            }
        }
    }


    CVideoPlayer{
        id: cplayer
        anchors.fill: parent
    }


    Rectangle{
        id: skipAdvert
        width: 80
        height: 25
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        color: "#444444"
        radius: 50
        opacity: 0.8
        visible: isPlayingAdvert ? true : false
        z:2

        Text {
            font.pixelSize: 16
            text: qsTr("跳过广告")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            color: "white"
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                hoverEnabled: true
                enabled: true

                onEntered: {
                    parent.color = "blue"
                }
                onExited: {
                    parent.color = "white"
                }
                onClicked: {
                    //停止播放广告
                    isPlayingAdvert = false
                    advertTimer.stop()
                    stopPlay()
                    allAdvertsTime = 30

                    //播放视频
                    isPlaying = true
                    isFirstPlay = false
                    cplayer.startPlay(videoPath)
                    cplayer.visible = true
                    console.log("a:" + isPlaying)
                }
            }
        }
    }

    Timer{
        id: advertTimer
        interval: 1000
        //        running: true
        triggeredOnStart: true
        repeat: true
        onTriggered: {
            aTime.text = allAdvertsTime
            allAdvertsTime--
            if(allAdvertsTime < 0)
            {
                //停止播放广告
                isPlayingAdvert = false
                advertTimer.stop()
                stopPlay()
                allAdvertsTime = 30

                //播放视频
                isPlaying = true
                isFirstPlay = false
                cplayer.startPlay(videoPath)
                cplayer.visible = true
            }
        }
    }

    Rectangle{
        id: advertTime
        width: 60
        height: 25
        anchors.right: skipAdvert.left
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 10
        color: "#444444"
        radius: 50
        opacity: 0.8
        visible: isPlayingAdvert ? true : false
        Text{
            id: aTime
            font.pixelSize: 16
            text: allAdvertsTime
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            color: "red"
            font.bold: true
        }

        Text {
            font.pixelSize: 16
            text: qsTr("秒")
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            color: "white"
        }
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {
            if(isPlayingAdvert)
            {
                clickAvert++
                //add
                console.log(clickAvert)
            }
            else
            {
                if(isPlaying)
                {
                    isPlaying = false
                    cplayer.pause()
                }
                else
                {
                    isPlaying = true
                    cplayer.play()
                }
            }
        }
    }

    Connections{
        target: cplayer
        onSigShowTotalTime:
        {
            duation.text = totalTime
        }
    }

    Connections{
        target: cplayer
        onSigShowCurrentTime:
        {
            timing.text = currentTime
        }
    }

    Connections{
        target: cplayer
        onSigVideoIsOver:
        {
            cplayer.stop();
            console.log("llll")
            isPlaying = false
            isFirstPlay = true;
            cplayer.visible = false;
        }
    }

    Connections{
        target: cplayer
        onSigSliderTotalValue:{
            progressBar.to = value
        }
        onSigSliderCurrentValue:{
            progressBar.value = currentvalue
        }
    }

    Rectangle{
        id: bottomControl
        color: "black"
        opacity: 0
        width: parent.width
        height: parent.height * 1 / 18
        anchors.bottom: parent.bottom
        visible: isPlayingAdvert ? false : true

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered:{
                playerBottom.visible = true
            }
            onExited: {
                showBottonTimer.start()
            }
        }
    }

    Timer{
        id:showBottonTimer
        interval: 5000;
        running: true;
        repeat: true
        onTriggered:{
            playerBottom.visible = false
        }
    }

    Connections{
        target: progressBar
        onMoved:{
            cplayer.sliderMoved(progressBar.value)
        }
    }

    Rectangle{
        id: playerBottom
        color: "#DDDDDD"
        width: parent.width
        height: parent.height * 1 / 18
        anchors.bottom: parent.bottom
        visible: isPlayingAdvert ? false : true

        Slider{
            id: progressBar
            width: parent.width
            height: parent.height * 2 / 5
            anchors.top: parent.top
            from: 0
            to: 100

            background: Rectangle {
                x: progressBar.leftPadding
                y: progressBar.topPadding + progressBar.availableHeight / 2 - height / 2
                implicitWidth: 200
                implicitHeight: 4
                width: progressBar.availableWidth
                height: implicitHeight
                radius: 2
                color: "#bdbebf"

                Rectangle {
                    width: progressBar.visualPosition * parent.width
                    height: parent.height
                    color: "#00BBFF"
                    radius: 2
                }
            }

            handle: Rectangle{
                x:progressBar.leftPadding + progressBar.visualPosition * (progressBar.availableWidth - width)
                y: progressBar.topPadding + progressBar.availableHeight / 2 - height / 2
                color:progressBar.pressed ? "#00BBFF":"white";
                border.color: "gray";
                width: 15;
                height: 15;
                radius: 12;
            }
        }

        Rectangle{
            id: controllerButtons
            width: parent.width
            height: parent.height * 3 / 5
            anchors.top: progressBar.bottom

            Rectangle{
                id: playOrPause
                width: parent.height
                height: parent.height
                anchors.left: parent.left
                Image {
                    width: parent.height
                    height: parent.height
                    anchors.fill: parent
                    source: isPlaying ? "../image/videoController/pause.png" :
                                        "../image/videoController/play.png"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        if(isPlaying)
                        {
                            isPlaying = false
                            cplayer.pause();
                        }
                        else
                        {
                            isPlaying = true
                            if(isFirstPlay)
                            {
                                isFirstPlay = false
                                cplayer.startPlay(videoPath);
                                cplayer.visible = true
                            }
                            else
                                cplayer.play()
                        }
                    }
                }
            }

            Rectangle{
                id: stop
                width: parent.height
                height: parent.height
                anchors.left: playOrPause.right
                anchors.leftMargin: 20

                Image {
                    width: parent.height
                    height: parent.height
                    anchors.fill: parent
                    source: "../image/videoController/stop.png"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        isFirstPlay = true
                        isPlaying = false
                        progressBar.value = 0
                        duation.text = "00:00:00"
                        timing.text = "00:00:00"
                        cplayer.stop()
                        cplayer.visible = false
                    }
                }
            }
            Rectangle{
                id: nextVideo
                width: parent.height
                height: parent.height
                anchors.left: stop.right
                anchors.leftMargin: 20
                Image {
                    width: parent.height
                    height: parent.height
                    anchors.fill: parent
                    source: "../image/videoController/next.png"
                }
            }
            Rectangle{
                id: playTime
                width: 4 * parent.height
                height: parent.height
                anchors.left: nextVideo.right
                anchors.leftMargin: 20

                Text {
                    id: timing
                    text: "00:00:00"
                    anchors.verticalCenter: parent.verticalCenter
                }

                Text {
                    id: slash
                    text: " / "
                    anchors.left: timing.right
                    anchors.verticalCenter: parent.verticalCenter
                }

                Text {
                    id: duation
                    text: "00:00:00"
                    anchors.left: slash.right
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Rectangle{
                id:fullScreen
                width: parent.height
                height: parent.height
                anchors.right: parent.right
                anchors.rightMargin: 10
                Image {
                    width: parent.height
                    height: parent.height
                    anchors.fill: parent
                    source: "../image/videoController/fullScreen.png"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        console.log("全屏")
                        if(isFullScreen)
                        {
                            isFullScreen = false


                            mainWindow.width = previousWidth
                            mainWindow.height = previousHeight

                            xLflag = !xLflag
                            xRflag = !xRflag

                            mainItem.exitfullScreen()
                            rightbt.visible = true
                            leftbu.opacity = 0.5
                        }
                        else
                        {
                            isFullScreen = true
                            mainWindow.width = Screen.desktopAvailableWidth
                            mainWindow.height = Screen.desktopAvailableHeight
                            xLflag = !xLflag
                            xRflag = !xRflag

                            mainItem.fullScreen()
                            rightbt.visible = false
                            leftbu.opacity = 0
                        }
                    }
                }
            }

            Rectangle{
                id:star
                width: parent.height
                height: parent.height
                anchors.right: fullScreen.left
                anchors.rightMargin: 20
                Image {
                    id: starImg
                    width: parent.height
                    height: parent.height
                    anchors.fill: parent
                    source: (collections.length !== 0 && search(play.name) === true)
                            ? "../image/videoController/star2.png"
                            : "../image/videoController/star.png"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            var year = date.getFullYear()
                            var month = date.getMonth()+1
                            var day = date.getDate()
                            var hours = date.getHours()
                            var minutes = date.getMinutes()
                            var collecttime = year+"-"+month+"-"+day+"-"+hours+":"+minutes
                            if(audienceInterface.audienceName === ""){
                                audienceItem.open()
                            }else{
                                addCollection(play.name,collecttime)
                                collections = JSON.parse(client.audienceCollection(audienceInterface.audienceName))
                            }
                        }
                    }
                }
            }

            Rectangle{
                id:voiceController
                width: 4 * parent.height
                height: parent.height
                anchors.right: star.left
                anchors.rightMargin: 20

                Slider{
                    id:voiceBar
                    width: parent.width
                    anchors.verticalCenter: parent.verticalCenter
                    from: 0
                    to:100
                    value: 50

                    background: Rectangle {
                        x: voiceBar.leftPadding
                        y: voiceBar.topPadding + voiceBar.availableHeight / 2 - height / 2
                        implicitWidth: 200
                        implicitHeight: 4
                        width: voiceBar.availableWidth
                        height: implicitHeight
                        radius: 2
                        color: "#bdbebf"

                        Rectangle {
                            width: voiceBar.visualPosition * parent.width
                            height: parent.height
                            color: "#00BBFF"
                            radius: 2
                        }
                    }

                    handle: Rectangle{
                        x:voiceBar.leftPadding + voiceBar.visualPosition * (voiceBar.availableWidth - width)
                        y: voiceBar.topPadding + voiceBar.availableHeight / 2 - height / 2
                        color:voiceBar.pressed ? "#00BBFF":"white";
                        border.color: "gray";
                        width: 10;
                        height: 10;
                        radius: 12;
                    }

                }

            }

            Connections{
                target: voiceBar
                onMoved:{
                    if(voiceBar.value === 0)
                        volumeOff = true
                    else
                        volumeOff = false
                    cplayer.voiceSliderMoved(voiceBar.value)
                }
            }

            Rectangle{
                id:voice
                width: parent.height
                height: parent.height

                anchors.right: voiceController.left
                Image {
                    width: voice.height
                    height: parent.height
                    anchors.fill: parent
                    source: volumeOff ? "../image/videoController/volumeOff.png" : "../image/videoController/volumeUp.png"
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        volumeOff = !volumeOff
                        if(volumeOff)
                        {
                            voiceBar.value = 0
                            cplayer.voiceSliderMoved(0)
                        }
                        else
                        {
                            voiceBar.value = 50
                            cplayer.voiceSliderMoved(50)
                        }
                    }
                }
            }
        }

    }

    function startPlay()
    {
        console.log("dd:" + videoPath)
        isPlaying = true
        cplayer.startPlay(videoPath)
        cplayer.visible = true
        isFirstPlay = false
    }

    function stopPlay()
    {
        isFirstPlay = true
        isPlaying = false
        progressBar.value = 0
        duation.text = "00:00:00"
        timing.text = "00:00:00"
        cplayer.stop()
        cplayer.visible = false

        //        播放视频
        //        isPlaying = true
        //        cplayer.startPlay(videoPath)
        //        if(isFirstPlay)
        //        {
        //            isFirstPlay = false
        //            cplayer.startPlay(videoPath)
        //            cplayer.visible = true
        //        }
    }

    function playAdverts()
    {
        console.log("ooooo:" + adverts.length)

        isPlayingAdvert = true
        allAdvertsTime = 30
        advertTimer.start()
        if(adverts.length > 0)
        {
            var i = 0;
            for(; i !== adverts.length; i++)
            {
                cplayer.visible = true
                cplayer.startPlay(adverts[i].rtsp)
            }
        }

    }

    function search(cName){
        var flag = 0
        for(var i=0;i<collections.length;i++){
            if(cName === collections[i].name){
                flag = 1
            }
        }
        if(flag === 0)
            return false
        else
            return true
    }

    function addCollection(cName,collecttime){

        var flag = 0
        for(var i=0;i<collections.length;i++){
            if(cName === collections[i].name){
                flag = 1
            }
        }
        if(flag === 0) {
            client.addCollection(audienceInterface.audienceName,
                                 collecttime,play.name,play.datas.resource.category)
        }
    }
}
