#include <Arduino.h>
#include "Photocell.h"
#include "Led.h"

Led red;
Led yellow;
Led green;

Photocell left;
Photocell right;

int wait = 0;
int reset = 0;
int timeout = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(0, INPUT);
    left.init(0);
    left.setThreshold(50);
    right.setThreshold(50);
    right.init(1);

    green.init(2, false);
    yellow.init(3, false);
    red.init(4, false);
}

void loop()
{
    int calibrate = digitalRead(7);

    if (calibrate == HIGH)
    {
        left.calibrate();
        right.calibrate();
    }
    else
    {
        left.poll();
        right.poll();

       int lt = left.triggered();
       int rt = right.triggered();
       if (wait != 0 && !(lt && rt))
       {
           timeout++;
           if (timeout > 10)
           {
               red.on();
               reset = 1;
           }
           yellow.on();
           delay(50);
           yellow.off();
       }

       if ((lt && rt) || (!lt && !rt))
       {
           if (reset)
           {
               red.off();
               reset = 0;
               wait = 0;
               timeout = 0;
               delay(100);
           }
       }
       else if (lt && !reset)
       {
           if (wait < 0)
           {
               Serial.write('l');
               green.on();
               delay(20);
               green.off();
               reset = 1;
           }
           else
           {
               wait = 1;
               delay(100);
           }
       }
       else if (rt && !reset)
       {
           if (wait > 0)
           {
               Serial.write('r');
               green.on();
               delay(20);
               green.off();
               reset = 1;
           }
           else
           {
               wait = -1;
               delay(100);
           }
       }
    }
}
