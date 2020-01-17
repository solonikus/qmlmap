import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtPositioning 5.12
import QtLocation 5.12

Item {
    id: item
    visible: true

    signal geocodecheck(int err)
    signal addfavorit(double x, double y)

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
            ListElement{
                x: 0
                y: 0
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
            acceptedButtons: Qt.AllButtons
            onClicked: {
                if (mouse.button == Qt.RightButton)
                {
                    contmenu.popup(mouse.x, mouse.y)
                    listmodel.setProperty(2, "x", map.toCoordinate(Qt.point(mouse.x, mouse.y)).latitude);
                    listmodel.setProperty(2, "y", map.toCoordinate(Qt.point(mouse.x, mouse.y)).longitude);
                }
                else
                    contmenu.close()
            }
            onPressed: {
                if (mouse.button == Qt.LeftButton)
                    contmenu.close()
            }

            onWheel: {
                wheel.accepted = false
                if (map.zoomLevel >= 17)
                    listmodel.setProperty(1, "Rad", (3))
                else if (map.zoomLevel >= 16)
                    listmodel.setProperty(1, "Rad", (10))
                else if (map.zoomLevel >= 15)
                    listmodel.setProperty(1, "Rad", (20))
                else if (map.zoomLevel >= 14)
                    listmodel.setProperty(1, "Rad", (40))
                else if (map.zoomLevel >= 13)
                    listmodel.setProperty(1, "Rad", (70))
                else if (map.zoomLevel >= 12)
                    listmodel.setProperty(1, "Rad", (100))
                else if (map.zoomLevel >= 11)
                    listmodel.setProperty(1, "Rad", (200))
                else if (map.zoomLevel >= 10)
                    listmodel.setProperty(1, "Rad", (400))
                else if (map.zoomLevel >= 9)
                    listmodel.setProperty(1, "Rad", (800))
                else if (map.zoomLevel >= 8)
                    listmodel.setProperty(1, "Rad", (1500))
                else if (map.zoomLevel >= 7)
                    listmodel.setProperty(1, "Rad", (3000))
                else if (map.zoomLevel >= 6)
                    listmodel.setProperty(1, "Rad", (6000))
                else if (map.zoomLevel >= 5)
                    listmodel.setProperty(1, "Rad", (12000))
                else if (map.zoomLevel >= 4)
                    listmodel.setProperty(1, "Rad", (20000))
                else if (map.zoomLevel >= 3)
                    listmodel.setProperty(1, "Rad", (40000))
                else if (map.zoomLevel >= 2)
                    listmodel.setProperty(1, "Rad", (80000))
                else if (map.zoomLevel >= 1)
                    listmodel.setProperty(1, "Rad", (200000))
            }
        }
        Menu {
            id: contmenu
            Action {
                text: "Добавить в избранное"
                onTriggered: {addfavorit(listmodel.get(2).x, listmodel.get(2).y)}
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
