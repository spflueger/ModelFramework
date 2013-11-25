#include "ModelVar.h"

ModelVar::ModelVar() :
		name(""), value(0.0), set(false), bounded(false), fixed(false) {
}

ModelVar::~ModelVar() {
}

void ModelPar::setValue(double value_) {
	// there are some requirements to allow the setting of the parameter
	// if it wasn't set at all before...
	if (!set) {
		set = true;
		value = value_;
	} else {
		// only if its not fixed you want to allow it to change
		if (!fixed) {
			value = value_;
		}
	}
}
