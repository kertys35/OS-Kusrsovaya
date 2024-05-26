import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12

ApplicationWindow {
    visible: true
    width: 640
    height: 640
    title: qsTr("Chat-a-lot")

    Connections{
        target : server
        function onNewMessage(ba)
        {
            listModelMessages.append({
                                         message: ba + ""
                                     }
                                         )
        }

    }

    ColumnLayout{
        anchors.fill: parent
        ListView{
            Layout.fillHeight: true
            Layout.fillWidth: true
            clip: true
            model: ListModel{
                id: listModelMessages
                ListElement {
                    message: "Добро пожаловать на сервер"
                }
            }
            delegate: ItemDelegate{
                text: message
            }
            ScrollBar.vertical: ScrollBar{}
        }
        RowLayout{
            TextField{
                id: textFilledMessage
               placeholderText: qsTr("Ваше сообщение")
               Layout.fillWidth: true
               onAccepted:  buttonSend.clicked()
            }
            Button{
                id: buttonSend
                text: qsTr("Отправить")
                onClicked: {

                    console.log("Сообщение отправлено")
                    textFilledMessage.clear()
                }
            }
        }
    }
}
