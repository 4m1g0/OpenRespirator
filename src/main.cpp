
#include <Arduino.h>
#include "BasicStepperDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200

// All the wires needed for full functionality
#define DIR D5
#define STEP D6

// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

int rpms = 0;

void setup() {
    Serial.begin(115200);
    delay(5000);
    Serial.print("Write RPMs: ");
    rpms = Serial.parseInt();
    Serial.println();
    Serial.print("[OK] Setting new speed to "); Serial.print(rpms); Serial.println(" RPMs.");
    stepper.begin(rpms);
    stepper.startRotate(360);

    Serial.print("Write new RPMs: ");
}

void loop() {
  

    // motor control loop - send pulse and return how long to wait until next pulse
    unsigned wait_time_micros = stepper.nextAction();

    if (wait_time_micros < 100){
        // start rotating again
        stepper.startRotate(360);
    }

    if (Serial.available()){
        rpms = Serial.parseInt();

        // set new rpms and start rotating again
        stepper.setRPM(rpms);
        stepper.startRotate(360);
    }


}
