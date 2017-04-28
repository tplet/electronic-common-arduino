//
// Created by Thibault PLET on 28/09/2016.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_ACTION_TRANSMITBATTERYLEVELACTION_H
#define COM_OSTERES_AUTOMATION_ARDUINO_ACTION_TRANSMITBATTERYLEVELACTION_H

#include <com/osteres/automation/action/Action.h>
#include <com/osteres/automation/transmission/Transmitter.h>
#include <com/osteres/automation/transmission/packet/Packet.h>
#include <com/osteres/automation/transmission/packet/Command.h>
#include <com/osteres/automation/memory/Property.h>
#include <com/osteres/automation/arduino/memory/StoredProperty.h>
#include <com/osteres/automation/arduino/component/BatteryLevel.h>

using com::osteres::automation::action::Action;
using com::osteres::automation::transmission::Transmitter;
using com::osteres::automation::transmission::packet::Packet;
using com::osteres::automation::transmission::packet::Command;
using com::osteres::automation::memory::Property;
using com::osteres::automation::arduino::memory::StoredProperty;
using com::osteres::automation::arduino::component::BatteryLevel;

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
                    class TransmitBatteryLevelAction : public Action
                    {
                    public:
                        /**
                         * Constructor
                         */
                        TransmitBatteryLevelAction(
                            Property<unsigned char> * propertyType,
                            StoredProperty<unsigned char> * propertyIdentifier,
                            BatteryLevel * batteryLevel,
                            unsigned char target,
                            Transmitter * transmitter
                        ) {
                            this->batteryLevel = batteryLevel;
                            this->transmitter = transmitter;
                            this->target = target;
                            this->propertyType = propertyType;
                            this->propertyIdentifier = propertyIdentifier;
                        }

                        /**
                         * Request to send battery level
                         */
                        void request()
                        {
                            // parent
                            Action::execute();

                            // Battery level (in pourcent)
                            unsigned char level = this->batteryLevel->getRatio() * 100.0;

                            // Prepare packet
                            Packet * packet = new Packet(this->propertyType->get());

                            // Prepare data
                            packet->setCommand(Command::BATTERY);
                            packet->setTarget(this->target);
                            packet->setSourceIdentifier(this->propertyIdentifier->get());
                            packet->setSourceType(this->propertyType->get());
                            packet->setDataUChar1(level);

                            // Transmit packet
                            this->transmitter->add(packet);
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
                         * Transmitter to send packet
                         */
                        Transmitter * transmitter = NULL;

                        /**
                         * Target to obtain identifier
                         */
                        unsigned char target;

                        /**
                         * Battery level component
                         */
                        BatteryLevel * batteryLevel = NULL;

                    };
                }
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_ARDUINO_ACTION_TRANSMITBATTERYLEVELACTION_H
