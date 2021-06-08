#include"polyFit.h"
Eigen::MatrixXd loadData(std::fstream &fs){
    int N=50;


    MatrixXf A(N, 2);

    for (int i = 0; i < N; i++) {
        fs >> A(i,0);
        fs >> A(i,1);
    }
    fs.close();
    return A;
}

Eigen::MatrixXd polyFit(const Eigen::MatrixXd &mat, bool linear){
    int N=50;
    MatrixXf F_result;
    float norm;
    if(linear==true){
        MatrixXf A(N, 2);

        VectorXf b(N);

        for (int i = 0; i < N; i++) {
            A(i, 0)=mat(i,0);
            A(i, 1) = 1;
            b(i) = mat(i,1);
        }
        //SVD方法

        cout << "Here is the matrix A:\n" << A << endl;

        cout << "Here is the right hand side b:\n" << b << endl;

        F_result = A.bdcSvd(ComputeThinU | ComputeThinV).solve(b);
        cout << "The least-squares solution is:\n"
            << F_result << endl;
        //QR分解

        F_result = A.colPivHouseholderQr().solve(b);
        cout << "The solution using the QR decomposition is:\n"

            << F_result << endl;
        //ATAx = ATb
        F_result = (A.transpose() * A).ldlt().solve(A.transpose() * b);
        cout << "The solution using normal equations is:\n"

            << F_result << endl;
        //输出距离
        norm = (A * F_result - b).norm();
        cout << "The distance is :\n"
            << norm << endl;
    }
    else{
        MatrixXf A(N, 3);

        VectorXf b(N);

        for (int i = 0; i < N; i++) {
            A(i, 0)=mat(i,0);
            A(i, 1) = mat(i,0)*mat(i,0);
            A(i, 1) =1;
            b(i) = mat(i,1);
        }
        //ATAx = ATb
        F_result = (A.transpose() * A).ldlt().solve(A.transpose() * b);
        cout << "The solution using normal equations is:\n"

            << F_result << endl;
        //输出距离
        norm = (A * F_result - b).norm();
        cout << "The distance is :\n"
            << norm << endl;
    }

    return F_result;

}
Eigen::MatrixXd Estimate(const Eigen::MatrixXd &mat, double x_start, double x_finish, int m,bool linear){
    MatrixXf A(m,2);
    float delta = (x_finish-x_start)/m;
    if(linear == true){
        for(int i=0;i<m;i++){
            A(i,0)=x_start+i*delta;
            A(i,2)=A(i,0)*mat(0)+mat(1);
        }
    }
    else{
        for(int i=0;i<m;i++){
            A(i,0)=x_start+i*delta;
            A(i,2)=A(i,0)*A(i,0)*mat(0)+A(i,0)*mat(1)+mat(2);
        }
    }
    return A;
}
