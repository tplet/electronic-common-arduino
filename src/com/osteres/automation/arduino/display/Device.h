//
// Created by Thibault PLET on 01/05/2017.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_DISPLAY_DEVICE_H
#define COM_OSTERES_AUTOMATION_ARDUINO_DISPLAY_DEVICE_H

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
                namespace display
                {
                    class Device
                    {
                    public:

                        /**
                         * Constructor
                         */
                        Device() { }

                        /**
                         * Destructor
                         */
                        virtual ~Device()
                        {
                            // Enabled property
                            if (this->enabled != NULL) {
                                delete this->enabled;
                                this->enabled = NULL;
                            }
                        }

                        /**
                         * Enable device
                         */
                        virtual void enable()
                        {
                            this->setEnabled(true);
                        }

                        /**
                         * Disable device
                         */
                        virtual void disable()
                        {
                            this->setEnabled(false);
                        }

                        /**
                         * Flag to indicate if device is enable
                         */
                        bool isEnabled()
                        {
                            return this->enabled->get();
                        }

                        /**
                         * Indicate if device is enabled
                         */
                        void setEnabled(bool flag)
                        {
                            this->enabled->set(flag);
                        }

                    protected:
                        /**
                         * Property to store enabled value
                         */
                        Property<bool> * enabled = NULL;
                    };
                };
            };
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_ARDUINO_DISPLAY_DEVICE_H
