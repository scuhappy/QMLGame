import QtQuick 2.0
import QtWebSockets 1.0
Item {

    Rectangle{
        id:root
        anchors.fill: parent
        color: "#78EDFF"
        property var wordList:["A","B","C","D","E","F","G","H","I","J","K","L","M","N",
        "O","P","Q","R","S","T","U","V","W","X","Y","Z"]

        property var wordMap: {1:"A",2:"B",3:"C", "dfdf":{"ddd":"vbbb","sdfds":"dfg"}}

        MouseArea{
            anchors.fill: parent
            onClicked: {
             // cardList.visible = true;
              //  socket.sendTextMessage("test test!");
               // console.debug(root.wordMap[1]);
                for(var i in root.wordMap)
                {
                    console.debug(i + "  /  "+ root.wordMap[i]);
                }
            }
        }
        Row{
            id: cardList
            spacing: 10
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            visible: false

            Repeater{
                model: 5
                Card{
                    width: 80
                    height: 100
                    wordContent:  root.wordList[Math.floor(Math.random()*100%26)]
                    Component.onCompleted: {

                    }
                }
            }


        }
    }

}
