#include "main.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void lrt() {
  //goal 1
  deploy();

  translate(500, 0);
  rotate(-90);
  translate(2500, -90);
  rotate(-135);
  translateAndIntake(1200, -135, false);

  //goal 2
  scorer = 127;
  indexer = 127;
  pros::delay(1000);
  startIntake(false, false);
  pros::delay(200);
  scorer = 0;
  stopIntake();

  translate(-1900, -135);
  rotate(0);
  translateAndIntake(1500, 0, true);
  rotate(-90);

  //goal 3
  translate(-1400, -90);

  translate(400, -90);
  rotate(-180);
  double encoder;
  double prevEncoder;
  double derivative;
  double max = 40;
  double done = 0;
  double sector = 1;
  resetDriveEncoders();
  while (done < 1) {
    prevEncoder = avgDriveEncoderValue();
    pros::delay(10);
    encoder = avgDriveEncoderValue();
    derivative = encoder - prevEncoder;
    if (sector == 1) {
      setDrive(max - (inertial.get_rotation() + 250) * 2, max + (inertial.get_rotation() + 250) * 2);
      if (fabs(inertial.get_rotation() + 250) < 1) {
        sector += 1;
      }
    } else {
      setDrive(max - (inertial.get_rotation() + 225) * 2, max + (inertial.get_rotation() + 225) * 2);
      if (fabs(inertial.get_rotation() + 225) < 1) {
        sector += 1;
      }
    }
    if (fabs(derivative) < 2) {
      done += 0.2;
    }
    if (max < 127 && sector < 3) {
      max += 4;
    }
    if (sector == 3) {
      max -= 2;
    }
   }
  setDrive(0, 0);

  //goal 4
  scorer = 127;
  indexer = 127;
  pros::delay(1000);
  scorer = 0;
  indexer = 0;
}

void autonomous() {
  lrt();
}
