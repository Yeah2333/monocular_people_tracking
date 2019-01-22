/**
* gaussian.hpp
* @author : koide
**/
#ifndef KKL_GAUSSIAN_HPP
#define KKL_GAUSSIAN_HPP

#include <cmath>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/StdVector>

#ifdef _USE_BOOST_ERF
#include <boost/math/special_functions/erf.hpp>
#endif

namespace kkl{
  namespace math{

template<typename T, int p>
double gaussianProbMul(const Eigen::Matrix<T, p, 1>& mean, const Eigen::Matrix<T, p, p>& cov, const Eigen::Matrix<T, p, 1>& x) {
  const double sqrtDet = std::sqrt(cov.determinant());
  const Eigen::Matrix<T, p, 1> dif = x - mean;
  const double lhs = 1.0 / (std::pow(2.0 * M_PI, p / 2.0) * sqrtDet);
  const double rhs = std::exp(-0.5 * ((dif.transpose() * cov.inverse() * dif))(0, 0));
  return lhs * rhs;
}


template<typename T, typename Matrix>
Eigen::Matrix<T, 3, 1> errorEllipse(const Matrix& cov, double kai) {
  Eigen::SelfAdjointEigenSolver<Eigen::Matrix<T, 2, 2>> solver(cov);

  Eigen::Matrix<T, 3, 1> params;
  params[0] = std::sqrt(kai * kai * solver.eigenvalues()[1]);
  params[1] = std::sqrt(kai * kai * solver.eigenvalues()[0]);
  params[2] = std::atan2(solver.eigenvectors()(0, 2), solver.eigenvectors()(1, 2));

  return params;
}

template<typename T, int p>
double squaredMahalanobisDistance(const Eigen::Matrix<T, p, 1>& mean, const Eigen::Matrix<T, p, p>& cov, const Eigen::Matrix<T, p, 1>& x){
  const Eigen::Matrix<T, p, 1> diff = x - mean;
  double distance = diff.transpose() * cov.inverse() * diff;
  return distance;
}

  }
}

#endif
