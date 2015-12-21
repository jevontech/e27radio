/* 
 * File:   BluetoothDevice.h
 * Author: Jeroen Vennegoor op Nijhuis
 *
 * Created on December 5, 2015, 2:29 PM
 */

#ifndef BLUETOOTHDEVICE_H
#define	BLUETOOTHDEVICE_H

#include <QtXml/QtXml>
#include <QtDBus/QtDBus>
#include <QtCore/QDebug>
#include <QtCore/QStringList>

class BluetoothDevice {
public:
    BluetoothDevice(QString name);

    void connect();
    void disconnect();

    QString getName();
    bool isConnected();

    virtual ~BluetoothDevice();
private:
    QString name;
    QDBusConnection bus;
    QDBusInterface* interface;
};

typedef QSharedPointer<BluetoothDevice> BluetoothDevicePointer;

#endif	/* BLUETOOTHDEVICE_H */

