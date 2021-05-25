#include "main.h"

void setDrive(int left, int right);

void setBrakeMode(pros::motor_brake_mode_e_t mode);

void resetDriveEncoders();

double avgDriveEncoderValue();

void setDriveMotors();

void translate(double distance, double angle, double correction, double voltage);

void translateAndIntake(double distance, double angle, double correction, double voltage, bool indexer);

void rotate(double angle);
