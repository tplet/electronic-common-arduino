//
// Created by Thibault PLET on 06/05/2016.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_TRANSMISSION_REQUESTER_H
#define COM_OSTERES_AUTOMATION_ARDUINO_TRANSMISSION_REQUESTER_H

#include <RTClib/RTClib.h>
#include <com/osteres/automation/transmission/Requester.h>

using com::osteres::automation::transmission::Requester;

namespace com
{
    namespace osteres
    {
        namespace automation
        {
            namespace arduino
            {
                namespace transmission
                {
                    class ArduinoRequester : public Requester {
                    public:
                        /**
                     * Constructor
                     */
                        ArduinoRequester(RF24 * radio, unsigned long long writingChannel) : Requester(radio, writingChannel) {};

                        /**
                         * Destructor
                         */
                        ~ArduinoRequester() : ~Requester();

                        /**
                         * Set RTC object
                         */
                        ArduinoRequester *setRTC(RTC_DS1307 *rtc);

                        /**
                         * Flag to indicate if can use rtc
                         */
                        bool useRTC();

                    protected:
                        /**
                         * Prepare packet and send it only (no response attempted)
                         */
                        void doSend(Packet *packet)
                        {
                            // Datetime if possible and not already defined
                            if (this->useRTC() && packet->getDate() == 0) {
                                packet->setDate(this->rtc->now().unixtime());
                            }

                            Requester::doSend(packet);
                        }

                        /**
                         * RTC object (optional)
                         */
                        RTC_DS1307 *rtc = NULL;
                    };

                }
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_ARDUINO_TRANSMISSION_REQUESTER_H
