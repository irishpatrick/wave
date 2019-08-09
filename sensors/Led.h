#pragma once

class Led
{
public:
    Led();
    ~Led();

    void init(int, bool);
    void on();
    void off();
    void update();
    void blink();
    void blink_async();
    void setBrightness(int);

private:
    int digital;
    int pwm;
    int pin;
    int mode;
};
