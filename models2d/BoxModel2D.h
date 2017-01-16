#ifndef BOXMODEL2D_H_
#define BOXMODEL2D_H_

#include "core/Model2D.h"

class BoxModel2D: public Model2D {
private:
  shared_ptr<ModelPar> amplitude;
  shared_ptr<ModelPar> lower_edge_var1;
  shared_ptr<ModelPar> upper_edge_var1;
  shared_ptr<ModelPar> lower_edge_var2;
  shared_ptr<ModelPar> upper_edge_var2;

public:
  BoxModel2D(std::string name_);
	virtual ~BoxModel2D();

  mydouble eval(const double *x) const;

  void initModelParameters();

  void updateDomain();
};

#endif /* STEPFUNCTION1D_H_ */
