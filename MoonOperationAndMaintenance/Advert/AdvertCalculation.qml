/* Author:董梦丹
* Date:2020-03-01
* Note:广告
*/
import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.12

Rectangle {
    id: calculation
    width: parent.width
    height: parent.height

    property var lists:""

    Row {
        id: companySearch
        width: parent.width
        height: 1 / 10 * parent.height
        spacing: txtInput.height
        anchors.top: parent.top
        anchors.topMargin: 1 / 20 * parent.height

        Text {
            text: "搜索公司名称："
            font.pixelSize: 16
        }

        TextField {
            id: txtInput
        }

        Image {
            id: searchbutton
            source: "qrc:/image/advert/search.png"
            MouseArea {
                anchors.fill: parent
                onClicked:
                {
                    if(txtInput.text !== ""){
                        lists = JSON.parse(client.showCompanyClicksRank(txtInput.text))
                        if(lists.length === 1 && lists[0].name === "NULL")
                            rankList.model = 0
                        else
                            rankList.model = lists
                    }
                }
            }
        }
    }

    Rectangle {
        id: rankRec
        width: parent.width
        height: parent.height - companySearch.height
        anchors.top: companySearch.bottom

        ScrollView {
            anchors.fill: parent
            clip: true
            ColumnLayout {
                anchors.top: parent.top
                anchors.topMargin: 1 / 10 * txtInput.height
                spacing: 1 / 2 * txtInput.height

                Text {
                    id: notice
                    text: "——暂时没有任何广告——"
                    font.pixelSize: 22
                    color: "#696969"
                    visible: (lists.length === 1 && lists[0].name
                             === "NULL") ? true : false
                }

                Repeater {
                    id: rankList
                    model: 0

                    Rectangle {
                        id: listRec
                        width: companySearch.width
                        height: 35

                        property var name: modelData.name
                        property var clicks: modelData.clicks
                        property var duetime: modelData.duetime

                        Row {
                            width: parent.width
                            spacing: parent.height
                            anchors.verticalCenter: parent.verticalCenter

                            Text {
                                width: 1 / 4 * parent.width
                                text: "NAME: " + listRec.name
                                font.pixelSize: 16
                            }

                            Text {
                                width: 1 / 4 * parent.width
                                text: "CLICKS: " + listRec.clicks
                                font.pixelSize: 16
                            }

                            Text {
                                width: 1 / 4 * parent.width
                                text: "DUETIME: " + listRec.duetime
                                font.pixelSize: 16
                            }
                        }
                    }
                }
            }
        }
    }
}
