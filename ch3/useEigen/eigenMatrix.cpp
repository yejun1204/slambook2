#include <iostream>

using namespace std;

#include <ctime>

#include <eigen3/Eigen/Core>

#include <eigen3/Eigen/Dense>

using namespace Eigen;

#define MATRIX_SIZE 50

int main(int argc, char **argv) {

Matrix<float,2,3> matrix_23;
Vector3d v_3d;
Matrix<float,3,1> vd_3d;

Matrix3d matrix_33=Matrix3d::Zero();
MatrixXd matrix_x;

matrix_23<<1,2,3,4,5,6;
cout<<"matrix 2x3 from 1 to 6:\n"<<matrix_23<<endl;


  return 0;
}
