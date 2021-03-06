#include "ModelAbsVarSet.h"

#include <iostream>

ModelAbsVarSet::ModelAbsVarSet(std::string model_name_) {
	model_name = model_name_;
}

ModelAbsVarSet::~ModelAbsVarSet() {
	// TODO Auto-generated destructor stub
}

void ModelAbsVarSet::setVariables(
		std::map<std::pair<std::string, std::string>, shared_ptr<ModelAbsVar>
				, ModelStructs::stringpair_comp>::iterator begin
		, std::map<std::pair<std::string, std::string>, shared_ptr<ModelAbsVar>
				, ModelStructs::stringpair_comp>::iterator end) {
	variables.insert;
}

unsigned int ModelAbsVarSet::getNumberOfParameters() const {
	return model_par_map.size();
}

unsigned int ModelAbsVarSet::getNumberOfFreeParameters() const {
	unsigned int nfree = 0;
	for (std::map<std::pair<std::string, std::string>, shared_ptr<ModelVar>
			, ModelStructs::stringpair_comp>::const_iterator it =
			model_par_map.begin(); it != model_par_map.end(); it++) {
		if (!it->second->isFixed())
			nfree++;
	}
	return nfree;
}

void ModelAbsVarSet::printInfo() const {
	std::cout << "Set contains " << model_par_map.size() << " entries"
			<< std::endl;
	int counter = 0;
	std::cout << "************************************************************"
			<< std::endl;
	for (std::map<std::pair<std::string, std::string>, shared_ptr<ModelVar>
			, ModelStructs::stringpair_comp>::const_iterator it =
			model_par_map.begin(); it != model_par_map.end(); it++) {
		std::cout << "------------------------------------------------------------"
				<< std::endl;
		std::cout << "parameter " << counter << "  (" << it->first.first << ":"
				<< it->first.second << ")" << std::endl;
		std::cout << "name: " << it->second->getName() << std::endl;
		std::cout << "value: " << it->second->getValue() << std::endl;
		std::cout << "is fixed: " << it->second->isFixed() << std::endl;
		std::cout << "is set: " << it->second->isSet() << std::endl;
		std::cout << "------------------------------------------------------------"
				<< std::endl;
		counter++;
	}
	std::cout << "************************************************************"
			<< std::endl;
}

const shared_ptr<ModelVar> ModelAbsVarSet::addModelParameter(std::string name_,
		double value_, bool fixed_) {
	if (modelParameterExists(name_)) {
		std::cout << "(" << model_name << ") WARNING: This model parameter "
				<< name_ << " already exists. Returning existing value reference!"
				<< std::endl;
	} else {
		model_par_map[std::make_pair(model_name, name_)] = shared_ptr < ModelVar
				> (new ModelVar());
	}
	return model_par_map[std::make_pair(model_name, name_)];
}

void ModelAbsVarSet::addModelParameter(shared_ptr<ModelVar> model_par) {
	model_par_map[std::make_pair(model_name, model_par->getName())] = model_par;
}

int ModelAbsVarSet::setModelParameterValue(const std::string &name_,
		double value_) {
	if (modelParameterExists(name_)) {
		model_par_map[std::make_pair(model_name, name_)]->setValue(value_);
		return 0;
	} else {
		// we did not find the parameter to be defined in this model, but if it is
		// superior/global then we have to check only for the name of the parameter
		for (std::map<std::pair<std::string, std::string>, shared_ptr<ModelVar>
				, ModelStructs::stringpair_comp>::const_iterator it =
				model_par_map.begin(); it != model_par_map.end(); it++) {
			if (it->first.second.compare(name_) == 0) {
				it->second->setValue(value_);
				return 0;
			}
		}
		std::cout << "(" << model_name << ") ERROR: Parameter " << name_
				<< " was not found in the parameter set!" << std::endl;
		return 1;
	}
}

void ModelAbsVarSet::reassignParameter(shared_ptr<ModelVar> model_par) {
	model_par_map.erase(std::make_pair(model_name, model_par->getName()));
	addModelParameter(model_par);
}

bool ModelAbsVarSet::modelParameterExists(
		const shared_ptr<ModelVar> &model_par) const {
	return modelParameterExists(model_par->getName());
}

bool ModelAbsVarSet::modelParameterExists(const std::string &name_) const {
	return modelParameterExists(std::make_pair(model_name, name_));
}

bool ModelAbsVarSet::modelParameterExists(
		const std::pair<std::string, std::string> &name_) const {
	if (model_par_map.find(name_) != model_par_map.end())
		return true;
	else {
		return false;
	}
}

int ModelAbsVarSet::addModelParameters(ModelVarSet &daughter_model_par_set) {
	int num_pars_reassigned = 0;
	// loop over all parameters to be added
	for (std::map<std::pair<std::string, std::string>, shared_ptr<ModelVar>
			, ModelStructs::stringpair_comp>::const_iterator it =
			daughter_model_par_set.getModelParameterMap().begin();
			it != daughter_model_par_set.getModelParameterMap().end(); it++) {
		// superior/global parameters are special
		if (it->second->isSuperior()) {
			// loop over all parameters that are already in the set
			bool found = false;
			for (std::map<std::pair<std::string, std::string>, shared_ptr<ModelVar>
					, ModelStructs::stringpair_comp>::const_iterator model_it =
					model_par_map.begin(); model_it != model_par_map.end(); model_it++) {
				// check if this element already exists in this map
				if (model_it->first.second.compare(it->first.second) == 0) {
					// check that also this variable is superior
					if (model_it->second->isSuperior()) {
						// take that element and reassign the one which is supposed to be added
						daughter_model_par_set.reassignParameter(model_it->second);
						num_pars_reassigned++;
						found = true;
						break;
					} else {
						// display a warning if we have a variable with the same name but is
						// not superior
						std::cout
								<< "("
								<< model_name
								<< ") WARNING: While trying to add a superior model parameter, a "
										"parameter with equal name was found, however this parameter is not "
										"global/superior!" << std::endl;
					}
				}
			}
			if (!found) {
				model_par_map[it->first] = it->second;
			}
		} else { // if its not global just check if its unique and add it
			if (model_par_map.find(it->first) == model_par_map.end()) {
				model_par_map[it->first] = it->second;
			} else { // otherwise we have a problem...
				std::cout << "(" << model_name << ") ERROR: Entry " << it->first.first
						<< ":" << it->first.second
						<< " already exists in the current model parameter set! Skipping this entry..."
						<< std::endl;
			}
		}
	}
	return num_pars_reassigned;
}

const double& ModelAbsVarSet::getModelParameterValue(
		const std::string &name_) const {
	return model_par_map.at(std::make_pair(model_name, name_))->getValue();
}

shared_ptr<ModelAbsVar> ModelAbsVarSet::getModelParameter(
		const std::pair<std::string, std::string> &name_) {
	if (!modelParameterExists(name_)) {
		// ok we should actually throw an exception here
		// because we can only end up here if user asks from a composite model
		// for a parameter that does not exist... which is a mistake...
		std::cout
				<< "ERROR: The requested parameter "
				<< name_.first
				<< ":"
				<< name_.second
				<< " does not exist! Return a new parameter of this type which is unused!"
				<< " As this call is for composite models please make sure that the model "
				<< "and parameter name are correct." << std::endl;
		addModelParameter(name_.second);
	}
	return model_par_map.at(name_);
}

shared_ptr<ModelAbsVar> ModelAbsVarSet::getModelParameter(
		const std::string &name_) {
	if (!modelParameterExists(name_)) {
		addModelParameter(name_);
	}
	return getModelParameter(std::make_pair(model_name, name_));
}
