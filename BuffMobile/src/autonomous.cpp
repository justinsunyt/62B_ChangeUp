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
  translate(2350, -90);
  rotate(-135);
  translateAndIntake(1000, -135, false);

  //goal 2
  scorer = 127;
  indexer = 127;
  pros::delay(500);
  startIntake(false, false);
  pros::delay(500);
  scorer = 20;
  stopIntake();

  translate(-1650, -135);
  rotate(0);
  translateAndIntake(1300, 0, true);
  rotate(-90);

  //goal 3
  translate(-1350, -90);

  translate(200, -90);
  rotate(-230);
  translateFast(5000, -230);

  //goal 4
  scorer = 127;
  indexer = 127;
  pros::delay(1000);
  scorer = 0;
  indexer = 0;
}

void autonomous() {
  // lrt();
  translate(4000, 0);
  rotate(90);
  translate(-4000, 90);
  rotate(0);
  translate(-4000, 0);
  rotate(90);
  translate(4000, 90);
  rotate(0);
}
