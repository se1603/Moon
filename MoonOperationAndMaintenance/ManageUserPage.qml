/*
 *guchangrong   2016051604218
 * 2020-2-14
 * 管理员处理用户举报页面
 */
import QtQuick 2.0
import QtQuick.Controls 2.5
import "./usermanage"


Item {
    anchors.fill: parent

    property alias reprotStack: reportStack
    property alias reportUntreatedPage: reportuntreatedpage
    property alias informInformationPage: informinformationpage
    property alias reportProcessedPage: reportprocessedpage
    property alias processedInformationPage: processedinformationpage
    property alias tipDelete: deletetip

    property var untreatedinfobyid: ""
    property var processedinfobyid: ""

    //加载页面
    Rectangle{
        id:managePage
        width: parent.width
        height: parent.height
        anchors.fill: parent
        StackView{
            id:reportStack
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.fill: parent
            initialItem: reportuntreatedpage
        }

        //显示未处理详情界面
        Component{
            id:informinformationpage
            InformInformationPage{

            }
        }

        //显示已处理详情界面
        Component{
            id:processedinformationpage
            ProcessedInformationPage{

            }
        }

        //显示管理用户未处理信息页面
        Component{
            id:reportuntreatedpage
            ReportUntreatedPage{

            }
        }

        //显示已处理的信息列表
        Component{
            id:reportprocessedpage
            ReportProcessedPage{

            }
        }
        //提示删除评论结果
        Component{
            id:deletetip
            TipDelete{

            }
        }
    }
}
