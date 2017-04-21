//
// Created by Thibault PLET on 21/04/2017.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_COMPONENT_SCREEN_H
#define COM_OSTERES_AUTOMATION_ARDUINO_COMPONENT_SCREEN_H

/* Defined values */
#define LCD_WIDTH 16
#define LCD_HEIGHT 2

#include <LiquidCrystal.h>

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
                    class Screen
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
                        ~Screen()
                        {


                        }

                        /**
                         * Enable screen if available
                         */
                        void enable()
                        {
                            if (this->hasDevice()) {
                                this->setEnabled(true);
                                this->device->begin(this->getWidth(), this->getHeight());
                                this->device->display();
                            }
                        }

                        /**
                         * Disable screen if available
                         */
                        void disable()
                        {
                            if (this->hasDevice()) {
                                this->device->noDisplay();
                                this->setEnabled(false);
                            }
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
                         * Flag to indicate if screen is enable and used
                         */
                        bool isEnabled()
                        {
                            return this->enabled;
                        }

                        /**
                         * Indicate if screen is enabled and used
                         */
                        void setEnabled(bool flag)
                        {
                            this->enabled = flag;
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
                            this->setDevice(device);
                            this->setWidth(width);
                            this->setHeight(height);
                        }

                        /**
                         * Screen
                         */
                        LiquidCrystal *device = NULL;

                        /**
                         * Flag to indicate if screen is enabled and used
                         */
                        bool enabled = false;

                        /**
                         * Screen width (in number of chars)
                         */
                        unsigned int width = LCD_WIDTH;

                        /**
                         * Screen height (in number of chars)
                         */
                        unsigned int height = LCD_HEIGHT;
                    };
                };
            };
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_ARDUINO_COMPONENT_SCREEN_H
