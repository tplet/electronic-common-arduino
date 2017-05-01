//
// Created by Thibault PLET on 01/05/2017.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_DISPLAY_OUTPUT_H
#define COM_OSTERES_AUTOMATION_ARDUINO_DISPLAY_OUTPUT_H

#include <com/osteres/automation/arduino/display/Device.h>

using com::osteres::automation::arduino::display::Device;

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
                    class Output
                    {
                    public:

                        /**
                         * Constructor
                         *
                         * @param device Device
                         */
                        Output(Device *device)
                        {
                            this->setDevice(device);
                        }

                        /**
                         * Constructor
                         */
                        Output() { }

                        /**
                         * Setup output
                         *
                         * Need to call with setup arduino application
                         */
                        virtual void setup();

                        /**
                         * Print to output
                         *
                         * Call to display content to output
                         */
                        virtual void print();

                        /**
                         * Loop process
                         */
                        virtual void loop();

                        /**
                         * Get device
                         */
                        Device *getDevice()
                        {
                            return this->device;
                        }

                        /**
                         * Set device
                         */
                        void setDevice(Device *device)
                        {
                            this->device = device;
                        }

                        /**
                         * Flag to indicate if a device is defined
                         */
                        bool hasDevice()
                        {
                            return this->device != NULL;
                        }

                    protected:
                        /**
                         * Device associated
                         */
                        Device *device = NULL;
                    };
                };
            };
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_ARDUINO_DISPLAY_OUTPUT_H
