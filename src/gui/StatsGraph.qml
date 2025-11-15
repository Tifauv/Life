import QtQuick
import QtQuick.Layouts
import QtGraphs

Item {
    id: mainView
    width: 800
    height: 180

    GraphsView {
        id: changesGraphView

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        width: parent.width * 0.5

        theme: GraphsTheme {
            theme: GraphsTheme.Theme.BlueSeries
            labelBorderVisible: true
            labelBackgroundVisible: true
        }

        axisX: ValueAxis {
            min: 0
            max: Math.max(200, graph.changesSeries.count)
            subTickCount: 5
            subGridVisible: false
        }

        axisY: ValueAxis {
            min: 0
            max: Math.max(1, graph.maxChanges * 1.05)
            subTickCount: 0
        }

        seriesList: [ graph.changesSeries ]
    }

    GraphsView {
        id: durationGraphView

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        width: parent.width * 0.5

        theme: GraphsTheme {
            theme: GraphsTheme.Theme.BlueSeries
            labelBorderVisible: true
            labelBackgroundVisible: true
        }

        axisX: ValueAxis {
            min: 0
            max: Math.max(200, graph.durationSeries.count)
            subTickCount: 5
            subGridVisible: false
        }

        axisY: ValueAxis {
            min: 0
            max: Math.max(1, graph.maxDuration * 1.05)
            subTickCount: 0
        }

        seriesList: [ graph.durationSeries ]
    }
}
