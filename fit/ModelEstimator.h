/*
 * ModelEstimator.h
 *
 *  Created on: Jun 5, 2013
 *      Author: steve
 */

#ifndef MODELESTIMATOR_H_
#define MODELESTIMATOR_H_

#include "core/ModelStructs.h"
#include "fit/ModelControlParameter.h"
#include "fit/EstimatorOptions.h"

#include "SharedPtr.h"

#include <map>
#include <vector>

#include <boost/thread.hpp>

class Data;
class Model;
class ModelPar;

class ModelEstimator: public ModelControlParameter {
private:
	boost::mutex mtx; // lock variable for multi threading
	unsigned int nthreads;
	double last_estimator_value;
	std::vector<double> previous_values;

	// list of free parameters
	std::map<std::pair<std::string, std::string>, shared_ptr<ModelPar>
			, ModelStructs::stringpair_comp> free_parameters;

	void insertParameters();

	void updateFreeModelParameters(const double *new_values);

	// data
	shared_ptr<Data> data;

	// chopped data
	std::vector<shared_ptr<Data> > chopped_data;

	void chopData();

protected:
	// model used for fitting
	shared_ptr<Model> fit_model;

	EstimatorOptions estimator_options;

public:
	ModelEstimator();
	virtual ~ModelEstimator();

	void setNumberOfThreads(unsigned int number_of_threads);

	const shared_ptr<Model> getModel() const;
	void setModel(shared_ptr<Model> new_model);

	const shared_ptr<Data> getData() const;
	void setData(shared_ptr<Data> new_data);

	std::vector<shared_ptr<ModelPar> >& getFreeParameterList();

	double getLastEstimatorValue() const;

	double evaluate(const double *par);

	void applyEstimatorOptions(const EstimatorOptions &estimator_options_);

	/**
	 * The estimator function (chi2, likelihood, etc)
	 */
	virtual double eval(shared_ptr<Data> data) =0;
};

#endif /* MODELESTIMATOR_H_ */
