#include "main.h"

void setIntakeIndexerMotors() {
  int intakePower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) * 1.5);
  intakeLeft = intakePower;
  intakeRight = intakePower;
  scorer = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1));
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) == 1 || controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) == 1) {
    indexer = -127;
  } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) == 1 || controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) == 1) {
    indexer = 127;
  } else {
    indexer = 0;
  }
}

void deploy() {
  intakeLeft = 127;
  intakeRight = 127;
  pros::delay(800);
  intakeLeft = 0;
  intakeRight = 0;
}

void startIntake(bool direction, bool i) {
  int dir = direction ? 1 : -1;
  intakeLeft = dir * 127;
  intakeRight = dir * 127;
  if (i) {
    indexer = dir * 127;
  }
}

void stopIntake() {
  intakeLeft = 0;
  intakeRight = 0;
  indexer = 0;
}
