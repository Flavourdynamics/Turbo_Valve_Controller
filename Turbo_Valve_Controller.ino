#include <Servo.h>
#include <FastLED_timers.h>

// Most adjustable settings should be here
#define servoPIN      9    // The control pin of the servo
#define maxangle      90   // Degrees of freedom of the servo
#define servooffset        // A fixed offset on the initial position of the servo [unused]
#define pospotPIN     A0   // Analog pin for reading servo position
#define dampenpotPIN  A1   // Analog pin for 

Servo servo;  // Create servo object

uint16_t posval;       // Stores the value read from the analog pin for servo position
uint8_t dampenval = 1; // Stores how much dampening is applied (higher is less movement)[can't be 0]

void setup() {////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.begin(9600);       // Initiate serial monitor
  servo.attach(servoPIN);   // attaches the servo on pin 9 to the servo object
}

void loop() {/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Measure intended position from analog reading (potentiometer/sensor)
  posval = analogRead(pospotPIN);               // reads the value of the potentiometer (value between 0 and 1023)
  posval = map(posval, 0, 1023, 0, maxangle);   // scale read value from an analogRead range of 0-1024 to the degrees of freedom of the servo
  
  // Measure intended amount of dampening from analog input (potentiometer)
  dampenval = analogRead(dampenpotPIN);         // reads a pot to determine how much dampening should be applied
  dampenval = map(dampenval, 0 , 1023, 1, 255); // map that value from an analogRead range of 0-1024 to a byte)[not including zero]
  
  EVERY_N_MILLIS(1){
    servo.write((posval*10)/(dampenval));       // sets the servo position according to the scaled value // set with an arbitrary ratio right now
  }
  EVERY_N_MILLIS(5){ // Print diagnostics
    Serial.print("Posval: ");
    Serial.print(posval);
    Serial.print(" --- Dampening: ");
    Serial.print(dampenval);
    Serial.print(" --- Dampened posval: ");
    Serial.println((posval*10)/(dampenval));
  }
}
