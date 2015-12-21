/* 
 * File:   BluetoothConfig.cpp
 * Author: Jeroen Vennegoor op Nijhuis
 * 
 * Created on December 4, 2015, 8:13 PM
 */

#include "BluetoothConfig.h"

BluetoothConfig::BluetoothConfig() : logger(Poco::Logger::get("BluetoothConfig")) {

        QDBusConnection bus = QDBusConnection::systemBus();
        if (!bus.isConnected()) {
            fprintf(stderr, "Cannot connect to the D-Bus system bus.\n");
        }
}

BluetoothConfig::~BluetoothConfig() {

}

void BluetoothConfig::configure() {
        adapter = new BluetoothAdapter();
        qDebug() << "Bluetooth adapter address=" << adapter->address();
        adapter->printDevices();
        
        vector<BluetoothDevicePointer> devices = adapter->getDevices();
        
        if (devices.size()>0) {
            //for now , just pick the first Bluetooth device available
            selectedDevice=devices[0];
            selectedDevice->connect();
            qDebug() << "Connect to device: "<< devices[0]->getName();
        }
        else
        {
              qDebug() << "No bluetooth devices found" ;
        }
    
}

void BluetoothConfig::disconnect(){
    selectedDevice->connect();
}

void BluetoothConfig::startScan() {
}

void BluetoothConfig::scanFinished() {
}

