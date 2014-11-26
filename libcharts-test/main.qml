import QtQuick 2.0
import QtQuick.Controls 1.0
import com.develer.libcharts 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property var anArray: [0, 100, 90, 10]

    LineSeries {
        id: series
        dataSource: anArray
    }

    LineSeries {
        id: series2
        dataSource: [100, 22, 80.3, 17, 61, 12, 18, -6]
        scaleMinimum: -10
        scaleMaximum: 200
    }

    Text {
        id: scaleTop
        anchors.top: background.top
        anchors.right: background.left
        text: chart.model[0].scaleMaximum
    }
    Text {
        id: scaleBottom
        anchors.baseline: background.bottom
        anchors.right: background.left
        text: chart.model[0].scaleMinimum
    }

    Rectangle {
        id: background
        color: "#fdf9ba"
        border.color: "black"
        anchors.fill: chart
    }

    LineChart {
        id: chart
        clip: true
        width: 200
        height: 200
        anchors.centerIn: parent
        model: series
        color: "red"
        lineWidth: 2
    }

    Button {
        onClicked: {
            if (chart.model[0] === series) {
                chart.model = [series2]
                chart.color = "green"
                chart.lineWidth = 20
            }
            else {
                chart.color = "red"
                chart.model = [series]
                chart.lineWidth = 1
            }
        }

        text: "Switch"
    }
}
