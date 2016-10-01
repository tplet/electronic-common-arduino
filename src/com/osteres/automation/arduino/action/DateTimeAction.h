//
// Created by Thibault PLET on 28/09/2016.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_ACTION_DATETIMEACTION_H
#define COM_OSTERES_AUTOMATION_ARDUINO_ACTION_DATETIMEACTION_H

#include <RTClib/RTClib.h>
#include <com/osteres/automation/action/Action.h>
#include <com/osteres/automation/transmission/Transmitter.h>
#include <com/osteres/automation/transmission/packet/Packet.h>
#include <com/osteres/automation/transmission/packet/Command.h>
#include <com/osteres/automation/memory/Property.h>
#include <com/osteres/automation/arduino/memory/StoredProperty.h>

using com::osteres::automation::action::Action;
using com::osteres::automation::transmission::Transmitter;
using com::osteres::automation::transmission::packet::Packet;
using com::osteres::automation::transmission::packet::Command;
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
                namespace action
                {
                    class DateTimeAction : public Action
                    {
                    public:
                        /**
                         * Constructor
                         */
                        DateTimeAction(
                            Property<unsigned char> * propertyType,
                            StoredProperty<unsigned char> * propertyIdentifier,
                            RTC_DS1307 * rtc,
                            unsigned char target,
                            Transmitter * transmitter
                        ) {
                            this->rtc = rtc;
                            this->transmitter = transmitter;
                            this->target = target;
                        }

                        /**
                         * Request to obtain new identifier
                         */
                        void request()
                        {
                            // parent
                            Action::execute();

                            Packet * packet = new Packet(this->propertyType->get());

                            // Prepare data
                            packet->setCommand(Command::DATETIME_REQUEST);
                            packet->setTarget(this->target);
                            packet->setSourceIdentifier(this->propertyIdentifier->get());
                            packet->setLast(true);

                            // Transmit packet
                            this->transmitter->send(packet);

                            // Free memory
                            delete packet;
                        }

                        /**
                         * Identifier received
                         * Save it
                         */
                        void response(Packet * packet)
                        {
                            this->rtc->adjust(DateTime(static_cast<uint32_t>(packet->getDataLong1())));
                            this->setSuccess();
                            this->executed = true;
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
                         * RTC for DateTime
                         */
                        RTC_DS1307 * rtc = NULL;

                        /**
                         * Transmitter to send packet
                         */
                        Transmitter * transmitter = NULL;

                        /**
                         * Target to obtain identifier
                         */
                        unsigned char target;

                    };
                }
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_ARDUINO_ACTION_DATETIMEACTION_H
