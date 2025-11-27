import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import QtGraphs
import org.kde.kirigami as Kirigami

Item {
    id: mainView
    width: 800
    height: 180

    Rectangle {
        id: background

        anchors.fill:parent

        color: Kirigami.Theme.backgroundColor
    }

    GridLayout {
        id: changesGraphLayout

        anchors.fill: parent

        columns: 2
        uniformCellWidths: true

        rowSpacing: 0

        Controls.Label {
            id: changesGraphTitle

            Layout.leftMargin: changesGraphView.marginLeft

            text: "Changes"
        }

        Controls.Label {
            id: durationGraphTitle

            Layout.leftMargin: durationGraphView.marginLeft

            text: "Duration"
        }

        GraphsView {
            id: changesGraphView

            Layout.fillWidth: true
            Layout.fillHeight: true

            theme: GraphsTheme {
                theme: GraphsTheme.Theme.BlueSeries
                labelBorderVisible: true
                labelBackgroundVisible: true
            }

            axisX: ValueAxis {
                titleText: "Steps"
                min: 0
                max: Math.max(200, graph.changesSeries.count)
                subTickCount: 0
                subGridVisible: false
            }

            axisY: ValueAxis {
                min: 0
                max: Math.max(1, graph.maxChanges * 1.05)
                subTickCount: 0
                labelFormat: "%g"
            }

            seriesList: [ graph.changesSeries ]
        }

        GraphsView {
            id: durationGraphView

            Layout.fillWidth: true
            Layout.fillHeight: true

            theme: GraphsTheme {
                theme: GraphsTheme.Theme.OrangeSeries
                labelBorderVisible: true
                labelBackgroundVisible: true
            }

            axisX: ValueAxis {
                titleText: "Steps"
                min: 0
                max: Math.max(200, graph.durationSeries.count)
                subTickCount: 0
                subGridVisible: false
            }

            axisY: ValueAxis {
                min: 0
                max: Math.max(1, graph.maxDuration * 1.05)
                labelFormat: "%g ms"
            }

            seriesList: [ graph.durationSeries ]
        }
    }
}
