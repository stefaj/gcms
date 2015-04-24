import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0

/*ButtonStyle {
        background: Rectangle {
            property color onHoverColor: Qt.rgba(1.0, 1.0, 1.0, 0.9)
            property color defaultColor: Qt.rgba(1.0, 1.0, 1.0, 0.5)
            implicitWidth: 100
            implicitHeight: 50
            //border.width: control.activeFocus ? 2 : 1
            //border.color: "#888"
            color: defaultColor
            border.color: defaultColor
            radius: 20

            label: Text { anchors.centerIn: parent; color: "white";font.pixelSize: 18;}
            gradient: Gradient {
                GradientStop { position: 0 ; color: control.pressed ? "#ccc" : onHoverColor}
                GradientStop { position: 1 ; color: control.pressed ? "#aaa" : defaultColor }
            }




       }
 }*/

Style{
        Rectangle {
            id: button
            property color onHoverColor: Qt.rgba(1.0, 1.0, 1.0, 0.9)
            property color defaultColor: Qt.rgba(1.0, 1.0, 1.0, 0.5)
            anchors.top: parent.top
            width: 100;
            height: 50;
            radius: 1;
            color: defaultColor
            border.color: defaultColor
            border.width: 1
            Text { anchors.centerIn: parent; text: "hgkghjkgk"; color: "white";font.pixelSize: 18;}
            /*MouseArea {
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
            }*/
        }
}
