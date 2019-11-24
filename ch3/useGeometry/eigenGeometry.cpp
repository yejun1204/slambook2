#include <iostream>
#include <cmath>

using namespace std;

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

using namespace Eigen;



int main(int argc, char **argv) {
  
  Matrix3d rotation_matrix=Matrix3d::Identity();
  AngleAxisd rotation_vector(M_PI/4,Vector3d(0,0,1));
  cout.precision(3);
  cout<<"rotation matrix=\n"<<rotation_vector.matrix()<<endl;

  rotation_matrix=rotation_vector.toRotationMatrix();

  Vector3d v(1,0,0);
  Vector3d v_rotated=rotation_vector*v;
  cout<<"(1,0,0) after rotation (by angle axis)= "<<v_rotated.transpose()<<endl;

  v_rotated=rotation_matrix*v;
  cout<<"(1,0,0) after rotation (by matrix)= "<<v_rotated.transpose()<<endl;
  

  return 0;
}
