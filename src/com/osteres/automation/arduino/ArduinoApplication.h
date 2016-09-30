//
// Created by Thibault PLET on 28/09/2016.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_ARDUINOAPPLICATION_H
#define COM_OSTERES_AUTOMATION_ARDUINO_ARDUINOAPPLICATION_H

#include <com/osteres/automation/Application.h>
#include <com/osteres/automation/memory/Property.h>
#include <com/osteres/automation/arduino/memory/StoredProperty.h>

using com::osteres::automation::Application;
using com::osteres::automation::memory::Property;
using com::osteres::automation::arduino::memory::StoredProperty;

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
                     *
                     * @param type Sensor type identifier
                     */
                    ArduinoApplication(unsigned char type)
                    {
                        // Sensor identifier
                        this->propertyIdentifier = new StoredProperty<unsigned char>();
                        this->propertyIdentifier->setAddress(0x00);

                        // Sensor type
                        this->propertyType = new Property<unsigned char>(type);
                    }

                    /**
                     * Destructor
                     */
                    ~ArduinoApplication()
                    {
                        // Remove sensor identifier property
                        if (this->propertyIdentifier != NULL) {
                            delete this->propertyIdentifier;
                            this->propertyIdentifier = NULL;
                        }

                        // Remove sensor type identifier property
                        if (this->propertyType != NULL) {
                            delete this->propertyType;
                            this->propertyType = NULL;
                        }
                    }

                    /**
                     * Get sensor identifier property
                     */
                    StoredProperty * getPropertyIdentifier()
                    {
                        return this->propertyIdentifier;
                    }

                    /**
                     * Get sensor type identifier property
                     */
                    Property * getPropertyType()
                    {
                        return this->propertyType;
                    }

                protected:
                    /**
                     * Sensor type identifier property
                     */
                    Property<unsigned char> * propertyType = NULL;

                    /**
                     * Sensor identifier property
                     */
                    StoredProperty<unsigned char> * propertyIdentifier = NULL;
                };
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_ARDUINO_ARDUINOAPPLICATION_H
