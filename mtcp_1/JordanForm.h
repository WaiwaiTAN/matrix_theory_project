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
        bool con_cal = 1;
        std::vector<std::string>::iterator iter;
        Eigen::MatrixXd mat_lambda(dim, dim);
        Eigen::MatrixXd mat_lambda_power(dim, dim);
        Eigen::MatrixXd mat_id(dim,dim);
        Eigen::EigenSolver<Eigen::MatrixXd> es(mat_in);
        mat_lambda_power = Eigen::MatrixXd::Identity(dim, dim);
        mat_id = Eigen::MatrixXd::Identity(dim, dim);
        std::cout << "The eigenvalues of the input matrix are:" << std::endl << es.eigenvalues() << std::endl;
//        std::cout << "Size of eigenvalues: " << std::endl << es.eigenvalues().size() << std::endl;
//        std::cout << "The first eigenvalue is: " << std::endl << es.eigenvalues()[0].real() << std::endl;
        std::cout << "Dim: " << dim << std::endl;

        eigenvalue.push_back(es.eigenvalues()[0].real());
        for (int eig = 0; eig < es.eigenvalues().size(); eig++){
            for(int nn = 0; nn < eigenvalue.size(); nn++)
            {
                if (es.eigenvalues()[eig].real() == eigenvalue[nn]){
                    con_cal = 0;
                }
            }
            if (!con_cal){break; }
            else{eigenvalue.push_back(es.eigenvalues()[eig].real()); }
        }

        for (int itr = 0; itr < eigenvalue.size(); itr++) {
            std::vector<float> DimKer;
            std::vector<float> d;
            std::vector<float> j;
            double eigenvalue_real = es.eigenvalues()[itr].real();
            std::cout<<eigenvalue_real<<std::endl;
            mat_lambda = mat_in - eigenvalue_real * mat_id;
            for (int power_row = 0; power_row < mat_lambda_power.rows(); power_row ++){
                for (int power_col = 0; power_col < mat_lambda_power.cols(); power_col ++){
                    if(abs(mat_lambda(power_row,power_col))<0.01){
                        mat_lambda(power_row,power_col) = 0;
                    }
                }
            }
            std::cout<<"MatLambda: "<<std::endl<<mat_lambda<<std::endl;

            while(con_pow){
                mat_lambda_power = mat_lambda_power * mat_lambda;
                for (int power_row = 0; power_row < mat_lambda_power.rows(); power_row ++){
                    for (int power_col = 0; power_col < mat_lambda_power.cols(); power_col ++){
                        if(abs(mat_lambda_power(power_row,power_col))<0.01){
                            mat_lambda_power(power_row,power_col) = 0;
                        }
                    }
                }
                std::cout<<"---------------------"<<std::endl<<mat_lambda_power<<std::endl;
                Eigen::FullPivLU<Eigen::MatrixXd> lu_decomp(mat_lambda_power);
                int dimker = dim - lu_decomp.rank();
                DimKer.push_back(dimker);
                if(dimker == dim){
                    con_pow = 0;
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


        }
    }

		
	virtual void print_ans() {
        int dim = mat_in.rows();
        Eigen::MatrixXd mat_Jordan = Eigen::MatrixXd::Zero(dim,dim);
        for (int itr = 0; itr < eigenvalue.size(); itr++){
            int sub_dim = 0;
            int start_row = 0, start_col = 0;
            for (int num = 0; num < D[itr].size(); num ++){
                sub_dim += D[itr][num];
            }
            Eigen::MatrixXd mat_subJor(sub_dim,sub_dim);
            for (int itr_j = 0; itr_j < J[itr].size(); itr_j++){
                int len_row = J[itr].size() - itr_j, len_col = J[itr].size() - itr_j;
                int num_j = J[itr][itr_j];
                if(num_j > 0){
                    for (int sub_itr = 0; sub_itr < num_j; sub_itr++){
                        for (int row = start_row; row < start_row+len_row*num_j; row++) {
                            for (int col = start_col; col < start_col+len_col*num_j; col++) {
                                if(row == col){mat_Jordan(row,col) = eigenvalue[itr]; }
                                else if(col - row == 1){mat_Jordan(row,col) = 1; }
                            }
                        }
                        start_row = start_row+len_row*num_j;
                        start_col = start_col+len_col*num_j;
                    }
                }
            }
        }
        std::cout<<"The Jordan Matrix should be: "<<std::endl << mat_Jordan << std::endl;
	}
};

