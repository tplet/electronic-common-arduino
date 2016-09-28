//
// Created by Thibault PLET on 28/09/2016.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_ARDUINOAPPLICATION_H
#define COM_OSTERES_AUTOMATION_ARDUINO_ARDUINOAPPLICATION_H

#include <com/osteres/automation/Application.h>
#include <com/osteres/automation/arduino/memory/Value.h>

using com::osteres::automation::Application;
using com::osteres::automation::arduino::memory::Value;

namespace com
{
    namespace osteres
    {
        namespace automation
        {
            namespace arduino
            {
                class ArduinoApplication : public Application
                {
                public:
                    /**
                     * Constructor
                     */
                    ArduinoApplication(int addressIdentifier)
                    {
                        this->identifier = new Value<unsigned char>(addressIdentifier);
                    }

                    /**
                     * Destructor
                     */
                    ~ArduinoApplication()
                    {
                        // Remove identifier
                        if (this->identifier != NULL) {
                            delete this->identifier;
                            this->identifier = NULL;
                        }
                    }

                protected:
                    /**
                     * EEProm location for sensor identifier
                     */
                    Value<unsigned char> * identifier = NULL;
                };
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_ARDUINO_ARDUINOAPPLICATION_H
