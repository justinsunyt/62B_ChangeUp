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
  int leftJoyStick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightJoyStick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  if (abs(leftJoyStick) < 10) {
    leftJoyStick = 0;
  }
  if (abs(rightJoyStick) < 10) {
    rightJoyStick = 0;
  }
  setDrive(leftJoyStick, rightJoyStick);
}

void translate(double degrees, double speed) {
  double initRotation = inertial.get_rotation();
  int direction = fabs(degrees) / degrees;
  double voltage = 20;

  resetDriveEncoders();
  while (avgDriveEncoderValue() < fabs(degrees)) {
    if (avgDriveEncoderValue() < fabs(degrees * 0.69)) {
      voltage = fmin(voltage * 1.1, speed * 1.27);
    } else {
      voltage = fmax(voltage * 0.92, speed * 0.32);
    }
    setDrive(voltage * direction - (inertial.get_rotation() - initRotation), voltage * direction + (inertial.get_rotation() - initRotation));
    pros::delay(10);
  }
  setDrive(0, 0);
  pros::delay(100);
}

void translateAndIntake(double degrees, double speed, double stopIntakeAt) {
  double initRotation = inertial.get_rotation();
  int direction = fabs(degrees) / degrees;
  double voltage = 20;

  resetDriveEncoders();
  intakeLeft = 127;
  intakeRight = 127;
  while (avgDriveEncoderValue() < fabs(degrees)) {
    if (avgDriveEncoderValue() < fabs(degrees * 0.69)) {
      voltage = fmin(voltage * 1.1, speed * 1.27);
    } else {
      voltage = fmax(voltage * 0.92, speed * 0.32);
    }
    setDrive(voltage * direction - (inertial.get_rotation() - initRotation), voltage * direction + (inertial.get_rotation() - initRotation));
    if (avgDriveEncoderValue() >= stopIntakeAt) {
      stopIntake();
    }
    pros::delay(10);
  }
  setDrive(0, 0);
  pros::delay(300);
  stopIntake();
}

void rotate(double degrees, double speed) {
  double initRotation = inertial.get_rotation();
  int direction = fabs(degrees) / degrees;
  double kP = 5;
  double kD = 15;
  double error = degrees - (inertial.get_rotation() - initRotation);
  double derivative;
  double voltage;
  double prevError;
  double done = 0;

  while (done < 1) {
    error = degrees - (inertial.get_rotation() - initRotation);
    derivative = error - prevError;
    prevError = error;
    voltage = speed / 100 * 1.27 * (error * kP + derivative * kD);
    setDrive(voltage, -voltage);
    if (fabs(error) < 2) {
      done += 0.2;
    }
    pros::delay(10);

  }
}
