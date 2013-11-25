#ifndef MODELABSVAR_H_
#define MODELABSVAR_H_

#include <utility>
#include <string>
#include <set>
#include <memory>

using std::shared_ptr;
using std::string;
using std::pair;

class ModelAbsVar {
	protected:
		string name;
		pair<double, double> bounds;
		double value;
		bool fixed, set, bounded;

		/**
		 * This stores the connection to other ModelVar's. Once this ModelVar is
		 * freed, the parametrizations (if they exist) of the connected parameters
		 * are called at each iteration step. Note that a parameter can also have a
		 * connection to itself to update parameters that are used directly within a
		 * model.
		 */
		std::set<shared_ptr<ModelAbsVar> > connections;

	public:
		ModelAbsVar();
		virtual ~ModelAbsVar();

		const string& getName() const;

		virtual void setValue(double value_) =0;
		const double& getValue() const;

		bool isFixed() const;
		void setFixed(bool fixed_);

		bool isSet() const;
		bool isConnected() const;

		const pair<double, double>& getBounds() const;

		void setBounds(double lower_bound, double upper_bound);

		/**
		 * This function adds a dependence of this model parameter on the specified
		 * parameter. Once the dependent parameter changed this model parameter will
		 * be updated via the specified parametrization in the corresponding handler
		 * instance.
		 */
		void setConnectionTo(const shared_ptr<ModelAbsVar> &model_par);

		std::set<shared_ptr<ModelAbsVar> >& getConnections();
};

#endif /* MODELDOMAINVAR_H_ */
