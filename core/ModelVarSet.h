/*
 * ModelVarSet.h
 *
 *  Created on: Feb 9, 2013
 *      Author: steve
 */

#ifndef MODELVARSET_H_
#define MODELVARSET_H_

#include "ModelVar.h"
#include "ModelStructs.h"

#include <map>
#include <vector>
#include <string>

class ModelVarSet {
private:
	std::string model_name;

	/**
	 * Map containing all the model parameters which are unique, independent
	 * and belong to this model.
	 */
	std::map<std::pair<std::string, std::string>, shared_ptr<ModelVar>
			, ModelStructs::stringpair_comp> model_par_map;

public:
	ModelVarSet(std::string model_name_);
	virtual ~ModelVarSet();

	/**
	 * This function returns the total number of parameters that are required by
	 * the current specification of the model.
	 */
	unsigned int getNumberOfVariables() const;

	bool modelParameterExists(
			const std::pair<std::string, std::string> &name_) const;
	bool modelParameterExists(const shared_ptr<ModelVar> &model_par) const;
	bool modelParameterExists(const std::string &name_) const;

	void printInfo() const;

	/**
	 * This function should be used to do create model parameters within a model
	 */
	const shared_ptr<ModelVar> addModelParameter(std::string name_,
			double value_ = 0.0, bool fixed_ = true);
	/**
	 * use this function when combining to models via some operation etc.
	 */
	void addModelParameter(shared_ptr<ModelVar> model_par);

	void reassignParameter(shared_ptr<ModelVar> model_par);

	/**
	 * Attempts to add all parameters of this daughter model to the parameter set.
	 * If there is a global parameter of the daughter model set with equal name
	 * already in this set, then the parameter in the daughter set will be
	 * reassigned and the return value will be nonzero.
	 * @param daughter_model_par_set daughter model parameter set
	 * @returns number of parameters in the daughter parameter set that were reassigned
	 */
	int addModelParameters(ModelVarSet &daughter_model_par_set);

	/**
	 * Attempts to add all parameters of the model parameter set addition, to the
	 * current model parameter set. In contrast to #addModelParameters the model
	 * parameters will be added with the complete key pair, so model+modelpar
	 * name. Hence this functions is used to construct the full model parameter
	 * set of a composite model.
	 * TODO: throw an exception if some model parameter is duplicate
	 * @param addition model parameter set that will be added
	 */
	void addModelParameterSet(ModelVarSet& addition);

	int setModelParameterValue(const std::string &name_, double value_);

	/**
	 * Used by the parametrizations to get a set of parameters on which the
	 * parametrization depends on.
	 */
	const double& getModelParameterValue(const std::string &name_) const;

	shared_ptr<ModelVar> getModelParameter(
			const std::pair<std::string, std::string> &name_);

	shared_ptr<ModelVar> getModelParameter(const std::string &name_);

	std::map<std::pair<std::string, std::string>, shared_ptr<ModelVar>
			, ModelStructs::stringpair_comp>& getModelParameterMap();
};

#endif /* MODELVARSET_H_ */
