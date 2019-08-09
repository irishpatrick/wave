#pragma once

class Photocell
{
public:
    Photocell();
    ~Photocell();

    void init(int);
    void poll();
    void calibrate();
    void setThreshold(int);

    int read();
    int get();
    int peaked();
    int triggered();

private:
    int m_val;
    int m_last;
    int m_min;
    int m_max;
    int m_pin;
    int m_delta;
    int m_last_delta;
    int m_th;
};
