
#ifndef Measure_h
#define Measure_h

#include <Wire.h>
#include <Adafruit_INA219.h>

#define MEASURE_SAMPLE_SIZE 128

struct Sample
{
    float voltage;
    float current;
    unsigned long time;
};

struct SampleBuffer
{
    Sample dataSamples[MEASURE_SAMPLE_SIZE];
    bool writing = false;
    bool reading = true;
};

class Measure
{
    private:

        Adafruit_INA219 ina219;

    public:
        
        //Sample dataSamples[MEASURE_SAMPLE_SIZE];
        SampleBuffer sbuffers[4];

        unsigned long readTime = 0;
        unsigned long printTime = 0;

        Measure();
        void init();
        void readSamples();
        void printSamples();
};

#endif