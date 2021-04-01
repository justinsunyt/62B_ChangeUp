#include "main.h"

void setIntakeIndexerMotors() {
  int intakePower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1));
  intakeLeft = intakePower;
  intakeRight = intakePower;
  scorer = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1));
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) == 1 || controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) == 1) {
    indexer = 127;
  } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) == 1 || controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) == 1) {
    indexer = -127;
  } else {
    indexer = 0;
  }
}

void deploy() {
  scorer = 127;
  pros::delay(100);
  scorer = 20;
}

void startIntake(bool direction, bool indexer) {
  int dir = direction ? 1 : -1;
  intakeLeft = dir * 127;
  intakeRight = dir * 127;
  if (indexer) {
    indexer = dir * 60;
  }
}

void stopIntake() {
  intakeLeft = 0;
  intakeRight = 0;
  indexer = 0;
}

void score(int balls) {
  if (balls == 1) {
    scorer = 127;
    indexer = 127;
    pros::delay(1000);
    scorer = 20;
    indexer = 0;
    pros::delay(100);
  } else if (balls == 2) {
    scorer = 127;
    indexer = 127;
    pros::delay(200);
    indexer = 0;
    pros::delay(200);
    scorer = 20;
    pros::delay(100);
  } else {
    scorer = 127;
    pros::delay(400);
    scorer = 20;
    pros::delay(100);
  }
}
