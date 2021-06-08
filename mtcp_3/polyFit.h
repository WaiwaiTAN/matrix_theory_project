#ifndef POLYFIT_H
#define POLYFIT_H
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <Eigen/IterativeLinearSolvers>


/*!
 * \brief loadData This function loads scatter data from file stream fs
 * \param fs File stream which data is loaded from, supposed to be Read-Only
 * \return A n by 2 matrix in which x-y data in a scatter chart is stored.
 */
Eigen::MatrixXd loadData(std::ifstream &fs);
/*!
 * \brief polyFit This function performs a polynomial fit.
 * \param mat The scatter data matrix which is supposed to be a n by 2 matrix.
 * \param linear Determine whether to perform a linear fit or not.
 * If this argument is false, this function will perform a parabolic fit.
 * \return The coefficients of the polynomial fit results.
 * In the case of linear fitting, the coefficients matrix is a 2 by 1 matrix.
 * Otherwise, it is a 3 by 1 matrix.
 */
Eigen::MatrixXd polyFit(const Eigen::MatrixXd &mat, bool linear);

/*!
 * \brief Estimate This function calculates a polynomial from x_start to x_finish.
 * \param mat The coefficients of the polynomial.
 * \param x_start The start point.
 * \param x_finish The last point.
 * \param m The number of steps.
 * \return The results which is supposed to be an m by 2 matrix.
 */
Eigen::MatrixXd Estimate(const Eigen::MatrixXd &mat, double x_start, double x_finish, int m,bool linear);
#endif // POLYFIT_H
