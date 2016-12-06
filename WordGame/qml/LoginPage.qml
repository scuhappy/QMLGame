import QtQuick 2.7
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
Item {
    property int large_text: 22
    property int mid_text: 20
    property int small_text: 18
    signal close()
    signal signup()
    Rectangle{
        id:root
        anchors.fill: parent
        color: "#00B000"
        Rectangle{
            id:center
            anchors.centerIn:root
            width: 400
            height: 300
            color:"transparent"

            Column{
                spacing: 10
                anchors.top: parent.top
                Label
                {
                    id:loginlabel
                    text: "Login"
                    font.pixelSize: large_text
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Row{
                    spacing: 10
                    Label{
                        id: namelabel
                        text:"User Name"
                        font.pixelSize: mid_text
                        width: 100
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Rectangle{
                        color:"white"
                        width: center.width-namelabel.width-10
                        height:30
                        radius: 4
                        anchors.verticalCenter: parent.verticalCenter
                        TextInput{
                            id:nameinput
                            font.pixelSize: mid_text
                            anchors.fill: parent
                            KeyNavigation.tab: pswinput
                            selectByMouse: true
                        }
                    }
                }
                Row{
                    spacing:10
                    Label{
                        id: passlabel
                        text:"Password"
                        font.pixelSize: mid_text
                        width: 100
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Rectangle{
                        color:"white"
                        width: center.width-passlabel.width-10
                        height:30
                        radius: 4
                        anchors.verticalCenter: parent.verticalCenter
                        TextInput{
                            id:pswinput
                            font.pixelSize: mid_text
                            anchors.fill: parent
                            passwordCharacter:"*"
                            echoMode: TextInput.Password
                            KeyNavigation.tab: nameinput
                            selectByMouse: true
                        }

                    }
                }
                Row{
                    id:row4
                    spacing: 1
                    leftPadding :100
                    Button{
                        width: 100
                        height: 30

                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            text: qsTr("Sign Up")
                            font.pixelSize: small_text
                        }
                    }
                    Button{
                        width: 100
                        height: 30

                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            text: "Sign In"
                            font.pixelSize: small_text
                        }
                        onClicked: {
                            console.debug("name : ",nameinput.text,"password : ",pswinput.text);
                            logical.sendLogin(nameinput.text, pswinput.text)
                        }
                    }
                    MessageDialog{
                        id: messageDialog
                        title: "Warnning Dialog"
                            text: "Wrong password!"
                            icon: StandardIcon.Warning
                            onAccepted: {
                                console.log("And of course you could only agree.")
                                messageDialog.close();
                            }
                            //Component.onCompleted: visible = true
                    }

                    Button{
                        width: 100
                        height: 30
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            text: qsTr("Exit")
                            font.pixelSize: small_text
                        }
                    }
                }
            }
        }
    }
}
