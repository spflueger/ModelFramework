#ifndef MODELVAR_H_
#define MODELVAR_H_

#include "ModelAbsVar.h"

class ModelVar : public ModelAbsVar {
	public:
		ModelVar();
		virtual ~ModelVar();

		void setValue(double value_);
};

#endif /* MODELVAR_H_ */
