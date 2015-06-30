/*
 * ModelFitFacade.cxx
 *
 *  Created on: Oct 7, 2013
 *      Author: steve
 */

#include "ModelFitFacade.h"
#include "fit/data/Data.h"

#include <iostream>

using std::cout;
using std::endl;

ModelFitFacade::ModelFitFacade() :
		data(), model(), estimator(), minimizer(), estimator_options() {
}

ModelFitFacade::~ModelFitFacade() {
	// TODO Auto-generated destructor stub
}

const EstimatorOptions& ModelFitFacade::getEstimatorOptions() const {
	return estimator_options;
}

void ModelFitFacade::setEstimatorOptions(const EstimatorOptions& est_opt_) {
	estimator_options = est_opt_;
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

shared_ptr<Model> ModelFitFacade::getModel() const {
	return model;
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

void ModelFitFacade::setModel(shared_ptr<Model> model_) {
	model = model_;
}

ModelFitResult ModelFitFacade::Fit() {
	ModelFitResult fit_result_dummy;

	// check that estimator is set
	if (!estimator) {
		fit_result_dummy.setFitStatus(-1);
		return fit_result_dummy;
	}

	// check if data and model have the correct dimensions
	if (model->getDimension() != data->getDimension()) {
		std::cout << "The model has a dimension of " << model->getDimension()
				<< ", which does not match the data dimension of "
				<< data->getDimension() << "!" << std::endl;
		return fit_result_dummy;
	}

	// set model
	estimator->setModel(model);
	// set data
	estimator->setData(data);
	// apply estimator options
	std::cout
			<< "applying estimator options (in case of integral scaling this can mean integrals are being computed!)..."
			<< std::endl;
	estimator->applyEstimatorOptions(estimator_options);

	// check that minimizer exists
	if (!minimizer) {
		fit_result_dummy.setFitStatus(-2);
		return fit_result_dummy;
	}

	minimizer->setControlParameter(estimator);

	// call minimization procedure
	int fit_status = minimizer->doMinimization();

	if (fit_status) {
		cout << "ERROR: Problem while performing fit. Returning NULL pointer!"
				<< endl;
		fit_result_dummy.setFitStatus(fit_status);
		return fit_result_dummy;
	}

	ModelFitResult fit_result = minimizer->createModelFitResult();
	fit_result.setFitStatus(fit_status);

	fit_result.setFinalEstimatorValue(estimator->getLastEstimatorValue());
	fit_result.setNumberOfDataPoints(
			estimator->getData()->getNumberOfUsedDataPoints());
	return fit_result;
}
