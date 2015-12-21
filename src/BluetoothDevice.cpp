/* 
 * File:   BluetoothDevice.cpp
 * Author: jeroen
 * 
 * Created on December 5, 2015, 2:29 PM
 */

#include "BluetoothDevice.h"

BluetoothDevice::BluetoothDevice(QString name) : name(name), bus(QDBusConnection::systemBus()) {
    interface = new QDBusInterface("org.bluez", "/org/bluez/hci0/" + name, "org.bluez.Device1", bus);
}

QString BluetoothDevice::getName() {
    return name;
}

bool BluetoothDevice::isConnected() {
    return interface->property("Connected").toBool();
}

void BluetoothDevice::connect() {
    interface->call("Connect");
}

void BluetoothDevice::disconnect() {
    interface->call("Disconnect");
}

BluetoothDevice::~BluetoothDevice() {
    disconnect();
    delete interface;
}

