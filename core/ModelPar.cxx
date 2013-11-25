/*
 * ModelPar.cxx
 *
 *  Created on: Jan 12, 2013
 *      Author: steve
 */

#include "ModelPar.h"

ModelPar::ModelPar() {
	fixed = true; // unlike a model variable we want it to be fixed by default
}

ModelPar::ModelPar(std::string name_, double value_, bool fixed_) {
	name = name_;
	value = value_;
	fixed = fixed_;
	locked = true; // variable is immediately locked which sounds strange
				   // but it can be set once because it is not set yet
				   // the lock should not be fiddled with and is automatically
				   // opened within the registerUpdater method of #ModelParameterHandler
	global = false;
}

void ModelPar::setLocked(bool locked_) {
	locked = locked_;
}

void ModelPar::setValue(double value_) {
	// there are some requirements to allow the setting of the parameter
	// if it wasn't set at all before...
	if (!set) {
		value = value_;
		set = true;
	} else {
		// usually if its set you don't want it to change again
		// there is an exception:
		// is fixed and is connected to another parameter
		// and that connection partner has changed
		if (!locked || !fixed) {
			value = value_;
		}
	}
}

bool ModelPar::isGlobal() const {
	return global;
}

void ModelPar::setGlobal(bool superior_) {
	global = superior_;
}

