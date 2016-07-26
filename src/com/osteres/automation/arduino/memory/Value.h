//
// Created by Thibault PLET on 26/07/2016.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_MEMORY_VALUE_H
#define COM_OSTERES_AUTOMATION_ARDUINO_MEMORY_VALUE_H

#include <EEPROM.h>
#include <com/osteres/automation/memory/ValueBase.h>

using com::osteres::automation::memory::ValueBase;

namespace com {
    namespace osteres {
        namespace automation {
            namespace arduino {
                namespace memory {
                    template<typename T>
                    class Value : public ValueBase {
                    protected:
                        /**
                         * Value stored
                         */
                        T value;
                    public:
                        /**
                         * Constructor
                         *
                         * @param int address Address to stored data in EEProm. Be sure that this address not already used!
                         */
                        Value(int address) : ValueBase(address) { };

                        /**
                         * Get address
                         */
                        int getAddress() {
                            return ValueBase::getAddress();
                        };

                        /**
                         * Constructor
                         *
                         * @param int address Address to stored data in EEProm. Be sure that this address not already used!
                         * @param T initValue Init value to affect if no value to memory
                         */
                        Value(int address, T initValue) : ValueBase(address) {
                            // Read value
                            if (initValue != this->get()) {
                                this->set(initValue);
                            }
                        };

                        /**
                         * Set value
                         *
                         * @param T value Value to store
                         */
                        T set(T value) {
                            if (this->value != value) {
                                this->value = value;
                                EEPROM.put(this->getAddress(), this->value);
                                this->changed = false;
                            }

                            return this->value;
                        }

                        /**
                         * Get value
                         */
                        T get() {
                            if (this->isChanged()) {
                                EEPROM.get(this->getAddress(), this->value);
                                this->changed = false;
                            }

                            return this->value;
                        }
                    };
                }
            }
        }
    }
}


#endif //COM_OSTERES_AUTOMATION_ARDUINO_MEMORY_VALUE_H
