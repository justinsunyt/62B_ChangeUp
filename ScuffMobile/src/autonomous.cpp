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

void skills() {
  deploy();
  translateAndIntake(1650, 80, 1000);
  rotate(-135, 100);
  translate(1650, 100);
  score(1);
  translate(-1300, 100);
  rotate(45, 100);
  translateAndIntake(1100, 80, 1100);
  translate(-250, 100);
  rotate(90, 100);
  translateAndIntake(1900, 60, 1900);
  rotate(-90, 100);
  translate(300, 100);
  score(2);
  translate(-500, 100);
  rotate(90, 100);
  translateAndIntake(2100, 60, 2100);
  rotate(-45, 100);
  translate(1500, 100);
  score(1);
  translate(-900, 100);
}

void autonomous() {
  skills();
}
