#include <Arduino.h>
#include <Servo.h>

enum MODE_t
  {
    MODE_NO  = 0,
    MODE_ORG,
    MODE_DREIECK,
    MODE_TOGGLE,
    MODE_ANZ
  };

enum DIR_t
  {
    DIR_DOWN = 0,
    DIR_UP
  };

enum POS_t
  {
    POS_DEF = 0,
    POS_L   = -20,
    POS_H   = 200
  };
static const int  servoPin = 16;

//static int        mode     = MODE_ORG;
//static int        mode     = MODE_DREIECK;
static int        mode     = MODE_TOGGLE;
static int        posAkt   = POS_DEF;
static int        dir      = DIR_UP;

Servo servo1;

void setup()
  {
    Serial.begin(115200);
    servo1.attach(servoPin, -1, POS_L, POS_H);
    servo1.write(posAkt);
  }

void loop()
  {
    switch (mode)
      {
        case MODE_ORG:// hin und herfahren mit Pause
          for(int posDegrees = 0; posDegrees <= POS_H; posDegrees++)
            {
              servo1.write(posDegrees);
              Serial.println(posDegrees);
              usleep(10000);
            }
          sleep(1);
          for(int posDegrees = POS_L; posDegrees >= 0; posDegrees--)
            {
              servo1.write(posDegrees);
              Serial.println(posDegrees);
              usleep(10000);
            }
          sleep(1);
          break;
        case MODE_DREIECK:// hin und herfahren ohne Pause
          if(dir == DIR_UP)
            {
              Serial.print(" UP   ");
              if (++posAkt >= POS_H) { dir = DIR_DOWN; }
            }
          else if(dir == DIR_DOWN)
            {
              Serial.print(" DOWN ");
              if (--posAkt <= POS_L) { dir = DIR_UP; }
            }
          else
            {
              Serial.println(" IDLE ");
            }
          servo1.write(posAkt);
          Serial.println(posAkt);
          usleep(10000);
          break;
        case MODE_TOGGLE:
          if(dir == DIR_UP)
            {
              Serial.print(" UP   ");
              posAkt = POS_H;
              dir = DIR_DOWN;
            }
          else if(dir == DIR_DOWN)
            {
              Serial.print(" DOWN ");
              posAkt = POS_L;
              dir = DIR_UP;
            }
          else
            {
              Serial.println(" IDLE ");
            }
          servo1.write(posAkt);
          Serial.println(posAkt);
          usleep(1500000);
          break;
        default: break;
      }

  }