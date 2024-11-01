#include <Arduino.h>
const int trans_pin = 14; // Trig
const int recv_pin = 12;  // Echo
float dist_raw;           // distance variable

void getDistance()
{
    float duration; // time var

    digitalWrite(trans_pin, LOW); // ensure no errant transmission
    delayMicroseconds(5);

    digitalWrite(trans_pin, HIGH); // transmit
    delayMicroseconds(10);

    digitalWrite(trans_pin, LOW);       // stop transmission
    duration = pulseIn(recv_pin, HIGH); // listen for pulses

    dist_raw = duration * (340 * 100) / (2 * 1000000); // calculate distance
    /*
    d = c*delta(t)/2
    c = 340 m/s
    39.79 inch per meter
    duration is in microseconds, so 1*10^6 is divided
    */
    Serial.print(dist_raw);
    Serial.println(" cm");

    delay(100); // can alter based on needs of application
}