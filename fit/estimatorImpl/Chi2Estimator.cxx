/*
 * Chi2Estimator.cxx
 *
 *  Created on: Jun 5, 2013
 *      Author: steve
 */

#include "Chi2Estimator.h"
#include "Model.h"
#include "Data.h"

#include <iostream>

Chi2Estimator::Chi2Estimator() {
	// TODO Auto-generated constructor stub
}

Chi2Estimator::~Chi2Estimator() {
	// TODO Auto-generated destructor stub
}

double Chi2Estimator::eval() const {
	//calculate chisquare
	double chisq = 0.0;
	double delta;

	std::vector<DataPointProxy> &data_points = data->getData();
	// loop over data
	for (unsigned int i = 0; i < data_points.size(); i++) {
		shared_ptr<DataStructs::binned_data_point> data_point;
		if (data_points[i].isPointUsed()) {
			data_point = data_points[i].getBinnedDataPoint();
			delta = (data_point->value
					- data_point->scaling_factor
							* fit_model->evaluate(&data_point->point.coordinates[0].value))
					/ data_point->value_error;
			chisq += delta * delta;
		}
	}
	return chisq;
}
