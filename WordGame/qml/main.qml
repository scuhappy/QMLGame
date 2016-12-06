import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
ApplicationWindow {
    visible: true
    width: 800
    height: 480
    title:  qsTr("Word Game")
    Component.onCompleted: {
        console.log("login :",clientmodel.Login);
    }

    LoginPage{
        id:loginpage
        visible: true
        opacity: clientmodel.Login ? 0:1
        anchors.fill: parent;
        z:1
        Behavior on opacity {
                NumberAnimation { duration: 5000; easing.type: Easing.InQuad;}
            }
    }
    GamePage{
        id:gamepage
        anchors.fill: parent
        visible: clientmodel.Login
        z:0
    }
    SignUpPage{
        id:signup
        anchors.fill: parent
        visible: false;
    }

}
