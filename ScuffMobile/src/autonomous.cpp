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
  translateAndIntake(1700, 0);
  rotate(-135);
  translate(1600, -135);
  score(2); //goal 1
  translate(-1450, -135);
  rotate(-90);
  translateAndIntake(1100, -90);
  translate(-500, -90);
  rotate(0);
  translateAndIntake(1850, 0);
  rotate(-90);
  translate(400 ,-90);
  score(3); //goal 2
  translate(-800, -90);
  rotate(0);
  translateAndIntake(2150, 0);
  rotate(-45);
  translate(1500, -45);
  score(3); //goal 3
  translate(-1000, -45);
  rotate(90);
  translate(2200, 90);
  rotate(0);
  translate(700, 0);
  score(2); //goal 4
  translate(-250, 0);
  rotate(90);
  translateAndIntake(2500, 90);
  rotate(45);
  translate(1500, 45);
  score(2); //goal 5
  translate(-1450, 45);
  rotate(90);
  translateAndIntake(1100, 90);
  translate(-500, 90);
  rotate(180);
  translateAndIntake(1850, 180);
  rotate(90);
  translate(400, 90);
  score(3);  //goal 6
  translate(-400, 90);
  rotate(180);
  translate(2000, 180);
  translate(-200, 180);
  rotate(90);
  translateAndIntake(1100, 90);
  translate(-1100, 90);
  rotate(135);
  translate(1600, 135);
  score(3); //goal 7
  translate(-2400, 135);
  rotate(270);
  translateAndIntake(1200, 270);
  rotate(180);
  translate(1500, 180);
  score(3); //goal 8
  translate(-300, 180);
  rotate(10);
  intakeLeft = -127;
  intakeRight = -127;
  translate(1200, 0);
  translateDumb(800);
  translateDumb(-600);
  translateDumb(800);
  translateDumb(-600);
  translateDumb(800);
  score(2); //goal 9
  score(1); //goal 9
  translateDumb(-600);
  stopIntake();
}

void autonomous() {
  skills();
}
