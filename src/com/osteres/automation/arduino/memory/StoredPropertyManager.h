//
// Created by Thibault PLET on 16/05/2017.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_MEMORY_STOREDPROPERTYMANAGER_H
#define COM_OSTERES_AUTOMATION_ARDUINO_MEMORY_STOREDPROPERTYMANAGER_H

#include <com/osteres/automation/arduino/memory/StoredProperty.h>

using com::osteres::automation::arduino::memory::StoredProperty;

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
                    class StoredPropertyManager {
                    protected:

                        /**
                         * Constructor
                         */
                        StoredPropertyManager()
                        {
                        }

                        /**
                         * Value to next address
                         */
                        static unsigned int nextAddress;


                    public:
                        /**
                         * Get next address value
                         */
                        static unsigned int getNextAddress()
                        {
                            return nextAddress;
                        }

                        template <typename T>
                        static void configure(StoredProperty<T> * storedProperty)
                        {
                            // Set stored property address
                            storedProperty->setAddress(nextAddress);

                            // Increment address
                            nextAddress += sizeof(T);
                        }
                    };

                    /**
                     * Init next address static property
                     */
                    unsigned int StoredPropertyManager::nextAddress = 0;
                }
            }
        }
    }
}


#endif //COM_OSTERES_AUTOMATION_ARDUINO_MEMORY_STOREDPROPERTYMANAGER_H
