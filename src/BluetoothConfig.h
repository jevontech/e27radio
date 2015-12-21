/* 
 * File:   BluetoothConfig.h
 * Author: Jeroen Vennegoor op Nijhuis
 *
 * Created on December 4, 2015, 8:13 PM
 */

#ifndef BLUETOOTH_H
#define	BLUETOOTH_H


#include "Poco/Logger.h"
#include "Poco/LogStream.h"
#include <QtDBus/QtDBus>
#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include "BluetoothAdapter.h"
#include "BluetoothDevice.h"

class BluetoothConfig : public QObject {
    Q_OBJECT
public:
    BluetoothConfig();
    virtual ~BluetoothConfig();
    void configure();
    void disconnect();

public slots:
    void startScan();
    void scanFinished();

private:
    Poco::Logger& logger;
    BluetoothAdapter* adapter;
    BluetoothDevicePointer selectedDevice;

};

#endif	/* BLUETOOTH_H */

