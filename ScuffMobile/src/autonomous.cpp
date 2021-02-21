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
  translateAndIntake(1550, 60, 1200);
  rotate(-135, 100);
  translate(1600, 100);
  scoreSingle(); //goal 1
  translate(-1100, 100);
  rotate(-90, 100);
  translateAndIntake(1150, 60, 1150);
  translate(-300, 100);
  rotate(0, 100);
  translateAndIntake(1700, 60, 1700);
  rotate(-90, 100);
  translate(400, 100);
  scoreDouble(); //goal 2
  translate(-500, 100);
  rotate(0, 100);
  translateAndIntake(2150, 60, 2150);
  translate(-50, 60);
  rotate(-45, 100);
  translate(1400, 100);
  scoreSingle(); //goal 3
  translate(-900, 100);
  rotate(90, 100);
  translateAndIntake(1350, 100, 1000);
  rotate(0, 100);
  translate(550, 100);
  scoreSingle(); //goal 4
  translate(-100, 100);
  rotate(90, 100);
  translateAndIntake(2400, 60, 2400);
  rotate(45, 100);
  translate(1500, 100);
  scoreSingle(); //goal 5
  translate(-1100, 100);
  rotate(90, 100);
  translateAndIntake(1150, 60, 1150);
  translate(-300, 100);
  rotate(180, 100);
  translateAndIntake(1650, 60, 1650);
  rotate(90, 100);
  translate(400, 100);
  scoreSingle();  //goal 6
  translate(-300, 100);
  rotate(180, 100);
  translate(1400, 100);
  rotate(90, 100);
  translateAndIntake(1250, 60, 1250);
  translate(-1000, 100);
  rotate(135, 100);
  translate(1500, 100);
  scoreSingle(); //goal 7
  translate(-900, 100);
}

void autonomous() {
  skills();
}
