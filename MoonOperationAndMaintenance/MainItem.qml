import QtQuick 2.0
import "Advert"

Item {
    anchors.fill: parent
    property bool userLoggedIn: false
    property var managerIdentity

    property alias manageuserPage:manageuser

    ManageUserPage{
        id:manageuser
        visible: false
    }


    Connections{
        target: client
        onLoginSucceed: {
            userLoggedIn = true
            managerIdentity = identity
            loagerPage()
            console.log("chenggong")
        }
    }

    LoginPage{
        z: 1 // show login above actual app pages
        visible: opacity > 0
        enabled: visible
        opacity: userLoggedIn ? 0 : 1 // hide if user is logged in
        Behavior on opacity { NumberAnimation { duration: 250 } } // page fade in/out
    }

    Loader{
        id: loader
        anchors.fill: parent
    }

    function loagerPage()
    {
        if(managerIdentity === "1")
        {
            console.log("aaa")
            loader.source = "ManageUserPage.qml"
            manageuser.visible = true
        }
        else if(managerIdentity === "2")
            loader.source = "ManageMTVPage.qml"
        else if(managerIdentity === "3"){
            loader.source = "ManageAdvertPage.qml"
            var i = client.showVideoCategory();
        }
    }
}
