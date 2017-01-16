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


// A cost functor that implements the residual r = 10 - x.
struct CostFunctor {
  shared_ptr<ModelControlParameter> est;
  CostFunctor(shared_ptr<ModelControlParameter> est_) : est(est_) {
  }
  bool operator()(double const* const* x, double* residual) const {
    residual[0] = est->evaluate(*x);
    return true;
  }
};

class ModelEstimator: public ModelControlParameter {
private:
	boost::mutex mtx; // lock variable for multi threading
	unsigned int nthreads;
	double last_estimator_value;
	std::vector<double> previous_values;
	double initial_estimator_value;

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

	void setInitialEstimatorValue(double initial_estimator_value_);
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
