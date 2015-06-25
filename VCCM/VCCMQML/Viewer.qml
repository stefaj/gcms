import QtQuick 2.4
import QMLOpenGL 1.0
import QtGraphicalEffects 1.0
import QtQuick.Window 2.0

Item {
    width: 640
    height: 480
    property color onHoverColor: Qt.rgba(0.1, 0.1, 1.0, 0.75)
    property color defaultColor: Qt.rgba(0.1, 0.1, 1.0, 0.5)
    property int iconsize: 64

    OpenGL {

        SequentialAnimation on t {
            NumberAnimation { to: 12; duration: 12000; easing.type: Easing.InQuad }
            NumberAnimation { to: 0; duration: 12000; easing.type: Easing.OutQuad }
            loops: Animation.Infinite
            running: true
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
