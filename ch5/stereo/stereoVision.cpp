#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <Eigen/Core>
#include <pangolin/pangolin.h>
#include <unistd.h>

using namespace std;
using namespace Eigen;

// 文件路径
string left_file = "./left.png";
string right_file = "./right.png";


void showPointCloud(
    const vector<Vector4d, Eigen::aligned_allocator<Vector4d>> &pointcloud);

int main(int argc, char **argv) {
    double fx = 718.856, fy = 718.856, cx = 607.1928, cy = 185.2157;
    double b=0.573;

    cv::Mat left=cv::imread(left_file);
    cv::Mat right=cv::imread(right_file);
    cv::Ptr<cv::StereoSGBM> sgbm = cv::StereoSGBM::create(0, 96, 9, 8 * 9 * 9, 32 * 9 * 9, 1, 63, 10, 100, 32);
    cv::Mat disparity_sgbm, disparity;
    sgbm->compute(left,right,disparity_sgbm);
    disparity_sgbm.convertTo(disparity,CV_32F,1.0/16.0f);//signed short 2byte -> float 4byte 
    
    
    vector<Vector4d,Eigen::aligned_allocator<Vector4d>> pointcloud;

    cout<<disparity_sgbm.rows<<" "<<disparity_sgbm.cols<<" "<<disparity_sgbm.step[0]<<" "<<disparity_sgbm.step[1]<<" "<<disparity_sgbm.channels()<<endl;
    cout<<disparity.rows<<" "<<disparity.cols<<" "<<disparity.step[0]<<" "<<disparity.step[1]<<" "<<disparity.channels()<<endl;

    cout<<disparity_sgbm.type()<<" "<<disparity.type()<<" "<<disparity_sgbm.at<short>(10,0)<<" "<< disparity.at<float>(10,0)<<endl;
/*
+--------+----+----+----+----+------+------+------+------+
|        | C1 | C2 | C3 | C4 | C(5) | C(6) | C(7) | C(8) |
+--------+----+----+----+----+------+------+------+------+
| CV_8U  |  0 |  8 | 16 | 24 |   32 |   40 |   48 |   56 |
| CV_8S  |  1 |  9 | 17 | 25 |   33 |   41 |   49 |   57 |
| CV_16U |  2 | 10 | 18 | 26 |   34 |   42 |   50 |   58 |
| CV_16S |  3 | 11 | 19 | 27 |   35 |   43 |   51 |   59 |
| CV_32S |  4 | 12 | 20 | 28 |   36 |   44 |   52 |   60 |
| CV_32F |  5 | 13 | 21 | 29 |   37 |   45 |   53 |   61 |
| CV_64F |  6 | 14 | 22 | 30 |   38 |   46 |   54 |   62 |
+--------+----+----+----+----+------+------+------+------+
*/
    for(int v=0;v<left.rows;v++)
    {
        for(int u=0;u<left.cols;u++)
        {
            if(disparity.at<float>(v,u)<=0||disparity.at<float>(v,u)>=96.0) continue;

            Vector4d point(0,0,left.at<uchar>(v,u))   
           
            
            
        }
        

    }


    
}

void showPointCloud(const vector<Vector4d, Eigen::aligned_allocator<Vector4d>> &pointcloud) {

    if (pointcloud.empty()) {
        cerr << "Point cloud is empty!" << endl;
        return;
    }

    pangolin::CreateWindowAndBind("Point Cloud Viewer", 1024, 768);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    pangolin::OpenGlRenderState s_cam(
        pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
        pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0)
    );

    pangolin::View &d_cam = pangolin::CreateDisplay()
        .SetBounds(0.0, 1.0, pangolin::Attach::Pix(175), 1.0, -1024.0f / 768.0f)
        .SetHandler(new pangolin::Handler3D(s_cam));

    while (pangolin::ShouldQuit() == false) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        d_cam.Activate(s_cam);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glPointSize(2);
        glBegin(GL_POINTS);
        for (auto &p: pointcloud) {
            glColor3f(p[3], p[3], p[3]);
            glVertex3d(p[0], p[1], p[2]);
        }
        glEnd();
        pangolin::FinishFrame();
        usleep(5000);   // sleep 5 ms
    }
    return;
}