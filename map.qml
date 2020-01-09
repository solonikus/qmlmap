import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtPositioning 5.12
import QtLocation 5.12

Item {
    id: item
    visible: true

    signal geocodecheck(int err)

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
        id: map
        anchors.fill: parent
        objectName: "map1"
        plugin: mapPlugin
        center: QtPositioning.coordinate(55.7507, 37.6175)
        zoomLevel: 10
        MapItemView {
            id: map111
            model: listmodel
            visible: false
            delegate:     MapCircle {
                id: circle
                visible: true
                center: QtPositioning.coordinate(listmodel.get(0).Lat , listmodel.get(0).Lon)
                radius: listmodel.get(1).Rad
                color: 'blue'
                border.width: 1
            }
        }
        ListModel {
            id: listmodel
            ListElement{
                Lat: 0
                Lon: 0
            }
            ListElement{
                Rad: 500.0
            }
        }

        GeocodeModel {
            id: geocodeModel
            plugin: mapPlugin
            autoUpdate: false
            onLocationsChanged: {
                if (count){
                    map.center = get(0).coordinate;
                    listmodel.setProperty(0, "Lat", get(0).coordinate.latitude);
                    listmodel.setProperty(0, "Lon", get(0).coordinate.longitude);
                    map111.visible = true;
                    }
                }
            }
        Column {
            x:10
            y:10
            Text {
                    id: latlon
                    text: "lat: %1; lon:%2".arg(map.center.latitude).arg(map.center.longitude)
                }
            Text {
                    id: zoom
                    text: "zoom: " + map.zoomLevel.toFixed(2)
                }
            Text {
                    id: crc
                    text: "crc: " + listmodel.get(1).Rad.toFixed(2)
                }
            }
        MouseArea{
            anchors.fill: map
            onWheel: {
                wheel.accepted = false
                listmodel.setProperty(1, "Rad", (map.zoomLevel * 10))
            }
        }
        }
    function search(str)
        {
        geocodeModel.query = str
        geocodeModel.update()
        geocodecheck(geocodeModel.status)
        }
    function clear()
        {
            map111.visible = false;
        }
    }
