import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick 2.12

Window {
    visible: true
    width: 640
    height: 640
    title: qsTr("Chat-A-Lot-Client")
    Connections {
            target: client
            function onNewMessage(ba) {
                listModelMessages.append({
                                             message: ba + ""
                                         })
            }
        }

        ColumnLayout {
            anchors.fill: parent
            RowLayout {
                Layout.fillWidth: true
                TextField {
                    id: textFieldIp
                    placeholderText: qsTr("IP Сервера")
                    Layout.fillWidth: true
                    onAccepted: buttonConnect.clicked()
                }
                TextField {
                    id: textFieldPort
                    placeholderText: qsTr("Порт сервера")
                    Layout.fillWidth: true
                    onAccepted: buttonConnect.clicked()
                }
                Button {
                    id: buttonConnect
                    text: qsTr("Connect")
                    onClicked: client.connectToServer(textFieldIp.text, textFieldPort.text)
                }
            }
            ListView {
                Layout.fillHeight: true
                Layout.fillWidth: true
                clip: true
                model: ListModel {
                    id: listModelMessages
                    ListElement {
                        message: "Добро пожаловать в чат"
                    }
                }
                delegate: ItemDelegate {
                    text: message
                }
                ScrollBar.vertical: ScrollBar {}
            }
            RowLayout {
                Layout.fillWidth: true
                TextField {
                    id: textFieldMessage
                    placeholderText: qsTr("Ваше сообшение")
                    Layout.fillWidth: true
                    onAccepted: buttonSend.clicked()
                }
                Button {
                    id: buttonSend
                    text: qsTr("Отправить")
                    onClicked: {
                        client.sendMessage(textFieldMessage.text)
                        textFieldMessage.clear()
                    }
                }
            }
        }
    }
