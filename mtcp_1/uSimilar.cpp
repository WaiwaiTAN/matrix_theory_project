#include "uSimilar.h"

void uSimilar::rand_input()
{
	Eigen::MatrixXd mat_ = Eigen::MatrixXd::Random(4, 4);
	mat_in = mat_.transpose() + mat_;
}

void uSimilar::process()
{
	es.compute(mat_in);
	mats_out.push_back(es.eigenvalues().asDiagonal());
	mats_out.push_back(es.eigenvectors());
}

void uSimilar::print_ans()
{
	std::cout << "eigenbasis matrix: \n" << mats_out[1] << std::endl;
	std::cout << "diagonal matrix: \n" << mats_out[0] << std::endl;
}
