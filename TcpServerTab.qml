import QtQuick 2.0
import QtQuick.Controls 2.14
import Qt.labs.platform 1.1

Rectangle{
    Row{
        id:row
        height: 35
        width: parent.width

        IpPortInput{
            id:ipAndPortInput
            height: parent.height
            width: (parent.width-80)*0.5
            ip:"127.0.0.1"
            port:"9999"
        }
        Button{
            height: parent.height
            text: "创建Tcp服务"
            width:(parent.width-80)*0.25
            onClicked: {
                var ip=ipAndPortInput.ip
                var port=ipAndPortInput.port
                tcpServer.start(ip,port)
            }
        }
        Button{
            id:sendDataButton
            height: parent.height
            text: "读取文件并发送数据"
            width:(parent.width-80)*0.25
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
