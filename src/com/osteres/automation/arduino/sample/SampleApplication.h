//
// Created by Thibault PLET on 29/05/2016.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_SAMPLE_SAMPLEAPPLICATION_H
#define COM_OSTERES_AUTOMATION_ARDUINO_SAMPLE_SAMPLEAPPLICATION_H

#define ADDR_COUNTER 0x0C

#include <com/osteres/automation/Application.h>
#include <LiquidCrystal.h>
#include <com/osteres/automation/arduino/memory/Value.h>

using com::osteres::automation::Application;
using com::osteres::automation::arduino::memory::Value;

namespace com
{
    namespace osteres
    {
        namespace automation
        {
            namespace arduino {
                namespace sample {
                    class SampleApplication : Application {
                    public:
                        /**
                         * Constructor
                         */
                        SampleApplication(LiquidCrystal *screen, unsigned int pinLight) {
                            this->screen = screen;
                            this->pinLight = pinLight;

                            // Init counter
                            this->counter = new Value<unsigned int>(ADDR_COUNTER, 0);
                        }

                        /**
                         * Destructor
                         */
                        ~SampleApplication() {
                            // Remove counter
                            if (this->counter != NULL) {
                                delete this->counter;
                                this->counter = NULL;
                            }
                        }

                        /**
                         * Init application
                         */
                        void setup() {
                            // Enable screen light
                            pinMode(this->pinLight, OUTPUT);
                            digitalWrite(this->pinLight, HIGH);

                            // Init screen
                            this->screen->begin(16, 2);
                            this->screen->display();
                        }

                        /**
                         * Process application
                         */
                        void process() {
                            // Increment counter
                            this->counter->set(this->counter->get() + 1);

                            this->refreshScreen();

                            // Wait 1s
                            delay(1000);
                        }

                        /**
                         * Refresh screen
                         */
                        void refreshScreen() {
                            // Clear screen
                            this->screen->clear();

                            // Display counter
                            this->screen->setCursor(0, 0);
                            String output = "Counter:" + String(this->counter->get());
                            this->screen->write(output.c_str());
                        }

                    protected:
                        /**
                         * Screen
                         */
                        LiquidCrystal *screen = NULL;

                        /**
                         * Counter
                         */
                        Value<unsigned int> *counter = NULL;

                        /**
                         * Screen pin light
                         */
                        unsigned int pinLight;
                    };
                }
            }
        }
    }
}


#endif //COM_OSTERES_AUTOMATION_ARDUINO_SAMPLE_SAMPLEAPPLICATION_H
