//time：2019.4.30
//内容：页面跳转组件
//author：徐丹

import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    width:  middleInterface.width
    height: middleInterface.height
//    anchors.centerIn: middleArea


    Row {
        width: parent.width
        height: parent.height
//        spacing: 1 / 60 * parent.width

        MiddleMenu {
            id: middle_Menu
            visible: true
        }

        Rectangle {
            id: page_display
            width: 13/ 14 * parent.width
            height: parent.height

            color: "red"

            StackView {
                id: middle_stack
                anchors {
                    fill: parent
                }
                initialItem:movie_page
            }

            Component {
                id: comic_page

                ComicStack {
                }
            }

//            Component{
//                id:drama_page
//                Drama{

//                }
//            }
            Component{
                id:movie_page
                MovieStack{

                }
            }
//            Component{
//                id:variety_page
//                Variety{

//                }
//            }
//            Component{
//                id:comic_page
//                Comic{

//                }
//            }

//            Component{
//                id:search_page
//                Search{
//                }
//            }

//            Component{
//                id:browserecord_page
//                BrowseRecord{

//                }
//            }
        }
    }
}
