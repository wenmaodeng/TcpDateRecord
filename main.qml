import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

Window {
    visible: true
    width: 800
    height: 600
    title: qsTr("Tcp数据保存和发送")
    TabBar {
        id: bar
        width: parent.width
        TabButton {
            text: qsTr("Tcp客户端接收数据")
        }
        TabButton {
            text: qsTr("Tcp服务端发送数据")
        }
    }
    StackLayout {
        width: parent.width
        height: parent.height-bar.height
        anchors.top: bar.bottom
        currentIndex: bar.currentIndex
        TcpClientTab {
            id:tcpClientTab
            width: parent.width
            height: parent.height
        }
        TcpServerTab {
            id:tcpServerTab
            width: parent.width
            height: parent.height
        }
    }
}
