import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Rectangle {
    id: loginPage
    width: parent.width
    height: parent.height

    color: Qt.rgba(0,0,0, 0.75)

    Connections{
        target: client
        onLoginFailed: {
            noticeText = "帐号或密码错误！"
        }
    }

    Rectangle {
        id: loginForm
        anchors.centerIn: parent
        color: "white"
        width: content.width + 58
        height: content.height + 26
        radius: 4
    }

    GridLayout {
        id: content
        anchors.centerIn: loginForm
        columnSpacing: 20
        rowSpacing: 10
        columns: 2

        Text {
            Layout.topMargin: 8
            Layout.bottomMargin: 15
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignHCenter
            text: "登陆"
        }

        Text {
            text: qsTr("帐号")
            font.pixelSize: 15
        }

        TextField {
            id: txtUsernumber
            Layout.preferredWidth: 200
            font.pixelSize: 15
        }

        Text {
            text: qsTr("密码")
            font.pixelSize: 15
        }

        TextField {
            id: txtPassword
            Layout.preferredWidth: 200
            font.pixelSize: 15
            echoMode: TextInput.Password
        }

        Column {
            Layout.fillWidth: true
            Layout.columnSpan: 2
            Layout.topMargin: 12

            Button {
                text: qsTr("登陆")
                flat: false
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    if(txtUsernumber.text === "" || txtPassword.text === "")
                        noticeText.text = "请正确输入帐号和密码！";
                    else
                    {
                        client.sendLoginInfo(txtUsernumber.text,txtPassword.text)
                    }

                }
            }

            Text{
                id: noticeText
                color: "red"
                font.pixelSize: 12
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
