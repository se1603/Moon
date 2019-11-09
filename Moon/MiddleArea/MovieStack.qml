//time：2019.5.1
//内容：动漫
//Author：徐丹

import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    id:comic
    width: parent.width
    height: parent.height

   property var comics
    StackView{
        id: movie_stack
        anchors {
            fill: parent
        }
        initialItem: movieRecommend_page
    }
    Component{
        id:movietype_page
        Movie{

        }

    }
    Component{
        id:movieRecommend_page
        MovieRecommd{

        }
    }

}
