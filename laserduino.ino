int lastMove = 1;
bool updateLastMove = false;
int dc = 255;
bool state = false;

void setup() {
  TCCR2B = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00);
  pinMode(3, OUTPUT);
  pinMode(2,INPUT_PULLUP);
  digitalWrite(3, HIGH);
}

void loop() {

  int sensorValue = digitalRead(2);
  if (sensorValue == 0)
  {
    delay(500);
    if (digitalRead(2) == 0)
    {
      updateLastMove = true;
      if (lastMove == 1)
      {
        while (digitalRead(2) == 0)
        {
          dc = dc - 1;
          analogWrite(3, dc);
          if (dc == 0)
          {
            state = false;
            while (digitalRead(2) == 0)
            {
              delay(100);
            }
          }
          delay(20);
        }
      }
      else
      {
        while (digitalRead(2) == 0)
        {
          dc = dc + 1;
          state = true;
          analogWrite(3, dc);
          if (dc == 255)
          {
            while (digitalRead(2) == 0)
            {
              delay(100);
            }
          }
          delay(20);
        }
      }
    }
    else
    {
      if (state == false)
      {
        state = true;
        if (dc == 0) dc = 255;
        analogWrite(3, dc);
      }
      else
      {
        state = false;
        digitalWrite(3, LOW);
      }
    }
  }
  if (updateLastMove == true)
  {
    if (lastMove == 1) lastMove = 0; else lastMove = 1;
    updateLastMove = false;
  }
}
