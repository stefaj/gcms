import QtQuick 2.0
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
   /* Grid {
         anchors.bottom: parent.bottom
         anchors.margins: 10
         anchors.leftMargin: 10
         anchors.rightMargin: 10
         x:10
         columns: 10
         spacing: 2
         Rectangle { color: defaultColor; width: iconsize; height: iconsize;
          MouseArea {anchors.fill: parent ;hoverEnabled: true; onEntered:{ parent.color = onHoverColor;parent.border.color = onHoverColor;}onExited: {parent.color = defaultColor;parent.border.color = defaultColor}}}
         Rectangle { color: defaultColor; width: iconsize; height: iconsize;
          MouseArea {anchors.fill: parent ;hoverEnabled: true; onEntered:{ parent.color = onHoverColor;parent.border.color = onHoverColor;}onExited: {parent.color = defaultColor;parent.border.color = defaultColor}}}
         Rectangle { color: defaultColor; width: iconsize; height: iconsize;
          MouseArea {anchors.fill: parent ;hoverEnabled: true; onEntered:{ parent.color = onHoverColor;parent.border.color = onHoverColor;}onExited: {parent.color = defaultColor;parent.border.color = defaultColor}}}
         Rectangle { color: defaultColor; width: iconsize; height: iconsize;
          MouseArea {anchors.fill: parent ;hoverEnabled: true; onEntered:{ parent.color = onHoverColor;parent.border.color = onHoverColor;}onExited: {parent.color = defaultColor;parent.border.color = defaultColor}}}
         Rectangle { color: defaultColor; width: iconsize; height: iconsize;
          MouseArea {anchors.fill: parent ;hoverEnabled: true; onEntered:{ parent.color = onHoverColor;parent.border.color = onHoverColor;}onExited: {parent.color = defaultColor;parent.border.color = defaultColor}}}
         Rectangle { color: defaultColor; width: iconsize; height: iconsize;
          MouseArea {anchors.fill: parent ;hoverEnabled: true; onEntered:{ parent.color = onHoverColor;parent.border.color = onHoverColor;}onExited: {parent.color = defaultColor;parent.border.color = defaultColor}}}
         Rectangle { color: defaultColor; width: iconsize; height: iconsize;
          MouseArea {anchors.fill: parent ;hoverEnabled: true; onEntered:{ parent.color = onHoverColor;parent.border.color = onHoverColor;}onExited: {parent.color = defaultColor;parent.border.color = defaultColor}}}
         Rectangle { color: defaultColor; width: iconsize; height: iconsize;
          MouseArea {anchors.fill: parent ;hoverEnabled: true; onEntered:{ parent.color = onHoverColor;parent.border.color = onHoverColor;}onExited: {parent.color = defaultColor;parent.border.color = defaultColor}}}
         Rectangle { color: defaultColor; width: iconsize; height: iconsize;
          MouseArea {anchors.fill: parent ;hoverEnabled: true; onEntered:{ parent.color = onHoverColor;parent.border.color = onHoverColor;}onExited: {parent.color = defaultColor;parent.border.color = defaultColor}}}
         Rectangle { color: defaultColor; width: iconsize; height: iconsize;
          MouseArea {anchors.fill: parent ;hoverEnabled: true; onEntered:{ parent.color = onHoverColor;parent.border.color = onHoverColor;}onExited: {parent.color = defaultColor;parent.border.color = defaultColor}}}
     }*/

}
