//
// Created by Thibault PLET on 28/09/2016.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_ARDUINOAPPLICATION_H
#define COM_OSTERES_AUTOMATION_ARDUINO_ARDUINOAPPLICATION_H

#include <com/osteres/automation/Application.h>
#include <com/osteres/automation/memory/Property.h>
#include <com/osteres/automation/arduino/memory/StoredProperty.h>
#include <com/osteres/automation/transmission/Transmitter.h>
#include <com/osteres/automation/arduino/action/SensorIdentifierAction.h>
#include <com/osteres/automation/sensor/Identity.h>
#include <com/osteres/automation/arduino/action/ArduinoActionManager.h>

using com::osteres::automation::Application;
using com::osteres::automation::memory::Property;
using com::osteres::automation::arduino::memory::StoredProperty;
using com::osteres::automation::transmission::Transmitter;
using com::osteres::automation::arduino::action::SensorIdentifierAction;
using com::osteres::automation::sensor::Identity;
using com::osteres::automation::arduino::action::ArduinoActionManager;

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
                    ArduinoApplication(unsigned char type, Transmitter * transmitter)
                    {
                        // Sensor identifier
                        this->propertyIdentifier = new StoredProperty<unsigned char>();
                        this->propertyIdentifier->setAddress(0x00);

                        // Sensor type
                        this->propertyType = new Property<unsigned char>(type);

                        // Transmitter
                        this->transmitter = transmitter;
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

                        // Remove action manager
                        if (this->actionManager != NULL) {
                            delete this->actionManager;
                            this->actionManager = NULL;
                        }

                        // Remove sensor identifier action
                        if (this->actionSensorIdentifier != NULL) {
                            delete this->actionSensorIdentifier;
                            this->actionSensorIdentifier = NULL;
                        }

                    }

                    /**
                     * Setup application
                     */
                    virtual void setup()
                    {
                        // Setup transmitter properties
                        this->transmitter->setPropertySensorType(this->getPropertyType());
                        this->transmitter->setPropertySensorIdentifier(this->getPropertyIdentifier());
                    }

                    /**
                     * Request to master to obtain an new identifier
                     */
                    void requestForAnIdentifier()
                    {
                        SensorIdentifierAction * action = this->getActionSensorIdentifier();

                        // Add support for identifier response command to action manager
                        if (this->hasActionManager()) {
                            this->getActionManager()->setActionSensorIdentifier(action);
                        }

                        // Request
                        action->request();
                    }

                    /**
                     * Flag to indicate if an identifier is needed for this sensor
                     */
                    bool isNeedIdentifier()
                    {
                        return this->getPropertyIdentifier()->get() == 0;
                    }

                    /**
                     * Get sensor identifier property
                     */
                    StoredProperty<unsigned char> * getPropertyIdentifier()
                    {
                        return this->propertyIdentifier;
                    }

                    /**
                     * Get sensor type identifier property
                     */
                    Property<unsigned char> * getPropertyType()
                    {
                        return this->propertyType;
                    }

                    /**
                     * Get transmitter
                     */
                    Transmitter * getTransmitter()
                    {
                        return this->transmitter;
                    }

                    /**
                     * Get action manager for arduino
                     */
                    ArduinoActionManager * getActionManager()
                    {
                        return this->actionManager;
                    }

                    /**
                     * Set action manager for arduino
                     */
                    void setActionManager(ArduinoActionManager * actionManager)
                    {
                        this->actionManager = actionManager;
                    }

                    /**
                     * Flag to indicate if action manager is defined
                     */
                    bool hasActionManager()
                    {
                        return this->actionManager != NULL;
                    }

                    /**
                     * Get sensor identifier action
                     *
                     * Generate instance if not exist yet
                     */
                    SensorIdentifierAction * getActionSensorIdentifier()
                    {
                        if (this->actionSensorIdentifier == NULL) {
                            this->actionSensorIdentifier = new SensorIdentifierAction(
                                this->getPropertyType(),
                                this->getPropertyIdentifier(),
                                Identity::MASTER,
                                this->getTransmitter()
                            );
                        }

                        return this->actionSensorIdentifier;
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

                    /**
                     * Transmitter
                     */
                    Transmitter * transmitter = NULL;

                    /**
                     * Action manager for Arduino
                     */
                    ArduinoActionManager * actionManager = NULL;

                    /**
                     * Sensor identifier action
                     */
                    SensorIdentifierAction * actionSensorIdentifier = NULL;

                };
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_ARDUINO_ARDUINOAPPLICATION_H
