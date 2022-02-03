
#include "Measure.h"

Measure::Measure()
{
    //sbuffers[0].logged = true;
}

void Measure::init()
{
    this->ina219 = Adafruit_INA219(0x40);
    this->ina219.begin();

    // nastavení kalibrace, k dispozici jsou 3 režimy
    // režim 32V a 2A má největší rozsahy, ale nejmenší přesnost
    //ina219.setCalibration_32V_2A();
    // režim 32V a 1A má lepší rozlišení průchozího proudu
    //ina219.setCalibration_32V_1A();
    // režim 16V a 400mA  má nejlepší rozlišení proudu i napětí
    this->ina219.setCalibration_16V_400mA();

     Wire.setClock(80000000);

    Serial.println("Init done!");
}

void Measure::readSamples()
{
    SampleBuffer * sbuff = nullptr;

    for (size_t i = 0; i < 4; i++)
    {
        if (!sbuffers[i].writing && sbuffers[i].reading)
        {
            sbuff = &sbuffers[i];
            break;
        }
    }

    if (sbuff == nullptr) return;
    
    unsigned long readTimer = millis();

    for (uint32_t i = 0; i < MEASURE_SAMPLE_SIZE; i++)
    {
        sbuff->dataSamples[i].current = this->ina219.getCurrent_mA();
        sbuff->dataSamples[i].voltage = ina219.getBusVoltage_V();
        sbuff->dataSamples[i].time = millis();
    }

    sbuff->writing = true;
    sbuff->reading = false;

    readTime = millis() - readTimer;
    Serial.printf("Read took %lums\n", readTime);
    /*
    // načtení všech dostupných údajů do proměnných
    napetiVstup = ina219.getBusVoltage_V();
    napetiBocnik = ina219.getShuntVoltage_mV();
    napetiZatez = napetiVstup + (napetiBocnik / 1000);
    proud = ina219.getCurrent_mA();
    */
}

void Measure::printSamples()
{
    SampleBuffer * sbuff = nullptr;

    for (size_t i = 0; i < 4; i++)
    {
        if (sbuffers[i].writing && !sbuffers[i].reading)
        {
            sbuff = &sbuffers[i];
            break;
        }
    }

    if (sbuff == nullptr) return;

    unsigned long printTimer = millis();

    for (uint32_t i = 0; i < MEASURE_SAMPLE_SIZE; i++)
    {
        unsigned long time  = sbuff->dataSamples[i].time;
        float curr          = sbuff->dataSamples[i].current;
        Serial.printf("[%d] %lums current: %.2fmA\n", i,time, curr);
    }

    sbuff->writing = false;
    sbuff->reading = true;

    printTime = millis() - printTimer;
    Serial.printf("Print took %lums\n", printTime);
}
