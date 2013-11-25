/*
 * Model.cxx
 *
 *  Created on: Jan 8, 2013
 *      Author: steve
 */

#include "Model.h"

//#include <iostream>

Model::Model(std::string name_) :
		model_par_handler(name_), name(name_) {
}

Model::~Model() {
	// clear map of ModelPars
}

void Model::addModelToList(shared_ptr<Model> model) {
	submodel_list.push_back(model);
	if (model_par_handler.getModelParameterSet().addModelParameters(
			model->getModelParameterSet())) {
		// in case some ModelPar's have been reassigned in the daughter model
		// the model and its parametrizations have to be re-initialized
		model->reinit();
	}
}

unsigned int Model::getDimension() const {
	return dimension;
}

std::string Model::getName() const {
	return name;
}

ModelParSet& Model::getModelParameterSet() {
	return model_par_handler.getModelParameterSet();
}

void Model::executeParametrizationModels(const DataStructs::data_point &point) {
	//first call through all submodels of this model
	for (unsigned int i = 0; i < submodel_list.size(); i++) {
		/*	std::cout<<submodel_list[i]<<std::endl;
		 std::cout<<submodel_list[i]->getName()<<std::endl;*/
		submodel_list[i]->executeParametrizationModels(point);
	}
	// loop over all parametrization models...
	model_par_handler.executeParametrizationModels(point);
	updateDomain();
}

double Model::evaluate() {
	executeParametrizationModels(x);
	return eval();
}

void Model::reinit() {
	model_par_handler.reinitModelParametrizations();
	initModelParameters();
}

int Model::init() {
	//first go through all submodels of this model
	for (unsigned int i = 0; i < submodel_list.size(); i++) {
		submodel_list[i]->init();
	}
	//now check on this model if everything is set
	//check that all parametrizations have their requirements fulfilled
	//and call them if possible
	model_par_handler.checkParametrizations();

	// update domain since parameters are different now
	updateDomain();

	//then check if all parameters of the model have now been set
	//by user and parametrizations
	int error_code = model_par_handler.checkParameters();
	if (0 == error_code)
		model_par_handler.registerUpdaters();
	return error_code;
}

ModelParameterHandler& Model::getModelParameterHandler() {
	return model_par_handler;
}

void Model::updateModel() {
	// call update functions for all submodels
	for (unsigned int i = 0; i < submodel_list.size(); i++) {
		submodel_list[i]->updateModel();
	}
	// update the model parameters that really appear in this model
	model_par_handler.updateModelParameters();
	// finally recalculate the domain of all models that construct this model
	updateDomain();
}

