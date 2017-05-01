//
// Created by Thibault PLET on 21/04/2017.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_DISPLAY_DEVICE_SCREEN_H
#define COM_OSTERES_AUTOMATION_ARDUINO_DISPLAY_DEVICE_SCREEN_H

/* Defined values */
#define LCD_WIDTH 16
#define LCD_HEIGHT 2

#include <LiquidCrystal.h>
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
                    namespace device
                    {
                        class Screen : public Device
                        {
                        public:

                            /**
                             * Constructor
                             *
                             * @param device LiquidCrystal screen
                             * @param width Screen width (number of chars)
                             * @param height Screen height (number of chars)
                             */
                            Screen(
                                LiquidCrystal *device,
                                unsigned int width,
                                unsigned int height
                            )
                            {
                                this->construct(device, width, height);
                            }

                            /**
                             * Constructor
                             *
                             * @param device LiquidCrystal screen
                             */
                            Screen(LiquidCrystal *device)
                            {
                                this->construct(device, LCD_WIDTH, LCD_HEIGHT);
                            }

                            /**
                             * Destructor
                             */
                            virtual ~Screen()
                            {
                                // Enabled property
                                if (this->enabled != NULL) {
                                    delete this->enabled;
                                    this->enabled = NULL;
                                }
                            }

                            /**
                             * Enable screen if available
                             */
                            virtual void enable()
                            {
                                Device::enable();

                                if (this->hasDevice()) {
                                    this->device->begin(this->getWidth(), this->getHeight());
                                    this->device->display();
                                }
                            }

                            /**
                             * Disable screen if available
                             */
                            virtual void disable()
                            {
                                Device::disable();

                                if (this->hasDevice()) {
                                    this->device->noDisplay();
                                }
                            }

                            /**
                             * Enable switch detection to enable/disable screen
                             *
                             * Need to call detectSwitch() method in sensor loop
                             */
                            void enableSwitchDetection(unsigned int pin, bool digital)
                            {
                                this->switchPin = pin;
                                this->switchPinDigital = digital;
                                this->switchEnabled = true;
                            }

                            /**
                             * Disable switch detection to enable/disable screen
                             */
                            void disableSwitch()
                            {
                                this->switchEnabled = false;
                            }

                            /**
                             * Set cursor position on screen
                             */
                            void setCursor(uint8_t col, uint8_t row)
                            {
                                this->device->setCursor(col, row);
                            }

                            /**
                             * Write to display
                             */
                            size_t write(const char *str)
                            {
                                this->device->write(str);
                            }

                            /**
                             * Switch detection
                             *
                             * Change enabled property when pin value change and enable/disable screen
                             */
                            void detectSwitch()
                            {
                                if (this->isSwitchEnabled()) {
                                    // Read value
                                    bool value;
                                    if (this->switchPinDigital) {
                                        value = digitalRead(this->switchPin) == 1;
                                    } else {
                                        value = analogRead(this->switchPin) >= 512;
                                    }
                                    this->enabled->set(value);

                                    // If value changed, enable/disable screen
                                    if (this->enabled->isChanged()) {
                                        if (value) {
                                            this->enable();
                                        } else {
                                            this->disable();
                                        }
                                    }
                                }
                            }

                            /**
                             * Get screen
                             */
                            LiquidCrystal *getDevice()
                            {
                                return this->device;
                            }

                            /**
                             * Set screen
                             */
                            void setDevice(LiquidCrystal *device)
                            {
                                this->device = device;
                            }

                            /**
                             * Flag to indicate if a screen is available
                             */
                            bool hasDevice()
                            {
                                return this->device != NULL;
                            }

                            /**
                             * Set screen width
                             */
                            void setWidth(unsigned int width)
                            {
                                this->width = width;
                            }

                            /**
                             * Get screen width
                             */
                            unsigned int getWidth()
                            {
                                return this->width;
                            }

                            /**
                             * Set screen height
                             */
                            void setHeight(unsigned int height)
                            {
                                this->height = height;
                            }

                            /**
                             * Get screen height
                             */
                            unsigned int getHeight()
                            {
                                return this->height;
                            }

                            /**
                             * Flag to indicate if switch detection is used to set screen state (enable or disable)
                             */
                            bool isSwitchEnabled()
                            {
                                return this->switchEnabled;
                            }

                        protected:
                            /**
                             * Global construct part
                             */
                            void construct(
                                LiquidCrystal *device,
                                unsigned int width,
                                unsigned int height
                            )
                            {
                                // Prepare enabled property
                                this->enabled = new Property<bool>(false);

                                this->setWidth(width);
                                this->setHeight(height);
                                this->setDevice(device);

                            }

                            /**
                             * Screen
                             */
                            LiquidCrystal *device = NULL;

                            /**
                             * Screen width (in number of chars)
                             */
                            unsigned int width = LCD_WIDTH;

                            /**
                             * Screen height (in number of chars)
                             */
                            unsigned int height = LCD_HEIGHT;

                            /**
                             * Flag to indicate if switch detection is used to set screen state (enable or disable)
                             */
                            bool switchEnabled = false;

                            /**
                             * Switch pin to read
                             */
                            unsigned int switchPin = 0;

                            /**
                             * Flag to indicate if pin for switch is analog or digital pin
                             */
                            bool switchPinDigital = true;
                        };
                    }
                };
            };
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_ARDUINO_DISPLAY_DEVICE_SCREEN_H
