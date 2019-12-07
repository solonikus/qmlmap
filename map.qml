import QtQuick 2.12
import QtQuick.Window 2.12
import QtPositioning 5.12
import QtLocation 5.12

Item {
    visible: true

    Plugin {
        id: mapPlugin
        name: "osm" // "mapboxgl", "esri", ...
        // specify plugin parameters if necessary
        // PluginParameter {
        //     name:
        //     value:
        // }
    }

    Map {
        anchors.fill: parent
        objectName: "map1"
        plugin: mapPlugin
        center: QtPositioning.coordinate(59.91, 10.75) // Oslo
        zoomLevel: 14
    }
}
