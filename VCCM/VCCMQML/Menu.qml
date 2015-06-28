import QtQuick 2.0
import QtQuick.Controls.Styles 1.3
import QtQuick.Controls 1.3
import QtQuick.Window 2.0
import QMLOpenGL 1.0
import QtGraphicalEffects 1.0
import "qrc:/VCCMQML"
Item {

    id:tree
    width: 450
    height: 800
    Loader {id:gamestate;focus: true;width: tree.width; height: tree.height}
    Loader {id:mainmenu;width: tree.width;height: tree.height
    Image {id: background;anchors.fill: parent;source: "Texture0";fillMode: Image.Stretch;opacity: 1}

    Rectangle {
        anchors.centerIn: parent
        width: 100;
        height: 110;
        color: Qt.rgba(0.0, 0.0, 0.0, 0.0)
        Grid {
                id: destination
                x: 0; y:0; anchors.bottomMargin: 4
                rows: 6; columns: 1; spacing: 3
                Cell{display:"View";onClicked:{gamestate.source ="Viewer";mainmenu.visible = false;}}
                Cell{onClicked:{gamestate.source ="Viewer";mainmenu.visible = false;}}
                Cell{onClicked:{gamestate.source ="Viewer";mainmenu.visible = false;}}
                Cell{onClicked:{gamestate.source ="Viewer";mainmenu.visible = false;}}
                Cell{onClicked:{gamestate.source ="Viewer";mainmenu.visible = false;}}
                Cell{display:"Exit";onClicked:{Qt.quit();}}
            }
        }
    }
}

