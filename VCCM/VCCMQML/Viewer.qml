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

}
