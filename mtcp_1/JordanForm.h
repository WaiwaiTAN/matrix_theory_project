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
			std::vector<double> d;
			std::vector<double> j;
			int eigenvalue = es.eigenvalues()[itr][0];
			for(int i = 0; i < dim; i++){
				for(int j = 0; j < dim; j++){
					if (i == j) { mat_lambda(i, j) = mat_in(i, j) - eigenvalue; }
					else { mat_lambda(i, j) = mat_in(i, j); }
				}
			}
			for(int k=1;k<=dim;k++){

				mat_lambda_power = Eigen::pow<Eigen::MatrixXd>(mat_lambda,k);
				Eigen::FullPivLU<Eigen::Matrix3f> lu_decomp(mat_lambda_power);
				int dimker = dim - lu_decomp.rank();
				DimKer[k] = dimker;
				if (lu_decomp.rank() == 0){break;}
			}
			for(int m=0;m< DimKer.size();m++){
				if(m==0){d[m] = DimKer[m];}
				else{
					d[m] = DimKer[m] - DimKer[m-1];
				}
			}
			for(int n=0;n< DimKer.size();n++){
				if(n==0){j[n] = d[DimKer.size()]; }
				else{
					j[n] = d[DimKer.size()] - d[DimKer.size()-1];
				}
			}
		}
	}
		
	virtual void print_ans() {}
};

