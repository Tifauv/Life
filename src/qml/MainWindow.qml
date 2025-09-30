import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

/**
 * Main window of the Life application.
 */
Kirigami.ApplicationWindow {
    id: root

    title: i18nc("@title:window", "Life")

    width: 600
    height: 800

    pageStack.initialPage: Kirigami.Page {

        ColumnLayout {
            RowLayout {
                id: actionsLayout

                Controls.Button {
                    id: stepBtn
                    text: " >| "
                }

                Controls.Button {
                    id: playBtn
                    text: " > "
                }

                Controls.Slider {
                    id: speedSld
                }
            }

            WorldItem {
                id: worldView
            }

            RowLayout {
                id: controlsLayout

                Controls.Label {
                    text: "Zoom: "
                }

                Controls.Slider {
                    id: zoomSld
                }

                Controls.Label {
                    id: zoomLbl
                    text: "x1"
                }
            }
        }
    }
}
