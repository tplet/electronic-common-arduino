//
// Created by Thibault PLET on 23/04/2017.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_COMPONENT_BATTERYLEVEL_H
#define COM_OSTERES_AUTOMATION_ARDUINO_COMPONENT_BATTERYLEVEL_H

#include <com/osteres/automation/arduino/memory/PinProperty.h>

using com::osteres::automation::arduino::memory::PinProperty;

namespace com
{
    namespace osteres
    {
        namespace automation
        {
            namespace arduino
            {
                namespace component
                {
                    class BatteryLevel
                    {
                    public:

                        /**
                         * Constructor
                         *
                         * @param pin Pin address to read battery level
                         */
                        BatteryLevel(unsigned int pin)
                        {
                            this->construct(pin);
                        }

                        /**
                         * Destructor
                         */
                        ~BatteryLevel()
                        {
                            // Value property
                            if (this->value != NULL) {
                                delete this->value;
                                this->value = NULL;
                            }
                        }

                        /**
                         * Get battery voltage
                         */
                        float getVoltage()
                        {
                            /*
                             * We search to found battery voltage (and not pin value voltage)
                             * batteryVoltage = voltagePin * (resistanceVcc + resistanceGnd) / resistanceGnd
                             * pinVoltage = pin_value * vcc / 1024
                             */

                            float pinVoltage = this->getPinVoltage();
                            float batteryVoltage = this->getCalculatedBatteryVoltage(pinVoltage);

                            /*
                            Serial.print("Pin value: ");
                            Serial.println(pinValue);
                            Serial.print("Pin voltage: ");
                            Serial.println(pinVoltage);
                            Serial.print("Battery voltage: ");
                            Serial.println(batteryVoltage);
                            */

                            return batteryVoltage;
                        }

                        /**
                         * Get pin voltage
                         */
                        float getPinVoltage()
                        {
                            /*
                             * pinVoltage = pin_value * vcc / 1024
                             */
                            unsigned int pinValue = this->value->read();

                            return float(pinValue) * this->vcc / 1024.0;
                        }

                        /**
                         * Get battery level ratio
                         */
                        float getRatio()
                        {
                            return (this->getVoltage() - this->getVoltageMin()) /
                                (this->getVoltageMax() - this->getVoltageMin());
                        }

                        /**
                         * Set pin address to read battery level
                         */
                        void setPin(unsigned int pin)
                        {
                            this->value->setPin(pin);
                        }

                        /**
                         * Get pin address to read battery level
                         */
                        unsigned int getPin()
                        {
                            return this->value->getPin();
                        }

                        /**
                         * Set reference voltage (when value is 1024, corresponding to this reference value)
                         */
                        void setVcc(float v)
                        {
                            this->vcc = v;
                        }

                        /**
                         * get reference voltage (when value is 1024, corresponding to this reference value)
                         */
                        float getVcc()
                        {
                            return this->vcc;
                        }

                        /**
                         * Set resistance value between pin and ground
                         */
                        void setResistanceGnd(float v)
                        {
                            this->resistanceGnd = v;
                        }

                        /**
                         * Get resistance value between pin and ground
                         */
                        float getResistanceGnd()
                        {
                            return this->resistanceGnd;
                        }

                        /**
                         * Set resistance value between vcc and pin
                         */
                        void setResistanceVcc(float v)
                        {
                            this->resistanceVcc = v;
                        }

                        /**
                         * Get resistance value between vcc and pin
                         */
                        float getResistanceVcc()
                        {
                            return this->resistanceVcc;
                        }

                        /**
                         * Set battery voltage max
                         */
                        void setVoltageMax(float v)
                        {
                            this->voltageMax = v;
                        }

                        /**
                         * Get battery voltage max
                         */
                        float getVoltageMax()
                        {
                            return this->voltageMax;
                        }

                        /**
                         * Set battery voltage min
                         */
                        void setVoltageMin(float v)
                        {
                            this->voltageMin = v;
                        }

                        /**
                         * Get battery voltage min
                         */
                        float getVoltageMin()
                        {
                            return this->voltageMin;
                        }


                    protected:
                        /**
                         * Global construct part
                         */
                        void construct(
                            unsigned int pin
                        )
                        {
                            // Prepare value property (analog pin)
                            this->value = new PinProperty<unsigned int>(pin, false);
                        }

                        /**
                         * Get voltage of battery from pin voltage (using voltage divider rule)
                         */
                        float getCalculatedBatteryVoltage(float pinVoltage)
                        {
                            return pinVoltage * (this->resistanceVcc + this->resistanceGnd) / this->resistanceGnd;
                        }

                        /**
                         * Property containing battery level
                         */
                        PinProperty<unsigned int> * value;

                        /**
                         * Reference voltage (when value is 1024, corresponding to this reference)
                         */
                        float vcc = 5.0;

                        /**
                         * Resistance value between pin and ground
                         */
                        float resistanceGnd = 10e3;

                        /**
                         * Resistance value between vcc and pin
                         */
                        float resistanceVcc = 3.3e3;

                        /**
                         * Battery voltage max
                         */
                        float voltageMax = 4.2;

                        /**
                         * Battery voltage min
                         */
                        float voltageMin = 3.0;
                    };
                };
            };
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_ARDUINO_COMPONENT_BATTERYLEVEL_H
