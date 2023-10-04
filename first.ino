#include <QTRSensors.h>
#define aphase 9
#define IN1 7
#define IN2 6
#define IN3 5
#define IN4 4
#define bphase 3
int button_calibration = A3;
int button_start = 2;

QTRSensors qtr;
int LAST_ERROR = 0;
const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

float K_P = 1;

float K_I = 0.06;

float K_D = 0.5;

void setup()
{
    Serial.begin(9600);
    pinMode(aphase, OUTPUT);
    pinMode(bphase, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(button_calibration, INPUT);
    pinMode(button_start, INPUT);
    digitalWrite(IN2, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(aphase, 0);
    analogWrite(bphase, 0);
    // put your setup code here, to run once:
    qtr.setTypeRC();
    qtr.setSensorPins((const uint8_t[]){10, 11, 12, A0, A1, A2, A4, A5}, SensorCount);
    delay(500);
    pinMode(LED_BUILTIN, OUTPUT);

    // while(digitalRead(button_calibration)==LOW){

    // }
    digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode

    // analogRead() takes about 0.1 ms on an AVR.
    // 0.1 ms per sensor * 4 samples per sensor read (default) * 6 sensors
    // * 10 reads per calibrate() call = ~24 ms per calibrate() call.
    // Call calibrate() 400 times to make calibration take about 10 seconds.
    for (uint16_t i = 0; i < 400; i++)
    {
        qtr.calibrate();
    }
    digitalWrite(LED_BUILTIN, LOW);
    // while(digitalRead(button_start)==LOW){

    // }
}
void movement(int speedA, int speedB)
{
    if (speedA < 0)
    {
        speedA = 0 - speedA;
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
    }

    if (speedB < 0)
    {
        speedB = 0 - speedB;
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
    }

    analogWrite(aphase, speedA);
    analogWrite(bphase, speedB);
}

void loop()
{
    PID_control_system();
}

void PID_control_system()
{
    uint16_t position_of_the_line = qtr.readLineWhite(sensorValues);
    int ERROR = 3500 - position_of_the_line;

    // PID BABAJI
    int P = ERROR;
    int I = ERROR + I;
    int D = LAST_ERROR - ERROR;
    LAST_ERROR = ERROR;

    int MOTOR_SPEED_CHANGE = P * K_P + I * K_I + D * K_D;

    int speedA = 35 + MOTOR_SPEED_CHANGE;
    int speedB = 35 - MOTOR_SPEED_CHANGE;
    if (speedA > 45)
    {
        speedA = 45;
    }
    if (speedB > 45)
    {
        speedB = 45;
    }
    if (speedA < -10)
    {
        speedA = -10;
    }
    if (speedB < -10)
    {
        speedB = -10;
    }
    movement(speedA, speedB);
}