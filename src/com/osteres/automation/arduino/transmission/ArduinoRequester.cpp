//
// Created by Thibault PLET on 06/05/2016.
//

#include "ArduinoRequester.h"

using namespace com::osteres::automation::arduino::transmission;

/**
 * RTC object setter
 */
ArduinoRequester * ArduinoRequester::setRTC(RTC_DS1307 * rtc) {
    this->rtc = rtc;

    return this;
}

/**
 * Flag to indicate if can use RTC object
 */
bool ArduinoRequester::useRTC() {
    return this->rtc != NULL;
}
