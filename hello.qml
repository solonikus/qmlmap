import QtQuick 2.5
import QtQuick.Controls 2.1

Item {
id: item1
width: 400
height: 400
property alias text1Text: text1.text

Text {
    id: text1
    width: 400
    height: 29
    color: "red"
    text: "This text should change..."
    font.pixelSize: 12
}

}
