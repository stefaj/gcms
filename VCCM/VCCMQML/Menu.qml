import QtQuick 2.4
import QtQuick.Controls.Styles 1.3
import QtQuick.Controls 1.3
import QtQuick.Window 2.0
import QMLOpenGL 1.0
import QtGraphicalEffects 1.0
import "VCCMQML/addbutton.js"  as funct

Item {
    id:tree
    width: 450
    height: 800
    Loader {id:gamestate;focus: true;width: tree.width; height: tree.height}

Loader {
    id:mainmenu
    width: tree.width
    height: tree.height
    Image {
         id: background
         anchors.fill: parent

         source: "Texture0"
         fillMode: Image.Stretch
         opacity: 1
     }
    Rectangle {

        anchors.centerIn: parent
        width: 100;
        height: 110;
        color: Qt.rgba(0.0, 0.0, 0.0, 0.0)

        Rectangle {
            id: playbutton
            property color onHoverColor: Qt.rgba(0.0, 0.0, 0.0, 0.9)
            property color defaultColor: Qt.rgba(0.0, 0.0, 0.0, 0.5)
            anchors.top: parent.top
            width: 100;
            height: 50;
            radius: 20;
            color: defaultColor
            border.color: defaultColor
            border.width: 4
            Text { anchors.centerIn: parent; text: "View"; color: "white";font.pixelSize: 18;}
            MouseArea {
                id: mouseAreaplay;
                anchors.fill: parent ;
                hoverEnabled: true
                onEntered:{ parent.color = parent.onHoverColor;parent.border.color = parent.onHoverColor;}
                onExited: {parent.color = parent.defaultColor;parent.border.color = parent.defaultColor}
                onClicked: {gamestate.source ="Viewer";mainmenu.visible = false;}}
            states: State {
                name: "down"; when: mouseAreaplay.containsMouse == true
                PropertyChanges { target: playbutton; y: 50; rotation: 10; }
            }

            transitions: Transition {
                from: ""; to: "down"; reversible: true
                ParallelAnimation {
                    NumberAnimation { properties: "y,rotation"; duration: 100; easing.type: Easing.InOutQuad }
                }
            }
        }
        Rectangle {
            id:exitbutton
            property color onHoverColor: Qt.rgba(0.0, 0.0, 0.0, 0.9)
            property color defaultColor: Qt.rgba(0.0, 0.0, 0.0, 0.5)
            anchors.bottom: parent.bottom
            width: 100;
            height: 50;
            radius: 20;
            color: defaultColor
            border.color: defaultColor
            border.width: 4
            Text { anchors.centerIn: parent; text: "Quit"; color: "white";font.pixelSize: 18; }

            MouseArea {
                id: mouseAreaexit;
                anchors.fill: parent ;
                hoverEnabled: true;
                onEntered:{ parent.color = parent.onHoverColor;parent.border.color = parent.onHoverColor;}
                onExited: {parent.color = parent.defaultColor;parent.border.color = parent.defaultColor}
                onClicked: Qt.quit();
            }
        }
        states: State {
            name: "down"; when: mouseAreaexit.containsMouse == true
            PropertyChanges { target: exitbutton; y: 50; rotation: 10; }
        }
        transitions: Transition {
            from: ""; to: "down"; reversible: true
            ParallelAnimation {
                NumberAnimation { properties: "y,rotation"; duration: 100; easing.type: Easing.InOutQuad }
            }
        }
    }


}
}
