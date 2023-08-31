#pragma once
#include <math.h>



class Vector3 {
private:
	double _x;
	double _y;
	double _z;
public:
	Vector3(double x, double y, double z) : _x(x), _y(y), _z(z)
		{}
	double getX() {
		return _x;
	}
	double getY() {
		return _y;
	}
	double getZ() {
		return _z;
	}
};

class ICurve3D {
public:
	virtual ~ICurve3D() {}
	virtual Vector3 getPointCoordinates(double param) = 0;
	virtual Vector3 getPointDerivative(double param) = 0;
};

class Circle : public ICurve3D {
private:
	double _radius;
public:
	 ~Circle() {}
	Circle(double radius) : _radius(radius)
		{}
	double getRadius();
	Vector3 getPointCoordinates(double param) override;
	Vector3 getPointDerivative(double param) override;
};

class Ellipse : public ICurve3D {
private:
	double _semi_major_axis, _semi_minor_axis;
public:
	~Ellipse() {}
	Ellipse(double semi_major_axis, double semi_minor_axis) : 
		_semi_major_axis(semi_major_axis),
		_semi_minor_axis(semi_minor_axis)
		{}
	Vector3 getPointCoordinates(double param) override;
	Vector3 getPointDerivative(double param) override;
};

class Helix : public ICurve3D {
private:
	double _radius, _slope;
public:
	~Helix() {}
	Helix(double radius, double slope) : _radius(radius), _slope(slope)
	{}
	Vector3 getPointCoordinates(double param) override;
	Vector3 getPointDerivative(double param) override;
};

