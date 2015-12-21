/* 
 * File:   BluetoothAdapter.cpp
 * Author: Jeroen Vennegoor op Nijhuis
 * 
 * Created on December 5, 2015, 11:28 AM
 */

#include "BluetoothAdapter.h"

BluetoothAdapter::BluetoothAdapter() :
bus(QDBusConnection::systemBus()) {
    interface = new QDBusInterface("org.bluez", "/org/bluez/hci0", "org.bluez.Adapter1", bus);
}

QString BluetoothAdapter::address() {
    return interface->property("Address").toString();
}

vector<BluetoothDevicePointer> BluetoothAdapter::getDevices() {
    devices.resize(0);
    QDomDocument doc("reply");
    QDBusMessage reply;
    QDBusInterface interface2("org.bluez", "/org/bluez/hci0",
            "org.freedesktop.DBus.Introspectable", bus);
    reply = interface2.call("Introspect");
    QByteArray bytes = reply.arguments().first().toByteArray();
    doc.setContent(bytes);
    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.firstChild();
    while (!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if (!e.isNull()) {

            if (e.tagName() == "node") {
                //qDebug() << qPrintable(e.attribute("name")) ;
                QString name = e.attribute("name");
                devices.push_back(BluetoothDevicePointer(new BluetoothDevice(name)));
            }
        }
        n = n.nextSibling();
    }

    return devices;

}

void BluetoothAdapter::printDevices() {
    QDomDocument doc("reply");
    QDBusMessage reply;

    QDBusInterface interface2("org.bluez", "/org/bluez/hci0",
            "org.freedesktop.DBus.Introspectable", bus);
    reply = interface2.call("Introspect");
    QByteArray bytes = reply.arguments().first().toByteArray();
    doc.setContent(bytes);

    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();
    while (!n.isNull()) {
        QDomElement e = n.toElement(); 
        if (!e.isNull()) {
            if (e.tagName() == "node") {
                qDebug() << qPrintable(e.attribute("name"));
            }
        }
        n = n.nextSibling();
    }


}

BluetoothAdapter::~BluetoothAdapter() {
    delete interface;
}

