import QtQuick 2.0
import "TopArea"
import "MiddleArea"

Item {
    width: parent.width
    height: parent.height

    TopArea{
        id: topArea
    }

    MiddleArea{
        id: middleArea
    }

}
