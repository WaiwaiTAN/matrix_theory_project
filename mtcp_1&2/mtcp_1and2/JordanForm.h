#pragma once
#include "project_base.h"
class JordanForm :
	public project_base
{
protected:
    std::vector<double> eigenvalue;
    std::vector<std::vector<float>> D;
    std::vector<std::vector<float>> J;
	virtual void process() {
        int dim = mat_in.rows();
        bool con_pow = 1;
        std::vector<std::string>::iterator iter;
        Eigen::MatrixXd mat_lambda(dim, dim);
        Eigen::MatrixXd mat_lambda_power(dim, dim);
        Eigen::MatrixXd mat_id(dim,dim);
        Eigen::EigenSolver<Eigen::MatrixXd> es(mat_in);
        mat_lambda_power = Eigen::MatrixXd::Identity(dim, dim);
        mat_id = Eigen::MatrixXd::Identity(dim, dim);
        std::cout << "The eigenvalues of the input matrix are:" << std::endl << es.eigenvalues() << std::endl;
        std::cout << "Size of eigenvalues: " << std::endl << es.eigenvalues().size() << std::endl;
//        std::cout << "The first eigenvalue is: " << std::endl << es.eigenvalues()[0].real() << std::endl;
        std::cout << "Dim: " << dim << std::endl;
        eigenvalue.push_back(es.eigenvalues()[0].real());
        for (int eig = 1; eig < es.eigenvalues().size(); eig++){
            if(abs(es.eigenvalues()[eig].real() - eigenvalue[eigenvalue.size() - 1]) > 0.01){
                eigenvalue.push_back(es.eigenvalues()[eig].real());
            }
            else{}
        }

        std::cout<<"The eigenvalues are: ";
        for (int eig_itr = 0; eig_itr < eigenvalue.size(); eig_itr++){
            std::cout<<eigenvalue[eig_itr] << "\t";
        }
        std::cout<<std::endl;
        std::cout<<"Length of eigenvalue:"<<eigenvalue.size()<<std::endl;

        for (int itr = 0; itr < eigenvalue.size(); itr++) {
            std::vector<float> DimKer;
            std::vector<float> d;
            std::vector<float> j;
            double eigenvalue_real = eigenvalue[itr];
            std::cout<<eigenvalue_real<<std::endl;
            mat_lambda = mat_in - eigenvalue_real * mat_id;
            for (int power_row = 0; power_row < mat_lambda_power.rows(); power_row ++){
                for (int power_col = 0; power_col < mat_lambda_power.cols(); power_col ++){
                    if(abs(mat_lambda(power_row,power_col))<0.01){
                        mat_lambda(power_row,power_col) = 0;
                    }
                }
            }
#ifdef print_info
            std::cout<<"MatLambda: "<<std::endl<<mat_lambda<<std::endl;
#endif // print_info
			int last_dimker = 0;

            while(con_pow){
                mat_lambda_power = mat_lambda_power * mat_lambda;
                for (int power_row = 0; power_row < mat_lambda_power.rows(); power_row ++){
                    for (int power_col = 0; power_col < mat_lambda_power.cols(); power_col ++){
                        if(abs(mat_lambda_power(power_row,power_col))<0.01){
                            mat_lambda_power(power_row,power_col) = 0;
                        }
                    }
                }

#ifdef print_info
				std::cout << "---------------------" << std::endl << mat_lambda_power << std::endl;
#endif // print_info
                Eigen::FullPivLU<Eigen::MatrixXd> lu_decomp(mat_lambda_power);
                int dimker = dim - lu_decomp.rank();
                if(DimKer.size() == 0){
                    DimKer.push_back(dimker);
                    last_dimker = dimker;
                }
                else{
                    if(last_dimker != dimker){
                        DimKer.push_back(dimker);
                        last_dimker = dimker;
                    }
                    else{
                        con_pow = 0;
                    }
                }
            }

            for (int m = 0; m < DimKer.size(); m++) {
                if (m == 0) { d.push_back(DimKer[m]); }
                else {
                    d.push_back(DimKer[m] - DimKer[m - 1]);
                }
            }

            D.push_back(d);
            std::cout<<"vector d=[  ";
            for(int num = 0;num<d.size();num++){
                std::cout<<d[num]<<"  ";
            }
            std::cout<<"]"<<std::endl;

            for (int n = 0; n < DimKer.size(); n++) {
                if (n == 0) { j.push_back(d[DimKer.size() - 1]); }
                else {
                    j.push_back(d[DimKer.size() - n - 1] - d[DimKer.size() - n]);
                }
            }

            J.push_back(j);
            std::cout<<"vector j=[  ";
            for(int num = 0;num<j.size();num++){
                std::cout<<j[num]<<"  ";
            }
            std::cout<<"]"<<std::endl;
            con_pow = 1;
            mat_lambda_power = Eigen::MatrixXd::Identity(dim, dim);
        }
        std::cout<<"D:"<<D.size()<<std::endl;
        std::cout<<"J:"<<J.size()<<std::endl;

    }

		
	virtual void print_ans() {
        int dim = mat_in.rows();
        Eigen::MatrixXd mat_Jordan = Eigen::MatrixXd::Zero(dim,dim);
        int start_row = 0;
        for (int itr = 0; itr < eigenvalue.size(); itr++){
            std::cout<<"Eigenvalue: "<<eigenvalue[itr]<<std::endl;
            std::cout<<"Start_row: "<<start_row<<std::endl;
            int sub_dim = 0;
            for (int num = 0; num < D[itr].size(); num ++){
                sub_dim += D[itr][num];
            }
            Eigen::MatrixXd mat_subJor(sub_dim,sub_dim);
            for (int sub_j = 0; sub_j < J[itr].size(); sub_j++){
                for (int num_sub_j = 0; num_sub_j < J[itr][sub_j]; num_sub_j++){
                    int end_row = start_row + J[itr].size() - sub_j;
                    for (int sub_row = start_row; sub_row < end_row; sub_row++){
                        for (int sub_col = start_row; sub_col < end_row; sub_col++){
                            if(sub_row==sub_col){
                                mat_Jordan(sub_row,sub_col) = eigenvalue[itr];
                            }
                            else if(sub_col == sub_row+1){
                                mat_Jordan(sub_row,sub_col) = 1;
                            }
                        }
                    } start_row = end_row;
                }
            }
        }
        std::cout<<"The Jordan Matrix should be: "<<std::endl << mat_Jordan << std::endl;
	}
};

