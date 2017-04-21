//
// Created by Thibault PLET on 21/04/2017.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_SCREENARDUINOAPPLICATION_H
#define COM_OSTERES_AUTOMATION_ARDUINO_SCREENARDUINOAPPLICATION_H

/* Defined values */
#define LCD_WIDTH 16
#define LCD_HEIGHT 2

#include <RTClib/RTClib.h>
#include <LiquidCrystal.h>
#include <com/osteres/automation/transmission/Transmitter.h>
#include <com/osteres/automation/arduino/ArduinoApplication.h>

using com::osteres::automation::transmission::Transmitter;
using com::osteres::automation::arduino::ArduinoApplication;

namespace com
{
    namespace osteres
    {
        namespace automation
        {
            namespace arduino
            {
                class ScreenArduinoApplication : public ArduinoApplication
                {
                public:
                    /**
                     * Constructor
                     *
                     * @param type Sensor type identifier
                     * @param transmitter Transmitter
                     * @param screen LiquidCrystal screen
                     */
                    ScreenArduinoApplication(
                        unsigned char type,
                        Transmitter * transmitter,
                        LiquidCrystal * screen
                    ) : ArduinoApplication(type, transmitter)
                    {
                        this->construct(screen, LCD_WIDTH, LCD_HEIGHT);
                    }

                    /**
                     * Constructor
                     *
                     * @param type Sensor type identifier
                     * @param transmitter Transmitter
                     * @param screen LiquidCrystal screen
                     * @param screenWidth Screen width (number of chars)
                     * @param screenHeight Screen height (number of chars)
                     */
                    ScreenArduinoApplication(
                        unsigned char type,
                        Transmitter * transmitter,
                        LiquidCrystal * screen,
                        unsigned int screenWidth,
                        unsigned int screenHeight
                    ) : ArduinoApplication(type, transmitter)
                    {
                        this->construct(screen, screenWidth, screenHeight);
                    }

                    /**
                     * Constructor
                     *
                     * @param type Sensor type identifier
                     * @param transmitter Transmitter
                     * @param rtc RTC for DateTime
                     * @param screen LiquidCrystal screen
                     */
                    ScreenArduinoApplication(
                        unsigned char type,
                        Transmitter * transmitter,
                        RTC_DS1307 * rtc,
                        LiquidCrystal * screen
                    ) : ArduinoApplication(type, transmitter, rtc)
                    {
                        this->construct(screen, LCD_WIDTH, LCD_HEIGHT);
                    }

                    /**
                     * Constructor
                     *
                     * @param type Sensor type identifier
                     * @param transmitter Transmitter
                     * @param rtc RTC for DateTime
                     * @param screen LiquidCrystal screen
                     * @param screenWidth Screen width (number of chars)
                     * @param screenHeight Screen height (number of chars)
                     */
                    ScreenArduinoApplication(
                        unsigned char type,
                        Transmitter * transmitter,
                        RTC_DS1307 * rtc,
                        LiquidCrystal * screen,
                        unsigned int screenWidth,
                        unsigned int screenHeight
                    ) : ArduinoApplication(type, transmitter, rtc)
                    {
                        this->construct(screen, screenWidth, screenHeight);
                    }

                    /**
                     * Constructor
                     *
                     * @param type Sensor type identifier
                     * @param transmitter Transmitter
                     */
                    ScreenArduinoApplication(
                        unsigned char type,
                        Transmitter * transmitter
                    ) : ArduinoApplication(type, transmitter)
                    {
                        this->construct();
                    }

                    /**
                     * Constructor
                     *
                     * @param type Sensor type identifier
                     * @param transmitter Transmitter
                     * @param rtc RTC for DateTime
                     */
                    ScreenArduinoApplication(
                        unsigned char type,
                        Transmitter * transmitter,
                        RTC_DS1307 * rtc
                    ) : ArduinoApplication(type, transmitter, rtc)
                    {
                        this->construct();
                    }

                    /**
                     * Destructor
                     */
                    ~ScreenArduinoApplication()
                    {


                    }

                    /**
                     * Setup application
                     */
                    virtual void setup()
                    {
                        // Parent
                        ArduinoApplication::setup();

                        // Init screen
                        if (this->isUseScreen()) {
                            this->enableScreen();
                        }
                    }

                    /**
                     * Enable screen if available
                     */
                    void enableScreen()
                    {
                        if (this->hasScreen()) {
                            this->setUseScreen(true);
                            this->screen->begin(this->getScreenWidth(), this->getScreenHeight());
                            this->screen->display();
                        }
                    }

                    /**
                     * Disable screen if available
                     */
                    void disableScreen()
                    {
                        if (this->hasScreen()) {
                            this->screen->noDisplay();
                            this->setUseScreen(false);
                        }
                    }

                    /**
                     * Flag to indicate if screen is used
                     */
                    bool isUseScreen()
                    {
                        return this->useScreen;
                    }

                    /**
                     * Indicate if screen is used
                     */
                    void setUseScreen(bool flag)
                    {
                        this->useScreen = flag;
                    }

                    /**
                     * Get screen
                     */
                    LiquidCrystal * getScreen() {
                        return this->screen;
                    }

                    /**
                     * Set screen
                     */
                    void setScreen(LiquidCrystal * screen)
                    {
                        this->screen = screen;
                    }

                    /**
                     * Flag to indicate if a screen is available
                     */
                    bool hasScreen()
                    {
                        return this->screen != NULL;
                    }

                    /**
                     * Set screen width
                     */
                    void setScreenWidth(unsigned int width)
                    {
                        this->screenWidth = width;
                    }

                    /**
                     * Get screen width
                     */
                    unsigned int getScreenWidth()
                    {
                        return this->screenWidth;
                    }

                    /**
                     * Set screen height
                     */
                    void setScreenHeight(unsigned int height)
                    {
                        this->screenHeight = height;
                    }

                    /**
                     * Get screen height
                     */
                    unsigned int getScreenHeight()
                    {
                        return this->screenHeight;
                    }

                protected:
                    /**
                     * Global construct part
                     */
                    void construct(
                        LiquidCrystal * screen,
                        unsigned int screenWidth,
                        unsigned int screenHeight
                    ) {
                        this->setScreen(screen);
                        this->setUseScreen(true);
                        this->setScreenWidth(screenWidth);
                        this->setScreenHeight(screenHeight);
                    }

                    /**
                     * Global construct part when no usage of screen
                     */
                    void construct()
                    {
                        this->setUseScreen(false);
                    }

                    /**
                     * Screen
                     */
                    LiquidCrystal * screen = NULL;

                    /**
                     * Flag to indicate if screen is used
                     */
                    bool useScreen = false;

                    /**
                     * Screen width (in number of chars)
                     */
                    unsigned int screenWidth = LCD_WIDTH;

                    /**
                     * Screen height (in number of chars)
                     */
                    unsigned int screenHeight = LCD_HEIGHT;

                };
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_ARDUINO_SCREENARDUINOAPPLICATION_H
