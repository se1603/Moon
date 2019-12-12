import QtQuick 2.0
import "TopArea"
import "MiddleArea"
import "Audience"

Item {
    width: parent.width
    height: parent.height

    property alias middleArea:middleArea

    TopArea{
        id: topArea
    }

    MiddleArea{
        id: middleArea
    }

    AudiencePoupItem {
        id:audienceItem
    }

}
