#include "main.h"

void setDrive(int left, int right) {
  driveLeftFront = left;
  driveLeftBack = left;
  driveRightFront = right;
  driveRightBack = right;
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
}

void translate(double distance, double angle) {
  bool direction = fabs(distance) / distance == 1;
  double kP = 0.25;
  double kD = 0;
  double error;
  double prevError;
  double derivative;
  double output;
  double done = 0;
  resetDriveEncoders();
  while (done < 1) {
    prevError = fabs(distance) / distance * (fabs(distance) - avgDriveEncoderValue());
    pros::delay(10);
    error = fabs(distance) / distance * (fabs(distance) - avgDriveEncoderValue());
    derivative = error - prevError;
    output = direction ? fmin(80, error * kP + derivative * kD) : fmax(-80, error * kP + derivative * kD);
    setDrive(output - (inertial.get_rotation() - angle), output + (inertial.get_rotation() - angle));
    if (fabs(error) < 5 || fabs(derivative) < 5) {
      done += 0.1;
    }
  }
  setDrive(0, 0);
  pros::delay(100);
}

void translateDumb(double distance) {
  bool direction = fabs(distance) / distance == 1;
  double kP = 0.25;
  double kD = 0;
  double error;
  double prevError;
  double derivative;
  double output;
  double done = 0;
  resetDriveEncoders();
  while (done < 1) {
    prevError = fabs(distance) / distance * (fabs(distance) - avgDriveEncoderValue());
    pros::delay(10);
    error = fabs(distance) / distance * (fabs(distance) - avgDriveEncoderValue());
    derivative = error - prevError;
    output = direction ? fmin(127, error * kP + derivative * kD) : fmax(-127, error * kP + derivative * kD);
    setDrive(output, output);
    if (fabs(error) < 5 || fabs(derivative) < 5) {
      done += 0.1;
    }
  }
  setDrive(0, 0);
  pros::delay(100);
}

void translateAndIntake(double distance, double angle, bool indexer) {
  startIntake(true, indexer);
  translate(distance, angle);
  stopIntake();
}

void translateAndOuttake(double distance, double angle) {
  bool direction = fabs(distance) / distance == 1;
  double kP = 0.25;
  double kD = 0;
  double error;
  double prevError;
  double derivative;
  double output;
  double done = 0;
  resetDriveEncoders();
  while (done < 1) {
    prevError = fabs(distance) / distance * (fabs(distance) - avgDriveEncoderValue());
    pros::delay(10);
    error = fabs(distance) / distance * (fabs(distance) - avgDriveEncoderValue());
    derivative = error - prevError;
    output = direction ? fmin(80, error * kP + derivative * kD) : fmax(-80, error * kP + derivative * kD);
    setDrive(output - (inertial.get_rotation() - angle), output + (inertial.get_rotation() - angle));
    if (fabs(error) < 5 || fabs(derivative) < 5) {
      done += 0.1;
    }
    if (fabs(error) < 400) {
      startIntake(false, false);
    }
  }
  setDrive(0, 0);
  pros::delay(100);
  stopIntake();
}

void rotate(double angle) {
  bool direction = fabs(angle - inertial.get_rotation()) / (angle - inertial.get_rotation()) == 1;
  double kP = 8;
  double kD = 36;
  double error;
  double prevError;
  double derivative;
  double output;
  double done = 0;

  while (done < 1) {
    prevError = angle - inertial.get_rotation();
    pros::delay(10);
    error = angle - inertial.get_rotation();
    derivative = error - prevError;
    output = direction ? fmin(80, error * kP + derivative * kD) : fmax(-80, error * kP + derivative * kD);
    setDrive(output, -output);
    if (fabs(error) < 1 || fabs(derivative) < 0.2) {
      done += 0.1;
    }
  }
  setDrive(0, 0);
  pros::delay(100);
}
