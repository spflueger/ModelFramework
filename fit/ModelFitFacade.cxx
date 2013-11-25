/*
 * ModelFitFacade.cxx
 *
 *  Created on: Oct 7, 2013
 *      Author: steve
 */

#include "ModelFitFacade.h"
#include "Data.h"

#include <iostream>

using std::cout;
using std::endl;

ModelFitFacade::ModelFitFacade() {
	// TODO Auto-generated constructor stub
}

ModelFitFacade::~ModelFitFacade() {
	// TODO Auto-generated destructor stub
}

EstimatorOptions& ModelFitFacade::getEstimatorOptions() {
	return estimator_options;
}

shared_ptr<Data> ModelFitFacade::getData() const {
	return data;
}

shared_ptr<ModelEstimator> ModelFitFacade::getEstimator() const {
	return estimator;
}

shared_ptr<ModelMinimizer> ModelFitFacade::getMinimizer() const {
	return minimizer;
}

shared_ptr<Model1D> ModelFitFacade::getModel1d() const {
	return model1d;
}

void ModelFitFacade::setData(shared_ptr<Data> data_) {
	data = data_;
}

void ModelFitFacade::setEstimator(shared_ptr<ModelEstimator> estimator_) {
	estimator = estimator_;
}

void ModelFitFacade::setMinimizer(shared_ptr<ModelMinimizer> minimizer_) {
	minimizer = minimizer_;
}

void ModelFitFacade::setModel1d(shared_ptr<Model1D> model1d_) {
	model1d = model1d_;
}

ModelFitResult ModelFitFacade::Fit() {
	ModelFitResult fit_result_dummy;

	// check that estimator is set
	if (0 == estimator) {
		fit_result_dummy.setFitStatus(-1);
		return fit_result_dummy;
	}

	// set model
	estimator->setModel(model1d);
	// set data
	estimator->setData(data);
	// apply estimator options
	estimator->applyEstimatorOptions(estimator_options);

	// check that minimizer exists
	if (0 == minimizer) {
		fit_result_dummy.setFitStatus(-2);
		return fit_result_dummy;
	}

	minimizer->setControlParameter(estimator);

	int fit_status = minimizer->doMinimization();
	// call minimization procedure
	if (fit_status) {
		cout << "ERROR: Problem while performing fit. Returning NULL pointer!"
				<< endl;
		fit_result_dummy.setFitStatus(fit_status);
		return fit_result_dummy;
	}

	ModelFitResult fit_result = minimizer->createModelFitResult();
	fit_result.setFitStatus(fit_status);

	fit_result.setFinalEstimatorValue(estimator->eval());
	fit_result.setNumberOfDataPoints(
			estimator->getData()->getNumberOfDataPoints());
	fit_result.setFinalEstimatorValue(estimator->eval());
	fit_result.setNumberOfDataPoints(
			estimator->getData()->getNumberOfDataPoints());
	return fit_result;
}
