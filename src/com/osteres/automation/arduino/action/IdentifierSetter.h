//
// Created by Thibault PLET on 28/09/2016.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_ACTION_IDENTIFIERSETTER_H
#define COM_OSTERES_AUTOMATION_ARDUINO_ACTION_IDENTIFIERSETTER_H

#include <com/osteres/automation/action/Action.h>
#include <com/osteres/automation/transmission/Transmitter.h>
#include <com/osteres/automation/transmission/packet/Packet.h>
#include <com/osteres/automation/transmission/packet/Command.h>
#include <com/osteres/automation/arduino/memory/Value.h>

using com::osteres::automation::action::Action;
using com::osteres::automation::transmission::Transmitter;
using com::osteres::automation::transmission::packet::Packet;
using com::osteres::automation::transmission::packet::Command;
using com::osteres::automation::arduino::memory::Value;

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
                    class IdentifierSetter : public Action
                    {
                    public:
                        /**
                         * Constructor
                         */
                        IdentifierSetter(Value<unsigned char> * identifier, Transmitter * transmitter)
                        {
                            this->identifier = identifier;
                            this->transmitter = transmitter;
                        }

                        /**
                         * Request to obtain new identifier
                         */
                        void request(unsigned char type, unsigned char to)
                        {
                            // parent
                            Action::execute();

                            Packet * packet = new Packet(this->identifier->get());

                            // Prepare data
                            packet->setCommand(Command::IDENTIFIER_REQUEST);
                            packet->setTarget(to);
                            packet->setLast(true);
                            packet->setDataUChar1(type); // Sensor type

                            // Transmit packet
                            this->transmitter->send(packet);

                            // Free memory
                            delete packet;

                            this->setSuccess();
                            return this->isSuccess();
                        }

                        /**
                         * Identifier received
                         * Save it
                         */
                        void response(Packet * packet)
                        {
                            this->identifier->set(packet->getDataUChar1());
                        }

                    protected:
                        /**
                         * EEPROM location for identifier value
                         */
                        Value<unsigned char> * identifier = NULL;
                        /**
                         * Transmitter to send packet
                         */
                        Transmitter * transmitter = NULL;

                    };
                }
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_ARDUINO_ACTION_IDENTIFIERSETTER_H
