/*
  * author:guchangrong 2016051604218
  * date:2020.4.26
  * 增加搜索相关界面的显示组件
  */
import QtQuick 2.0
import "../Audience"
import "../PlayArea"

Rectangle {
    width: parent.width
    height:fullScreenFlag ? parent.height - 38 : parent.height //17/18 * parent.height
    anchors.bottom: parent.bottom
    color: "green"

    property alias audienceInterface: audienceInterface

    property alias middleLoader: loader
    property alias playLoader: pLoader
    property alias browsePage: browseComponent
    property alias playPage: playComponent

    property string playPost
    property string playName
    property string playUrl
    property string playType
    property var adverts

    property var nextName
    property var startTime:""
    property var lastStartTime:""

    property var date: new Date()

    property var searchResource
    property alias searchFilmPage: searchFilmComponent
    property alias searchDramaPage: searchDramaComponent
    property alias searchCharacterPage: searchCharacterComponent
    property alias searchNonePage: searchNoneComponent
    property var lastPlayName

    signal stopPlay(var playname, var newname)  //停止播放之前的视频
    signal loadAdvert()  //播放广告
    signal startPlay()
    signal newPlay()
    signal recordTime()

    Loader{
        id: loader
        visible: true
        anchors.fill: parent
        sourceComponent: browseComponent
    }

    Loader{
        id: pLoader
        visible: false
        anchors.fill: parent
        sourceComponent: playComponent
    }

    Component{
        id: browseComponent
        BrowsePage{

        }
    }

    //用户主页
    AudienceInterface {
        id: audienceInterface
        visible: false
    }

    //播放页面
    Component{
        id: playComponent
        Play{

        }
    }

    //搜索电影界面
    Component{
        id: searchFilmComponent
        SearchFilm{

        }
    }

    //搜索连续剧界面
    Component{
        id:searchDramaComponent
        SearchDrama{

        }
    }

    //搜索演员和导演界面
    Component{
       id:searchCharacterComponent
       SearchCharacter{

       }
    }

    //未搜索到的界面
    Component{
        id:searchNoneComponent
        SearchNone{

        }
    }

}
