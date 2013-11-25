#ifndef MODELABSVARSET_H_
#define MODELABSVARSET_H_

#include "ModelAbsVar.h"
#include "ModelStructs.h"

#include <memory>
#include <map>
#include <vector>
#include <string>

using std::shared_ptr;

class ModelAbsVarSet {
private:
	std::map<std::pair<std::string, std::string>, shared_ptr<ModelAbsVar>
			, ModelStructs::stringpair_comp> variables;

protected:
	std::string model_name;

public:
	ModelAbsVarSet(std::string model_name_);
	virtual ~ModelAbsVarSet();



	/**
	 * This function returns the total number of parameters that are required by
	 * the current specification of the model.
	 */
	unsigned int getNumberOfVariables() const;

	bool modelParameterExists(
			const std::pair<std::string, std::string> &name_) const;
	bool modelParameterExists(const shared_ptr<ModelAbsVar> &model_par) const;
	bool modelParameterExists(const std::string &name_) const;

	void printInfo() const;

	/**
	 * This function should be used to do create model parameters within a model
	 */
	const shared_ptr<ModelAbsVar> addModelParameter(std::string name_,
			double value_ = 0.0, bool fixed_ = true);
	/**
	 * use this function when combining to models via some operation etc.
	 */
	void addModelParameter(shared_ptr<ModelAbsVar> model_par);

	void reassignParameter(shared_ptr<ModelAbsVar> model_par);

	/**
	 * Attempts to add all parameters of this daughter model to the parameter set.
	 * If there is a global parameter of the daughter model set with equal name
	 * already in this set, then the parameter in the daughter set will be
	 * reassigned and the return value will be nonzero.
	 * @param daughter_model_par_set daughter model parameter set
	 * @returns number of parameters in the daughter parameter set that were reassigned
	 */
	int addModelParameters(ModelAbsVarSet &daughter_model_par_set);

	int setModelParameterValue(const std::string &name_, double value_);

	/**
	 * Used by the parametrizations to get a set of parameters on which the
	 * parametrization depends on.
	 */
	const double& getModelParameterValue(const std::string &name_) const;

	shared_ptr<ModelAbsVar> getModelParameter(
			const std::pair<std::string, std::string> &name_);

	shared_ptr<ModelAbsVar> getModelParameter(const std::string &name_);
};

#endif /* MODELVARSET_H_ */
