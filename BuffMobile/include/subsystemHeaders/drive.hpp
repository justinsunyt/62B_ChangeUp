#include "main.h"

void setDrive();

void resetDriveEncoders();

void setDriveMotors();

void translate(double distance, double angle);

void translateFast(double distance, double angle);

void translateAndIntake(double distance, double angle, bool indexer);

void translateAndOuttake(double distance, double angle);

void rotate(double angle);
