#include "main.h"

void lrt() {
  deploy();
  startIntake(true, false);
  translate(1100, -45, 0.65, 80);
  setDrive(127, 127);
  pros::delay(200);
  setDrive(0, 0);
  stopIntake();
  pros::delay(200);
  scorer = 127; //goal 1
  indexer = 127;
  pros::delay(400);
  startIntake(false, true);
  scorer = 0;
  pros::delay(400);
  translate(-1700, -45, 5, 100);
  stopIntake();
  rotate(90);
  translateAndIntake(1550, 90, 5, 100, true);
  rotate(0);
  translateAndIntake(-1250, 0, 5, 100, true); //goal 2
  translate(100, 0, 5, 100);
  translate(1700, -180, 0.5, 60);
  translate(1850, -90, 1.2, 80);
  setDrive(80, 80);
  pros::delay(200);
  setDrive(0, 0);
  scorer = 127; //goal 3
  indexer = 127;
  pros::delay(400);
  scorer = 0;
  indexer = 0;
  translate(-1800, -90, 5, 100);
  rotate(-180);
  translate(4000, -135, 0.85, 100);
}

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
void autonomous() {
  lrt();
}
