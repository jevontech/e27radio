/* 
 * File:   E27radio.cpp
 * Author: Jeroen Vennegoor op Nijhuis
 *
 * 
 * 
 */


#include <iostream>
using namespace std;

#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/AutoPtr.h"
#include "Poco/Logger.h"

using Poco::Util::ServerApplication;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;
using Poco::AutoPtr;
using Poco::Logger;

#include <QtXml/QtXml>
#include <QtDBus/QtDBus>
#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include "StateMachine.h"

class E27radio : public ServerApplication {
private:
    StateMachine* statemachine;
public:

    E27radio() {
        //Logger::root().setLevel(Poco::Message::PRIO_DEBUG);
        statemachine = new StateMachine();
    }

    ~E27radio() {
        delete statemachine;
    }


protected:

    void initialize(Application& self) {
        loadConfiguration(); // load default configuration files, if present
        Application::initialize(self);
    }

    void uninitialize() {
        Application::uninitialize();
    }

    void reinitialize(Application& self) {
        Application::reinitialize(self);
    }

    int main(const std::vector<std::string>& args) {
        logger().information("Welcome to E27radio");
        logger().information("Press CTRL-C to quit");
        waitForTerminationRequest();
        return Application::EXIT_OK;
    }

private:

};

int main(int argc, char** argv) {
    QCoreApplication qapp(argc, argv);
    E27radio app;
    return app.run(argc, argv);
}
