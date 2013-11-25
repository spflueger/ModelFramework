/*
 * ModelVar.cxx
 *
 *  Created on: Jul 2, 2013
 *      Author: steve
 */

#include "ModelAbsVar.h"

ModelAbsVar::ModelAbsVar() :
		name(""), value(0.0), set(false), bounded(false), fixed(false) {
}

ModelAbsVar::~ModelAbsVar() {
}

const std::string& ModelAbsVar::getName() const {
	return name;
}

const double& ModelAbsVar::getValue() const {
	return value;
}

bool ModelAbsVar::isFixed() const {
	return fixed;
}

void ModelAbsVar::setFixed(bool fixed_) {
	fixed = fixed_;
}

bool ModelAbsVar::isSet() const {
	return set;
}

bool ModelAbsVar::isConnected() const {
	if (connections.size() > 0)
		return true;
	else
		return false;
}

const std::pair<double, double>& ModelAbsVar::getBounds() const {
	return bounds;
}

void ModelAbsVar::setBounds(double lower_bound, double upper_bound) {
	bounds.first = lower_bound;
	bounds.second = upper_bound;
	bounded = true;
}

void ModelAbsVar::setConnectionTo(const shared_ptr<ModelVar> &model_par) {
	connections.insert(model_par);
}

std::set<shared_ptr<ModelVar> >& ModelAbsVar::getConnections() {
	return connections;
}
