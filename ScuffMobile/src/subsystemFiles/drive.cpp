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

void translate(double degrees, double voltage) {
  double initRotation = inertial.get_rotation();
  int direction = fabs(degrees) / degrees;
  double output = 32;
  double prevValue;
  double stopped = 0;

  resetDriveEncoders();
  while (avgDriveEncoderValue() < fabs(degrees) && stopped < 1) {
    prevValue = avgDriveEncoderValue();
    pros::delay(10);
    if (avgDriveEncoderValue() < fmax(fabs(degrees) - 400, fabs(degrees) * 0.69)) {
      output = fmin(output * 1.1, voltage);
    } else {
      output = fmax(output * 0.93, voltage * 0.25);
    }
    setDrive(output * direction - (inertial.get_rotation() - initRotation), output * direction + (inertial.get_rotation() - initRotation));
    if (fabs(prevValue - avgDriveEncoderValue()) < 1) {
      stopped += 0.01;
    }
  }
  setDrive(0, 0);
  pros::delay(100);
}

void translateAndIntake(double degrees, double voltage, double stopIntakeAt) {
  double initRotation = inertial.get_rotation();
  int direction = fabs(degrees) / degrees;
  double output = 32;
  double prevValue;
  double stopped = 0;

  resetDriveEncoders();
  intakeLeft = 127;
  intakeRight = 127;
  while (avgDriveEncoderValue() < fabs(degrees) && stopped < 1) {
    prevValue = avgDriveEncoderValue();
    pros::delay(10);
    if (avgDriveEncoderValue() < fmax(fabs(degrees) - 400, fabs(degrees) * 0.69)) {
      output = fmin(output * 1.1, voltage);
    } else {
      output = fmax(output * 0.93, voltage * 0.25);
    }
    if (avgDriveEncoderValue() > stopIntakeAt) {
      stopIntake();
    }
    setDrive(output * direction - (inertial.get_rotation() - initRotation), output * direction + (inertial.get_rotation() - initRotation));
    if (fabs(prevValue - avgDriveEncoderValue()) < 1) {
      stopped += 0.02;
    }
  }
  setDrive(0, 0);
  pros::delay(500);
  stopIntake();
}

void rotate(double degrees, double voltage) {
  double initRotation = inertial.get_rotation();
  bool direction = fabs(degrees) / degrees == 1;
  double kP = 14;
  double kD = 56;
  double error;
  double prevError;
  double derivative;
  double output;
  double done = 0;

  while (done < 1) {
    prevError = degrees - (inertial.get_rotation() - initRotation);
    pros::delay(10);
    error = degrees - (inertial.get_rotation() - initRotation);
    derivative = error - prevError;
    output = direction ? fmin(voltage, error * kP + derivative * kD) : fmax(-voltage, error * kP + derivative * kD);
    setDrive(output, -output);
    if (fabs(error) < 1) {
      done += 0.1;
    }
  }
  setDrive(0, 0);
  pros::delay(100);
}
