//
// Created by Thibault PLET on 26/07/2016.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_MEMORY_STOREDPROPERTY_H
#define COM_OSTERES_AUTOMATION_ARDUINO_MEMORY_STOREDPROPERTY_H

#include <EEPROM.h>
#include <com/osteres/automation/memory/Property.h>

using com::osteres::automation::memory::Property;

namespace com
{
    namespace osteres
    {
        namespace automation
        {
            namespace arduino
            {
                namespace memory
                {
                    template<typename T>
                    class StoredProperty : public Property<T> {
                    protected:
                        /**
                         * Address to where contained data in EEProm
                         */
                        int address;

                        /**
                         * Flag to indicate if needed to force to read value from memory next time
                         */
                        bool forceReading;

                    public:
                        /**
                         * Constructor
                         */
                        StoredProperty() : Property<T>()
                        {
                            this->construct();
                        }

                        /**
                         * Constructor
                         * Be careful, when init value specified, can erase current stored value
                         *
                         * @param int address Address to stored data in EEProm. Be sure that this address not already used!
                         */
                        StoredProperty(T initValue) : Property<T>(initValue)
                        {
                            this->construct();
                        };

                        /**
                         * Common method for constructor
                         */
                        void construct()
                        {
                            this->forceReading = true;
                        }

                        /**
                         * Get address
                         */
                        int getAddress()
                        {
                            return this->address;
                        }

                        /**
                         * Set address
                         * Be sure for this operation and that this address not already used! Data will be lost!
                         */
                        void setAddress(int address)
                        {
                            this->address = address;
                            // Next time we read value, force refresh from memory
                            this->forceReading = true;
                        }

                        /**
                         * Set value
                         *
                         * @param T value Value to store
                         */
                        T set(T value) {
                            // Parent
                            Property<T>::set(value);

                            if (this->isChanged()) {
                                EEPROM.put(this->getAddress(), this->value);
                                this->forceReading = false;
                            }

                            return this->value;
                        }

                        /**
                         * Get value
                         */
                        T get() {
                            // Parent
                            T v = Property<T>::get();

                            if (this->isForceReading()) {
                                EEPROM.get(this->getAddress(), this->value);
                                this->forceReading = false;
                                v = Property<T>::get();
                            }

                            return v;
                        }

                        /**
                         * Flag to indicate if needed to force to read value from memory next time
                         */
                        bool isForceReading()
                        {
                            return this->forceReading;
                        }

                        /**
                         * Force reading property from memory next time to read
                         */
                        void setForceReading(bool force)
                        {
                            this->forceReading = force;
                        }
                    };
                }
            }
        }
    }
}


#endif //COM_OSTERES_AUTOMATION_ARDUINO_MEMORY_STOREDPROPERTY_H
