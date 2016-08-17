//
// Created by Thibault PLET on 31/05/2016.
//

#ifndef COM_OSTERES_AUTOMATION_ARDUINO_COMPONENT_DATABUFFER_H
#define COM_OSTERES_AUTOMATION_ARDUINO_COMPONENT_DATABUFFER_H

namespace com {
    namespace osteres {
        namespace automation {
            namespace arduino {
                namespace component {
                    class DataBuffer {
                    public:
                        /**
                         * Constructor
                         */
                        DataBuffer()
                        {
                            // Init
                            this->bufferDelay = 10 * 1000; // ms
                            this->bufferTimePoint = millis();
                        }

                        /**
                         * Destructor
                         */
                        ~DataBuffer()
                        {
                            // Nothing
                        }

                        /**
                         * Reset buffer
                         */
                        virtual void reset()
                        {
                            this->resetBufferTimePoint();
                        }

                        /**
                         * Flag to indicate if buffer is considering as outdated
                         */
                        bool isOutdated()
                        {
                            return millis() - this->bufferTimePoint > this->getBufferDelay();
                        }

                        /**
                         * Get limit delay at which buffer is considering as outdated (in milliseconds)
                         */
                        unsigned long getBufferDelay()
                        {
                            return this->bufferDelay;
                        }

                        /**
                         * Set limit delay at which buffer is considered as outdated (in milliseconds)
                         */
                        void setBufferDelay(unsigned int value)
                        {
                            this->bufferDelay = value;
                        }
                    protected:
                        /**
                         * Reset buffer time point
                         */
                        void resetBufferTimePoint()
                        {
                            this->bufferTimePoint = millis();
                        }

                        /**
                         * Limit interval before buffer is considering as outdated (in milliseconds)
                         */
                        unsigned int bufferDelay;

                        /**
                         * Time point for buffer
                         */
                        unsigned long bufferTimePoint;
                    };
                }
            }
        }
    }
}


#endif //COM_OSTERES_AUTOMATION_ARDUINO_COMPONENT_DATABUFFER_H
