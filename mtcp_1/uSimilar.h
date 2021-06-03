#pragma once
#include "project_base.h"
class uSimilar :
	public project_base
{
private:
	Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> es;
protected:
	virtual void rand_input();
	virtual void process();
	virtual void print_ans();
};

