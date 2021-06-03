#include "uSimilar.h"

void uSimilar::rand_input()
{
	project_base::rand_input();
	mat_in = mat_in.adjoint() * mat_in;
}

void uSimilar::process()
{
	es.compute(mat_in);
	mats_out[0] = es.eigenvalues().asDiagonal();
	mats_out[1] = es.eigenvectors();
}

void uSimilar::print_ans()
{
	std::cout << "eigenbasis matrix: \n" << mats_out[1] << std::endl;
	std::cout << "diagonal matrix: \n" << mats_out[0] << std::endl;
}
