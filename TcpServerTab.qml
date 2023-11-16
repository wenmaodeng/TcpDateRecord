import QtQuick 2.0
import QtQuick.Controls 2.14
import Qt.labs.platform 1.1

Rectangle{
    Row{
        id:row
        height: 35
        width: parent.width
        spacing: 1

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
            width: (parent.width-164)*0.2
            height: parent.height
            horizontalAlignment:Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: "9999"
        }
        Button{
            id:startTcpServer
            height: parent.height
            text: "创建Tcp服务"
            width:(parent.width-164)*0.3
            onClicked: {
                var port=portText.text
                if(tcpServer.start(port))
                {
                    startTcpServer.enabled=false
                }
            }
        }
        Button{
            id:endTcpServer
            height: parent.height
            text: "停止Tcp服务"
            width:(parent.width-164)*0.2
            onClicked: {
                tcpServer.stop()
                startTcpServer.enabled=true
            }
        }
        Button{
            id:sendDataButton
            height: parent.height
            text: "读取文件并发送数据"
            width:(parent.width-164)*0.3
            enabled: !startTcpServer.enabled
            onClicked: {
                fileDialog.open()
            }
        }
        Label {
            id:countinfo
            width: 80
            height: parent.height
            horizontalAlignment:Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: "white"
            background: Rectangle{
                color: "black"
            }
        }
    }

    ScrollView {
        id:scrollView
        anchors.top: row.bottom
        width: parent.width
        height: parent.height-row.height
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        TextArea {
            id:textArea
            width: scrollView.width
            wrapMode:TextEdit.Wrap
            textFormat: TextEdit.AutoText
        }
    }

    FileDialog {
        id: fileDialog
        fileMode:FileDialog.OpenFile
        title: qsTr("打开文件")
        nameFilters: ["文本文件 (*.txt)", "*.*"]
        onAccepted: {
            if(textHelper.readData(fileDialog.file))
            {
                textArea.text="";
                textHelper.startSendData();
                fileDialog.close()
            }
        }
    }
    Connections{
        target: textHelper
        onSendData:{
            textArea.append(data)
        }
    }
    Connections{
        target: textHelper
        onCountInfo:{
            countinfo.text=info
        }
    }
}
