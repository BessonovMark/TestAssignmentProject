#pragma once
#include "Curves.h"
#include <iostream>


double Circle::getRadius() {
	return _radius;
}

Vector3 Circle::getPointCoordinates(double param) {
	double x = _radius * cos(param);
	double y = _radius * sin(param);
	double z = 0.0;
	return Vector3(x, y, z);
}

Vector3 Circle::getPointDerivative(double param) {
	double x = -1.0 * _radius * sin(param);
	double y = _radius * cos(param);
	double z = 0.0;
	return Vector3(x, y, z);
}

Vector3 Ellipse::getPointCoordinates(double param) {
	double x = _semi_major_axis * cos(param);
	double y = _semi_minor_axis * sin(param);
	double z = 0.0;
	return Vector3(x, y, z);
}

Vector3 Ellipse::getPointDerivative(double param) {
	double x = -1.0 * _semi_major_axis * sin(param);
	double y = _semi_minor_axis * cos(param);
	double z = 0.0;
	return Vector3(x, y, z);
}

Vector3 Helix::getPointCoordinates(double param) {
	double x = _radius * cos(param);
	double y = _radius * sin(param);
	double z = _slope * param;
	return Vector3(x, y, z);
}

Vector3 Helix::getPointDerivative(double param) {
	double x = -1.0 * _radius * sin(param);
	double y = _radius * cos(param);
	double z = _slope;
	return Vector3(x, y, z);
}