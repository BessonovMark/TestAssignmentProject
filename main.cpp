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
#include <omp.h>


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
		if (std::dynamic_pointer_cast<Circle>(curve_list[i])) {
			circle_list.push_back(std::dynamic_pointer_cast<Circle>(curve_list[i]));
		}
	}
	std::cout << std::endl;

	//5. Sort the second container in the ascending order of circles’ radii.That is, the first element has the
	//	smallest radius, the last - the greatest.
	std::sort(circle_list.begin(), circle_list.end(),
		[](std::shared_ptr<Circle>& a, std::shared_ptr<Circle>& b) {
			return a->getRadius() < b->getRadius();
		}
	);
	std::cout << "Sorted Circles radii: \n";
	for (int i = 0; i < circle_list.size(); i++) {
		std::cout << circle_list[i]->getRadius() << std::endl;
	}
	std::cout << std::endl;
	// 6. Compute the total sum of radii of all curves in the second container.

	double t_sequential_begin = omp_get_wtime();

	double sum_radii_sequencial = 0.0;
	for (std::shared_ptr<Circle> circle : circle_list) {
		sum_radii_sequencial += circle->getRadius();
	}

	double t_sequential_spend = omp_get_wtime() - t_sequential_begin;

	// 8. Implement computation of the total sum of radii using parallel computations (e.g. OpenMP or Intel TBB library).
	double sum_radii_parallel = 0.0;
	double t_parallel_begin = omp_get_wtime();
#pragma omp parallel
	{
		int steps = circle_list.size() / omp_get_num_threads();
		for (int i = omp_get_thread_num() * steps; i < (omp_get_thread_num() + 1) * steps; ++i) {
			sum_radii_parallel += circle_list[i]->getRadius();
		}
		if (omp_get_thread_num() == omp_get_num_threads() - 1) {
			for (int i = (omp_get_thread_num() + 1) * steps; i < circle_list.size(); ++i){
				sum_radii_parallel += circle_list[i]->getRadius();
			}
		}
	}
	double t_parallel_end = omp_get_wtime();
	std::cout << "Execution time of sequential calculation: " <<  t_sequential_spend << std::endl;
	std::cout << "Execution time of parallel calculation: " << t_parallel_end - t_parallel_begin << std::endl;
	std::cout << "Sum calculated sequentially: " << sum_radii_sequencial << std::endl;
	std::cout << "Sum calculated in parallel: " << sum_radii_parallel;
	//Execution time of parallel calculations is longer with small input. It gets smaller with bigger input
}