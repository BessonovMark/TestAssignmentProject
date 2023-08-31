#define _USE_MATH_DEFINES

#include "Curves.h"
#include <memory>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <random>
#include <fstream>
#include <iomanip>
#include <algorithm>


int main() {
	double lower_bound = 0.0;
	double upper_bound = 100.0;
	std::uniform_real_distribution<double> random_double_unif(lower_bound, upper_bound);
	std::uniform_int_distribution<int> random_curve_unif(0, 2);
	std::default_random_engine re;

	//2. Populate a container
	std::vector<std::shared_ptr<ICurve3D>> curve_list;
	for (int i = 0; i < 100; ++i) {
		int random_curve_type = random_curve_unif(re);
		switch (random_curve_type) {
		case 0: {
			std::shared_ptr<ICurve3D> circle_rand = std::make_shared<Circle>(random_double_unif(re));
			curve_list.push_back(std::move(circle_rand));
			break;
		}
		case 1: {
			std::shared_ptr<ICurve3D> ellipse_rand = std::make_shared<Ellipse>(random_double_unif(re), random_double_unif(re));
			curve_list.push_back(std::move(ellipse_rand));
			break;
		}
		case 2: {
			std::shared_ptr<ICurve3D> helix_rand = std::make_shared<Helix>(random_double_unif(re), random_double_unif(re));
			curve_list.push_back(std::move(helix_rand));
			break;
		}
		}
	}
	//3. Print coordinates of points and derivatives of all curves in the container at t=PI/4
	std::cout << std::setprecision(4) << std::fixed;

	for (int i = 0; i < curve_list.size(); i++) {
		Vector3 coordinates = curve_list[i]->getPointCoordinates(M_PI_4);
		Vector3 derivative = curve_list[i]->getPointDerivative(M_PI_4);
		std::cout << std::setw(15) << std::left << (typeid(*curve_list[i].get())).name() << " t = PI / 4: P("
			<< coordinates.getX() << ", " << coordinates.getY() << ", " << coordinates.getZ() << "), " <<
			"P'(" << derivative.getX() << ", " << derivative.getY() << ", " << derivative.getZ() << ')' << std::endl;
	}

	//4. Populate a second container that would contain only circles from the first container. 
	// Make sure the second container shares(i.e. not clones) circles of the first one, e.g.via pointers.
	std::vector<std::shared_ptr<Circle>> circle_list;
	for (int i = 0; i < curve_list.size(); ++i) {
		if (std::dynamic_pointer_cast<Circle>(curve_list[i])){
			circle_list.push_back(std::dynamic_pointer_cast<Circle>(curve_list[i]));
		}
	}
	std::cout << std::endl;
	//5. Sort the second container in the ascending order of circles’ radii.That is, the first element has the
	//	smallest radius, the last - the greatest.
	std::sort(circle_list.begin(), circle_list.end(),
		[](std::shared_ptr<Circle> &a, std::shared_ptr<Circle> &b) {
			return a->getRadius() < b->getRadius();
		}
	);
	std::cout << "Sorted Circles radii: \n";
	for (int i = 0; i < circle_list.size(); i++) {
		std::cout << circle_list[i]->getRadius() << std::endl;
	}
	std::cout << std::endl;
	// 6. Compute the total sum of radii of all curves in the second container.
	double sum = 0.0;
	for(std::shared_ptr<Circle> circle : circle_list){
		sum += circle->getRadius();
	}
	std::cout << "Total sum of radii of all Circles: " << sum;

}