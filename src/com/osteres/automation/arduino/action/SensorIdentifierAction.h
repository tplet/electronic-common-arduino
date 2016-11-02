//
// Created by Thibault PLET on 28/09/2016.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_ACTION_SENSORIDENTIFIERACTION_H
#define COM_OSTERES_AUTOMATION_ARDUINO_ACTION_SENSORIDENTIFIERACTION_H

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
                    class SensorIdentifierAction : public Action
                    {
                    public:
                        /**
                         * Constructor
                         */
                        SensorIdentifierAction(
                            Property<unsigned char> * propertyType,
                            StoredProperty<unsigned char> * propertyIdentifier,
                            unsigned char target,
                            Transmitter * transmitter
                        ) {
                            this->propertyType = propertyType;
                            this->propertyIdentifier = propertyIdentifier;
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

                            //Search if an IDENTIFIER_REQUEST already exist
                            bool found = false;
                            Packing * packing = NULL;
                            for (unsigned int i = 0; i < this->transmitter->getQueueSended()->size(); i++) {
                                packing = this->transmitter->getQueueSended()->at(i);
                                if (packing->getPacket()->getCommand() == Command::IDENTIFIER_REQUEST) {
                                    found = true;
                                    break;
                                }
                            }
                            packing = NULL;

                            // If not already exists
                            if (!found) {
                                Packet *packet = new Packet(this->propertyType->get());

                                // Prepare data
                                packet->setCommand(Command::IDENTIFIER_REQUEST);
                                packet->setTarget(this->target);

                                // Transmit packet
                                this->transmitter->add(packet, true);
                            }
                        }

                        /**
                         * Identifier received
                         * Save it
                         */
                        void response(Packet * packet)
                        {
                            this->propertyIdentifier->set(static_cast<unsigned char>(packet->getDataUChar1()));
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

#endif //COM_OSTERES_AUTOMATION_ARDUINO_ACTION_SENSORIDENTIFIERACTION_H
