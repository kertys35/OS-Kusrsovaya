import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12

ApplicationWindow {
    visible: true
    width: 640
    height: 640
    title: qsTr("Chat-a-lot server")

    //создание сообщений
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
//вывод сообщений на экран
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

        }
    }

