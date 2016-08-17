//
// Created by Thibault PLET on 28/05/2016.
//

#ifndef COM_OSTERES_ARDUINO_UTIL_STRINGCONVERTER_H
#define COM_OSTERES_ARDUINO_UTIL_STRINGCONVERTER_H

#include <string>

using std::string;

namespace com {
    namespace osteres {
        namespace arduino {
            namespace util {
                class StringConverter {
                public:
                    /**
                     * Converter string to String
                     */
                    static String toString(string s)
                    {
                        int len = s.length();
                        char v[len];
                        strcpy(v, s.c_str());

                        return String(v);
                    }
                };
            }
        }
    }
}


#endif //COM_OSTERES_ARDUINO_UTIL_STRINGCONVERTER_H
