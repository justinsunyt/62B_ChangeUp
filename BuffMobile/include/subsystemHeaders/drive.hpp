#include "main.h"

void setDrive(int left, int right);

void resetDriveEncoders();

double avgDriveEncoderValue();

void setDriveMotors();

void translate(double distance, double angle);

void translateAndIntake(double distance, double angle, bool indexer);

void rotate(double angle);
