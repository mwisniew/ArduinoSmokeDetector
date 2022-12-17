# ArduinoSmokeDetector
Smoke detector based on Arduino

This is a smoke detector based on MH - MQ Flying Fish sensor and a buzzer.

Sensor pins (sensor pin -> arduino pin - I/O):
  - A0 -> A5 - analog input
  - GND -> GND - grounding
  - VCC -> 5V - voltage

Buzzer pins:
  - (+) -> D8 - digital output
  - (-) -> GND - grounding
  
Use resistors at will.

Feel free to modify the code to suit you, the pins I provided here will work "out of the box". The code was created for Arduino Uno, so keep in mind that other boards may have different pins. Just remember that the smoke detector is connected to an analog port!

Have fun :)
