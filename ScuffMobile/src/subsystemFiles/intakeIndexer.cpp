#include "main.h"

void setIntakeIndexerMotors() {
  int intakePower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1));
  intakeLeft = intakePower;
  intakeRight = intakePower;
  int indexerTopPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1));
  indexerTop = indexerTopPower == 0 ? 20 : indexerTopPower;
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) == 1 || controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) == 1) {
    indexerBottom = 127;
  } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) == 1) {
    indexerBottom = 127;
  } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) == 1) {
    indexerBottom = -127;
  } else {
    indexerBottom = 0;
  }
}

void deploy() {
  indexerTop = 127;
  pros::delay(100);
  indexerTop = 20;
}

void startIntake() {
  intakeLeft = 127;
  intakeRight = 127;
  indexerBottom = 127;
}

void stopIntake() {
  intakeLeft = 0;
  intakeRight = 0;
  indexerBottom = 0;
}

void score(int balls) {
  indexerBottom = 127;
  indexerTop = 127;
  pros::delay(150 + 100 * balls);
  indexerBottom = 0;
  pros::delay(150 + 100 * balls);
  indexerTop = 20;
}
