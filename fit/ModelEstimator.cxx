/*
 * ModelEstimator.cxx
 *
 *  Created on: Jun 5, 2013
 *      Author: steve
 */

#include "ModelEstimator.h"
#include "core/Model.h"
#include "core/ModelPar.h"
#include "fit/data/Data.h"

#include <cmath>

ModelEstimator::ModelEstimator() :
		free_parameters(), data(), fit_model(), estimator_options(), mtx(), nthreads(
				1) {
}

ModelEstimator::~ModelEstimator() {
	// TODO Auto-generated destructor stub
}

void ModelEstimator::setNumberOfThreads(unsigned int number_of_threads) {
	nthreads = number_of_threads;
	std::cout << "using multithreading with " << nthreads
			<< " concurrent threads!" << std::endl;
	if (chopped_data.size() != nthreads)
		chopData();
}

void ModelEstimator::chopData() {
	// chop data into bunches
	if (nthreads > 1 && data.get()) {
		std::cout << "chopping data into " << nthreads << " bunches" << std::endl;
		chopped_data.clear();
		unsigned int data_points_per_bunch = data->getNumberOfUsedDataPoints()
				/ nthreads + 1;
		std::vector<DataPointProxy> &data_points = data->getData();
		shared_ptr<Data> bunch(new Data(data->getDimension()));
		std::vector<DataPointProxy>::iterator data_point_iter;
		unsigned int counter = 1;
		for (data_point_iter = data_points.begin();
				data_point_iter != data_points.end(); data_point_iter++) {
			if (counter > data_points_per_bunch) {
				chopped_data.push_back(bunch);
				bunch.reset(new Data(data->getDimension()));
				counter = 1;
			}
			if (data_point_iter->isPointUsed()) {
				bunch->insertData(*data_point_iter);
				counter++;
			}
		}
		chopped_data.push_back(bunch);
	}
}

const shared_ptr<Model> ModelEstimator::getModel() const {
	return fit_model;
}

void ModelEstimator::setModel(shared_ptr<Model> new_model) {
	fit_model = new_model;

	// get list of all free parameters
	getParameterList().clear();
	free_parameters.clear();
	free_parameters = fit_model->getModelParameterSet().getFreeModelParameters();
	insertParameters();
}

const shared_ptr<Data> ModelEstimator::getData() const {
	return data;
}

void ModelEstimator::setData(shared_ptr<Data> new_data) {
	data = new_data;

	chopData();
}

void ModelEstimator::insertParameters() {
	for (std::map<std::pair<std::string, std::string>, shared_ptr<ModelPar>,
			ModelStructs::stringpair_comp>::iterator it = free_parameters.begin();
			it != free_parameters.end(); it++) {
		getParameterList().push_back(
				ModelStructs::minimization_parameter(it->first, it->second->getValue(),
						0.0));
	}
}

void ModelEstimator::updateFreeModelParameters(const double *new_values) {
	int counter = 0;
	int first(false);

	// first overwrite the corresponding parameter values
	// loop over the parameter set and update all the free parameters with these values
	for (std::map<std::pair<std::string, std::string>, shared_ptr<ModelPar>,
			ModelStructs::stringpair_comp>::iterator it = free_parameters.begin();
			it != free_parameters.end(); it++) {
		it->second->setValue(new_values[counter]);
		++counter;
	}
	fit_model->updateModel();

	/*if (previous_values.size() == 0) {
	 previous_values.resize(free_parameters.size());
	 first = true;
	 }

	 std::set<std::string> names_of_model_to_update_domain;

	 // first overwrite the corresponding parameter values
	 // loop over the parameter set and update all the free parameters with these values
	 for (std::map<std::pair<std::string, std::string>, shared_ptr<ModelPar>,
	 ModelStructs::stringpair_comp>::iterator it = free_parameters.begin();
	 it != free_parameters.end(); it++) {
	 if (first) {
	 it->second->setValue(new_values[counter]);
	 previous_values[counter] = new_values[counter];
	 names_of_model_to_update_domain.insert(it->first.first);
	 } else {
	 if (new_values[counter] != previous_values[counter]) {
	 it->second->setValue(new_values[counter]);
	 previous_values[counter] = new_values[counter];
	 names_of_model_to_update_domain.insert(it->first.first);
	 }
	 }
	 counter++;
	 }
	 std::set<std::string>::const_iterator model_name_iter =
	 names_of_model_to_update_domain.begin();
	 while (model_name_iter != names_of_model_to_update_domain.end()) {
	 std::cout << "updating domain for " << *model_name_iter << std::endl;
	 fit_model->updateDomainForModelWithName(*model_name_iter);
	 ++model_name_iter;
	 }*/
}

