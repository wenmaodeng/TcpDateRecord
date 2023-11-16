import QtQuick 2.14
import QtQuick.Controls 2.14
import Qt.labs.platform 1.1

Rectangle{
    id:clitenRectangle
    width: parent.width
    height: parent.height
    Row{
        id:row
        height: 35
        width: parent.width
        spacing: 1
        IpPortInput{
            id:ipAndPortInput
            height: parent.height
            width: parent.width*0.4
            ip:"162.168.100.171"
            port:"9999"
        }
        Button{
            id:startButton
            height: parent.height
            text: "连接服务"
            width:  parent.width*0.15
            onClicked: {
                var ip=ipAndPortInput.ip
                var port=ipAndPortInput.port
                tcpClient.connectToServer(ip,port)
                startButton.enabled=false;
            }
        }
        Button{
            height: parent.height
            text: "断开连接"
            width:  parent.width*0.15
            onClicked: {
                tcpClient.stop()
                startButton.enabled=true;
            }
        }
        Button{
            height: parent.height
            text: "清空数据"
            width:  parent.width*0.15
            onClicked: {
                textArea.text=""
            }
        }
        Button{
            height: parent.height
            width: parent.width*0.15
            text: "保存数据"
            onClicked: {
                fileDialog.open()
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
        fileMode:FileDialog.SaveFile
        title: qsTr("保存数据")
        nameFilters: ["文本文件 (*.txt)", "*.*"]
        onAccepted: {
            textHelper.writeData(fileDialog.file,textArea.text)
            textArea.text=""
        }
    }

    Connections{
        target: tcpClient
        onTriggerClientRecData:{
            textArea.append(data)
        }
    }
}
