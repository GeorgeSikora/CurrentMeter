#include <Arduino.h>
#include <Measure.h>

Measure meas = Measure();

void tPrint (void * parameter)
{
    for(;;)
    {
        //meas.printSamples();
        //vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void tRead (void * parameter)
{
    for(;;)
    {
        meas.readSamples();
        //vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void setup()
{
    Serial.begin(921600);

    meas.init();

    /*
    xTaskCreate(
        tPrint,    // Function that should be called
        "Print data task",   // Name of the task (for debugging)
        4096,            // Stack size (bytes)
        NULL,            // Parameter to pass
        1,               // Task priority
        NULL             // Task handle
    );
    */
    
    xTaskCreate(
        tRead,    // Function that should be called
        "Read data task1",   // Name of the task (for debugging)
        4096,            // Stack size (bytes)
        NULL,            // Parameter to pass
        1,               // Task priority
        NULL             // Task handle
    );
}

void loop()
{
    meas.printSamples();
    //meas.readSamples();

    //meas.printSamples();
}