void ModelEstimator::applyEstimatorOptions(
		const EstimatorOptions &estimator_options_) {
	estimator_options = estimator_options_;

	std::vector<DataPointProxy> &datapoints = data->getData();
	for (unsigned int i = 0; i < datapoints.size(); i++) {
		if (datapoints[i].isBinnedDataPoint()) {
			shared_ptr<DataStructs::binned_data_point> data_point =
					datapoints[i].getBinnedDataPoint();
			// check fit ranges
			if (data->getDimension() > 0
					&& estimator_options.getFitRangeX().is_active) {
				if (data_point->bin_center_value[0]
						< estimator_options.getFitRangeX().range_low
						|| data_point->bin_center_value[0]
								> estimator_options.getFitRangeX().range_high) {
					datapoints[i].setPointUsed(false);
					continue;
				}
				if (data->getDimension() > 1
						&& estimator_options.getFitRangeY().is_active) {
					if (data_point->bin_center_value[0]
							< estimator_options.getFitRangeY().range_low
							|| data_point->bin_center_value[0]
									> estimator_options.getFitRangeY().range_high) {
						datapoints[i].setPointUsed(false);
						continue;
					}
				}
				datapoints[i].setPointUsed(true);
			}
			if (estimator_options.isWithIntegralScaling()) {
				if (fit_model.get()) {
					std::vector<DataStructs::DimensionRange> bin_ranges;
					for (unsigned int dim = 0; dim < data->getDimension(); dim++) {
						DataStructs::DimensionRange bin_range;
						bin_range.range_low = data_point->bin_center_value[dim]
								- data_point->bin_widths[dim] / 2.0;
						bin_range.range_high = bin_range.range_low
								+ data_point->bin_widths[dim];
						bin_ranges.push_back(bin_range);
					}

					double scale = 1.0;
					double precision = 1e-3;
					double int_func_real = fit_model->Integral(bin_ranges, precision);
					double int_func_approx = fit_model->evaluate(
							data_point->bin_center_value);
					for (unsigned int dim = 0; dim < data->getDimension(); dim++) {
						int_func_approx *= (bin_ranges[dim].range_high
								- bin_ranges[dim].range_low);
					}

					if (int_func_approx > 0.0 && int_func_real > 0.0) {
						scale = int_func_approx / int_func_real;
					}

					data_point->scale = scale;
					data_point->z = data_point->z * scale;
					data_point->z_error = data_point->z_error * sqrt(scale);
				}
			}
		} else if (datapoints[i].isUnbinnedDataPoint()) {
			// TODO implement for unbinned data
		} else {
			// this point is neither...

		}
	}
}

double ModelEstimator::getLastEstimatorValue() const {
	return last_estimator_value;
}

double ModelEstimator::evaluate(const double *par) {
	/* This point is crucial: because this method is called for every iteration
	 * of the fitter, the "newly changed" parameters have to be updated in the
	 * model so that the changes are actually registered.
	 */
	updateFreeModelParameters(par);

	double estimator_value = 0.0;

	if (nthreads > 1) {
		// create threads and let them evaluate a part of the data
		boost::thread_group threads;

		std::vector<boost::unique_future<double> > futures;
		std::vector<boost::packaged_task<double>*> pts;

		for (unsigned int i = 0; i < nthreads; i++) {
			pts.push_back(
					new boost::packaged_task<double>(
							boost::bind(&ModelEstimator::eval, this, chopped_data[i])));
			futures.push_back(pts[i]->get_future());

			threads.create_thread(
					boost::bind(&boost::packaged_task<double>::operator(), pts[i]));
		}

		threads.join_all();

		for (unsigned int i = 0; i < futures.size(); i++) {
			estimator_value += futures[i].get();
		}

		for (unsigned int i = 0; i < pts.size(); i++) {
			delete pts[i];
		}
	} else {
		estimator_value = eval(data);
	}

	last_estimator_value = estimator_value;
	return estimator_value;
}
