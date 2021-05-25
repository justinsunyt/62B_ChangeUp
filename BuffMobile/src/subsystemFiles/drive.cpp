#include "main.h"

void setDrive(int left, int right) {
  driveLeftFront = left;
  driveLeftBack = left;
  driveRightFront = right;
  driveRightBack = right;
}

void setBrakeMode(pros::motor_brake_mode_e_t mode) {
  driveLeftFront.set_brake_mode(mode);
  driveLeftBack.set_brake_mode(mode);
  driveRightFront.set_brake_mode(mode);
  driveRightBack.set_brake_mode(mode);
}

void resetDriveEncoders() {
  driveLeftFront.tare_position();
  driveLeftBack.tare_position();
  driveRightFront.tare_position();
  driveRightBack.tare_position();
}

double avgDriveEncoderValue() {
  return (fabs(driveLeftFront.get_position()) + fabs(driveLeftBack.get_position()) + fabs(driveRightFront.get_position()) + fabs(driveRightBack.get_position())) / 4;
}

void setDriveMotors() {
  int leftJoyStick = abs(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) < 10 ? 0 : controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightJoyStick = abs(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)) < 10 ? 0 : controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  setDrive(leftJoyStick, rightJoyStick);
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
    if (driveLeftFront.get_brake_mode() == pros::E_MOTOR_BRAKE_COAST) {
      setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    } else {
      setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    }
  }
}

void translate(double distance, double angle, double correction, double voltage) {
  bool direction = fabs(distance) / distance == 1;
  double kP = fabs(distance) < 2000 ? 1.467 / (pow(fabs(distance), 0.3)) : 0.15;
  double error;
  double prevError;
  double derivative;
  double output;
  double max = 40;
  double done = 0;
  resetDriveEncoders();
  while (done < 5) {
    prevError = fabs(distance) / distance * (fabs(distance) - avgDriveEncoderValue());
    pros::delay(10);
    error = fabs(distance) / distance * (fabs(distance) - avgDriveEncoderValue());
    derivative = error - prevError;
    output = direction ? fmin(max, error * kP) : fmax(-max, error * kP);
    setDrive(output - (inertial.get_rotation() - angle) * correction, output + (inertial.get_rotation() - angle) * correction);
    if (fabs(derivative) < 2) {
      done += 1;
    }
    if (max < voltage) {
      max += 4;
    }
  }
  setDrive(0, 0);
}

void translateAndIntake(double distance, double angle, double correction, double voltage, bool indexer) {
  startIntake(true, indexer);
  translate(distance, angle, correction, voltage);
  stopIntake();
}

void rotate(double angle) {
  bool direction = fabs(angle - inertial.get_rotation()) / (angle - inertial.get_rotation()) == 1;
  double kP = 6;
  double kD = 30;
  double error;
  double prevError;
  double derivative;
  double output;
  double done = 0;

  while (done < 5) {
    prevError = angle - inertial.get_rotation();
    pros::delay(10);
    error = angle - inertial.get_rotation();
    derivative = error - prevError;
    output = direction ? fmin(100, error * kP + derivative * kD) : fmax(-100, error * kP + derivative * kD);
    setDrive(output, -output);
    if (fabs(error) < 2) {
      done += 1;
    }
  }
  setDrive(0, 0);
}
