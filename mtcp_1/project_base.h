#pragma once
#include <Eigen/Dense>
#include <iostream>
#include <vector>

class project_base
{
protected:
	Eigen::MatrixXd mat_in;
	std::vector<Eigen::MatrixXd> mats_out;

	void std_intput();
	virtual void rand_input();
	virtual void process() = 0;
	virtual void print_ans() = 0;

public:
	void rand_demo();
	void std_demo();
};

