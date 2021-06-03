#pragma once
#include "project_base.h"
class JordanForm :
	public project_base
{
protected:
	virtual void process() {
		int dim = mat_in.size();
		Eigen::MatrixXd mat_lambda(dim, dim);
		Eigen::MatrixXd mat_lambda_power(dim, dim);
		Eigen::EigenSolver<Eigen::MatrixXd> es(mat_in);
		std::cout << "The eigenvalues of the input matrix are:" << std::endl << es.eigenvalues() << std::endl;
		std::cout << "Size of eigenvalues: "<< std::endl << es.eigenvalues().size() << std::endl;
		for(int itr = 0; itr < es.eigenvalues().size(); itr++){
			std::vector<double> DimKer;
			
			int eigenvalue = es.eigenvalues()[itr][0];
			for(int i = 0; i < dim; i++){
				for(int j = 0; j < dim; j++){
					if (i == j) { mat_lambda(i, j) = mat_in(i, j) - eigenvalue; }
					else { mat_lambda(i, j) = mat_in(i, j); }
				}
			}
			for(int k=1;k<=dim;k++){
				mat_lambda_power = Eigen::pow(mat_lambda,k);
				FullPivLU<Matrix3f> lu_decomp(mat_lambda_power);
				int dimker = dim - lu_decomp.rank()

				if (lu_decomp.rank() == 0){break;}
			}
			FullPivLU<Matrix3f> lu_decomp(mat_lambda);
   			cout << "The rank of M_lambda is " << lu_decomp.rank() << endl;
		}
	}
		
	virtual void print_ans() {}
};

