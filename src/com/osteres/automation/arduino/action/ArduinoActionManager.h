//
// Created by Thibault PLET on 02/06/2016.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_ACTION_ARDUINOACTIONMANAGER_H
#define COM_OSTERES_AUTOMATION_ARDUINO_ACTION_ARDUINOACTIONMANAGER_H

#include <Arduino.h>
#include <string>
#include <com/osteres/automation/transmission/packet/Command.h>
#include <com/osteres/automation/transmission/packet/CommandString.h>
#include <com/osteres/automation/transmission/packet/Packet.h>
#include <com/osteres/automation/action/ActionManagerBase.h>
#include <com/osteres/automation/arduino/action/SensorIdentifierAction.h>
#include <com/osteres/automation/arduino/action/DateTimeAction.h>

using com::osteres::automation::transmission::packet::Command;
using com::osteres::automation::transmission::packet::CommandString;
using com::osteres::automation::transmission::packet::Packet;
using com::osteres::automation::action::ActionManagerBase;
using com::osteres::automation::arduino::action::SensorIdentifierAction;
using com::osteres::automation::arduino::action::DateTimeAction;
using std::string;

namespace com
{
    namespace osteres
    {
        namespace automation
        {
            namespace arduino
            {
                namespace action
                {
                    class ArduinoActionManager : public ActionManagerBase
                    {
                    public:
                        /**
                         * Constructor
                         */
                        ArduinoActionManager() {
                        }

                        /**
                         * Process packet
                         */
                        virtual void processPacket(Packet * packet)
                        {
                            // Command: IDENTIFIER_RESPONSE
                            if (Command::IDENTIFIER_RESPONSE == packet->getCommand()) {
                                if (this->hasActionSensorIdentifier()) {
                                    this->getActionSensorIdentifier()->response(packet);
                                }
                            }
                            // Command: DATETIME_RESPONSE
                            else if (Command::DATETIME_RESPONSE == packet->getCommand()) {
                                if (this->hasActionDateTime()) {
                                    this->getActionDateTime()->response(packet);
                                }
                            }
                        }

                        /**
                         * Set sensor identifier action
                         */
                        void setActionSensorIdentifier(SensorIdentifierAction * action)
                        {
                            this->actionSensorIdentifier = action;
                        }

                        /**
                         * Flag to indicate if sensor identifier action is defined
                         */
                        bool hasActionSensorIdentifier()
                        {
                            return this->actionSensorIdentifier != NULL;
                        }

                        /**
                         * Get sensor identifier action
                         */
                        SensorIdentifierAction * getActionSensorIdentifier()
                        {
                            return this->actionSensorIdentifier;
                        }

                        /**
                         * Set date time action
                         */
                        void setActionDateTime(DateTimeAction * action)
                        {
                            this->actionDateTime = action;
                        }

                        /**
                         * Flag to indicate if date time action is defined
                         */
                        bool hasActionDateTime()
                        {
                            return this->actionDateTime != NULL;
                        }

                        /**
                         * Get date time action
                         */
                        DateTimeAction * getActionDateTime()
                        {
                            return this->actionDateTime;
                        }

                    protected:

                        /**
                         * Sensor identifier action
                         */
                        SensorIdentifierAction * actionSensorIdentifier = NULL;

                        /**
                         * Date time action
                         */
                        DateTimeAction * actionDateTime = NULL;

                        /**
                         * RTC for DateTime
                         */
                        RTC_DS1307 * rtc = NULL;
                    };
                }
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_ARDUINO_ACTION_ARDUINOACTIONMANAGER_H
