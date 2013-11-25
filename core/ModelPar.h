/*
 * ModelPar.h
 *
 *  Created on: Jan 12, 2013
 *      Author: steve
 */

#ifndef MODELPAR_H_
#define MODELPAR_H_

#include "ModelAbsVar.h"

class ModelPar : public ModelAbsVar {
private:
  bool global, locked;

public:
  ModelPar();
  ModelPar(std::string name_, double value_, bool fixed_ = false);

  void setValue(double value_);

  void setLocked(bool locked_);
  bool isGlobal() const;
  void setGlobal(bool superior_);
};

#endif /* MODELPAR_H_ */
