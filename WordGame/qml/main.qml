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
        visible: !clientmodel.Login
        anchors.fill: parent;
        z:1
        Behavior on visible {

             animation: hidelogin
        }
//        onClose:
//        {
//            gamepage.visible=true;
//            hidelogin.running = true;
//            gamepage.z = 2;
//        }
    }
    GamePage{
        id:gamepage
        anchors.fill: parent
        visible: clientmodel.Login
        z:0
    }
    PropertyAnimation {
        id: hidelogin;
        target: loginpage;
        property: "opacity";
        to: 0;
        duration: 1000
    }

}
