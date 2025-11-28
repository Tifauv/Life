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

    World {
        id: world
    }

    pageStack.initialPage: Kirigami.Page {
        id: mainPage


        ColumnLayout {
            id: mainLayout

            anchors.fill: parent

            RowLayout {
                id: actionsLayout

                Controls.Button {
                    id: stepBtn

                    text: "\u23EF"
                    Controls.ToolTip {
                        visible: stepBtn.hovered
                        text: i18n("One step")
                    }

                    onClicked: {
                        mainPage.state = "stepping";
                    }
                }

                Controls.Button {
                    id: playBtn

                    text: "\u23F5"
                    Controls.ToolTip.visible: playBtn.hovered
                    Controls.ToolTip.text: i18n("Play")

                    onClicked: {
                        if (mainPage.state == "playing")
                            mainPage.state = "";
                        else
                            mainPage.state = "playing";
                    }
                }

                Controls.Slider {
                    id: speedSld

                    from: 0
                    value: 250
                    to: 1000

                    stepSize: 50

                    Layout.fillWidth: true

                    Controls.ToolTip {
                        parent: speedSld.handle
                        visible: speedSld.pressed
                        text: speedSld.value.toFixed(1) + " ms"
                    }
                }
            }

            WorldView {
                id: view
            }

            RowLayout {
                id: controlsLayout

                Controls.Label {
                    text: "Zoom: "
                }

                Controls.Slider {
                    id: zoomSld

                    from: 1
                    value: 1
                    to: 5

                    stepSize: 1

                    property int zoomFactor: 1 << (value.toFixed(1) - 1)

                    Layout.fillWidth: true

                    Controls.ToolTip {
                        parent: zoomSld.handle
                        visible: zoomSld.pressed
                        text: "\u2715" + (1 << (zoomSld.value.toFixed(1) -1))
                    }
                }

                Controls.Label {
                    id: zoomLbl
                    text: "\u27151"
                }
            }
        }

        states: [
            State {
                name: "playing"

                PropertyChanges { target: stepBtn; enabled: false }

                PropertyChanges {
                    target: playBtn
                    text: "\u23F8"
                    Controls.ToolTip.text: i18n("Pause")
                }
            },
            State {
                name: "stepping"

                PropertyChanges { target: stepBtn;  enabled: false }
                PropertyChanges { target: playBtn;  enabled: false }
                PropertyChanges { target: speedSld; enabled: false }
            }
        ]
    }
}
