/* 
 * File:   BluetoothAdapter.h
 * Author: Jeroen Vennegoor op Nijhuis
 *
 * Created on December 5, 2015, 11:28 AM
 */

#ifndef BLUETOOTHADAPTER_H
#define	BLUETOOTHADAPTER_H

#include <QtXml/QtXml>
#include <QtDBus/QtDBus>
#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include <vector>
#include "BluetoothDevice.h"

using namespace std;

class BluetoothAdapter : public QObject {
    Q_OBJECT
public:
    BluetoothAdapter();
    QString address();
    void printDevices();
    vector<BluetoothDevicePointer> getDevices();

    virtual ~BluetoothAdapter();
private:

    QDBusConnection bus;
    QDBusInterface* interface;
    vector<BluetoothDevicePointer> devices;
};

#endif	/* BLUETOOTHADAPTER_H */

