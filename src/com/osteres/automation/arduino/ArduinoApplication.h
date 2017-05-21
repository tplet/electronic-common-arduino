//
// Created by Thibault PLET on 28/09/2016.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_ARDUINOAPPLICATION_H
#define COM_OSTERES_AUTOMATION_ARDUINO_ARDUINOAPPLICATION_H

#include <RTClib/RTClib.h>
#include <com/osteres/automation/Application.h>
#include <com/osteres/automation/memory/Property.h>
#include <com/osteres/automation/arduino/memory/StoredPropertyManager.h>
#include <com/osteres/automation/arduino/memory/StoredProperty.h>
#include <com/osteres/automation/transmission/Transmitter.h>
#include <com/osteres/automation/arduino/action/SensorIdentifierAction.h>
#include <com/osteres/automation/arduino/action/DateTimeAction.h>
#include <com/osteres/automation/sensor/Identity.h>
#include <com/osteres/automation/arduino/action/ArduinoActionManager.h>
#include <com/osteres/automation/arduino/action/TransmitBatteryLevelAction.h>
#include <com/osteres/automation/arduino/transmission/ArduinoRequester.h>
#include <com/osteres/automation/arduino/component/BatteryLevel.h>

using com::osteres::automation::Application;
using com::osteres::automation::memory::Property;
using com::osteres::automation::arduino::memory::StoredProperty;
using com::osteres::automation::arduino::memory::StoredPropertyManager;
using com::osteres::automation::transmission::Transmitter;
using com::osteres::automation::arduino::action::SensorIdentifierAction;
using com::osteres::automation::arduino::action::DateTimeAction;
using com::osteres::automation::sensor::Identity;
using com::osteres::automation::arduino::action::ArduinoActionManager;
using com::osteres::automation::arduino::action::TransmitBatteryLevelAction;
using com::osteres::automation::arduino::transmission::ArduinoRequester;
using com::osteres::automation::arduino::component::BatteryLevel;

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
                     * @param transmitter Transmitter
                     */
                    ArduinoApplication(unsigned char type, Transmitter * transmitter)
                    {
                        this->construct(type, transmitter);
                    }

                    /**
                     * Constructor
                     *
                     * @param type Sensor type identifier
                     * @param transmitter Transmitter
                     * @param rtc RTC for DateTime
                     */
                    ArduinoApplication(unsigned char type, Transmitter * transmitter, RTC_DS1307 * rtc)
                    {
                        this->construct(type, transmitter);

                        // RTC
                        this->setRTC(rtc);
                    }

                    /**
                     * Destructor
                     */
                    virtual ~ArduinoApplication()
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

                        // Remove date time action
                        if (this->actionDateTime != NULL) {
                            delete this->actionDateTime;
                            this->actionDateTime = NULL;
                        }

                        // Remove transmit battery level action
                        if (this->actionTransmitBatteryLevel != NULL) {
                            delete this->actionTransmitBatteryLevel;
                            this->actionTransmitBatteryLevel = NULL;
                        }

                    }

                    /**
                     * Global construct part
                     */
                    void construct(unsigned char type, Transmitter * transmitter)
                    {
                        // Sensor identifier then add to container
                        this->propertyIdentifier = new StoredProperty<unsigned char>();
                        StoredPropertyManager::configure(this->propertyIdentifier);

                        // Sensor type
                        this->propertyType = new Property<unsigned char>(type);

                        // Transmitter
                        this->transmitter = transmitter;
                    }

                    /**
                     * Setup application
                     */
                    virtual void setup()
                    {
                        // Setup transmitter properties
                        this->transmitter->setPropertySensorType(this->getPropertyType());
                        this->transmitter->setPropertySensorIdentifier(this->getPropertyIdentifier());

                        // RTC
                        if (this->hasRTC()) {
                            // Init
                            this->rtc->begin();
//                            this->rtc->adjust(DateTime(2016, 9, 21, 23, 23, 00));

                            // Forward to transmitter
                            static_cast<ArduinoRequester *>(this->transmitter->getRequester())->setRTC(this->getRTC());
                        }

                        // Add support for identifier response command to action manager
                        if (this->hasActionManager()) {
                            this->getActionManager()->setActionSensorIdentifier(this->getActionSensorIdentifier());
                        }
                    }

                    /**
                     * Request to server to obtain an new identifier
                     */
                    void requestForAnIdentifier()
                    {
                        SensorIdentifierAction * action = this->getActionSensorIdentifier();

                        // Request
                        action->request();
                    }

                    /**
                     * Request to update date time from server
                     */
                    void requestForDateTime()
                    {
                        // Only if RTC is available
                        if (this->hasRTC()) {
                            DateTimeAction * action = this->getActionDateTime();

                            // Add support for date time response command to action manager
                            if (this->hasActionManager()) {
                                this->getActionManager()->setActionDateTime(action);
                            }

                            // Request
                            action->request();
                        }
                    }

                    /**
                     * Request to send battery level to server
                     */
                    void requestForBatteryLevel()
                    {
                        // Only if battery level is defined
                        if (this->hasBatteryLevel()) {
                            TransmitBatteryLevelAction * action = this->getActionTransmitBatteryLevel();

                            // Request
                            action->request();
                        }
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

                    /**
                     * Get date time action
                     *
                     * Generate instance if not exist yet and if RTC is available
                     */
                    DateTimeAction * getActionDateTime()
                    {
                        if (this->actionDateTime == NULL && this->hasRTC()) {
                            this->actionDateTime = new DateTimeAction(
                                this->getPropertyType(),
                                this->getPropertyIdentifier(),
                                this->getRTC(),
                                Identity::MASTER,
                                this->getTransmitter()
                            );
                        }

                        return this->actionDateTime;
                    }

                    /**
                     * Get transmit battery level action
                     *
                     * Generate instance if not exist yet and if battery level is available
                     */
                    TransmitBatteryLevelAction * getActionTransmitBatteryLevel()
                    {
                        if (this->actionTransmitBatteryLevel == NULL && this->hasBatteryLevel()) {
                            this->actionTransmitBatteryLevel = new TransmitBatteryLevelAction(
                                this->getPropertyType(),
                                this->getPropertyIdentifier(),
                                this->getBatteryLevel(),
                                Identity::MASTER,
                                this->getTransmitter()
                            );
                        }

                        return this->actionTransmitBatteryLevel;
                    }

                    /**
                     * Get RTC
                     */
                    RTC_DS1307 * getRTC()
                    {
                        return this->rtc;
                    }

                    /**
                     * Set RTC
                     */
                    void setRTC(RTC_DS1307 * rtc)
                    {
                        this->rtc = rtc;
                    }

                    /**
                     * Flag to indicate if rtc has defined
                     */
                    bool hasRTC()
                    {
                        return this->rtc != NULL;
                    }

                    /**
                     * Flag to indicate if battery level component exists
                     */
                    bool hasBatteryLevel()
                    {
                        return this->batteryLevel != NULL;
                    }

                    /**
                     * Set battery level component
                     */
                    void setBatteryLevel(BatteryLevel * batteryLevel)
                    {
                        this->batteryLevel = batteryLevel;
                    }

                    /**
                     * Get battery level component
                     */
                    BatteryLevel * getBatteryLevel()
                    {
                        return this->batteryLevel;
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

                    /**
                     * Date time action
                     */
                    DateTimeAction * actionDateTime = NULL;

                    /**
                     * Transmit battery level action
                     */
                    TransmitBatteryLevelAction * actionTransmitBatteryLevel = NULL;

                    /**
                     * RTC object for DateTime
                     */
                    RTC_DS1307 * rtc = NULL;

                    /**
                     * Battery level component
                     */
                    BatteryLevel * batteryLevel = NULL;

                };
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_ARDUINO_ARDUINOAPPLICATION_H
