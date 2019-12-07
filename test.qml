import QtQuick 2.5
import QtQuick.Controls 2.1

Item {
id: item1
width: 400
height: 400
    Text {
        id: text1
        objectName: "text1"
        width: 400
        height: 29
        color: "red"
        text: "This text should change..."
        font.pixelSize: 12
        }

}
