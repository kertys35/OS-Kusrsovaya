import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick 2.12

Window {
    visible: true
    width: 640
    height: 640
    title: qsTr("Chat-A-Lot-Client")
    //создание сообщений
    Connections {
            target: client
            function onNewMessage(ba) {
                listModelMessages.append({
                                             message: ba + " "
                                         })
            }
        }
    //ввод ip адреса сервера и имени пользователя
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
                    id: textFieldUser
                    placeholderText: qsTr("Имя пользователя")
                    Layout.fillWidth: true
                    onAccepted: buttonConnect.clicked()
                }
                Button {
                    id: buttonConnect
                    text: qsTr("Приоединиться")
                    onClicked: client.connectToServer(textFieldIp.text, 30000, textFieldUser.text)
                }
                Button {
                    id: buttonDisconnect
                    text: qsTr("Отключиться")
                    onClicked: {
                        client.disconnectFromServer()
                        textFieldIp.clear()
                    }
                }
            }
            //вывод на экран сообщений
            ListView {
                Layout.fillHeight: true
                Layout.fillWidth: true
                clip: true
                model: ListModel {
                    id: listModelMessages
                    ListElement {
                        message: "Добро пожаловать в мессенджер"
                    }
                }
                delegate: ItemDelegate {
                    text: message
                }
                ScrollBar.vertical: ScrollBar {}
            }
            //отправка сообщений
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
