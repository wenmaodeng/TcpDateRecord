import QtQuick 2.14
import QtQuick.Controls 2.14

Rectangle{
    property alias ip: ipText.text
    property alias port: portText.text

    Row{
        id:row
        height: 35
        width: parent.width
        Label {
            width: 80
            height: parent.height
            horizontalAlignment:Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            text: qsTr("Tcp服务IP: ")
            color: "white"
            background: Rectangle{
                color: "darkgray"
            }
        }
        TextField  {
            id: ipText
            width: (parent.width-160)*0.7
            height: parent.height
            horizontalAlignment:Text.AlignLeft
            verticalAlignment: Text.AlignVCenter

        }
        Label {
            width: 80
            height: parent.height
            horizontalAlignment:Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            text: qsTr("Tcp服务端口: ")
            color: "white"
            background: Rectangle{
                color: "darkgray"
            }
        }
        TextField {
            id: portText
            width: (parent.width-160)*0.3
            height: parent.height
            horizontalAlignment:Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }
    }
}
