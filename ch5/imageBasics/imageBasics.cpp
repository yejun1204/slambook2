#include <iostream>
#include <chrono>

using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char **argv) {

  cout<<argc<<"  "<<argv[0]<<"  "<<argv[1]<<endl;  
  cv::Mat image;
  image=cv::imread(argv[1]);
  if(image.data==nullptr)
  {
    cerr<<"no data"<<argv[1]<<endl;
    return 0;
  }

  chrono::steady_clock::time_point t1=chrono::steady_clock::now();
  for(size_t y=0;y<image.rows;y++)
  {
    unsigned char *row_ptr=image.ptr<unsigned char>(y);
    for(size_t x=0;x<image.cols;x++)
    {
      unsigned char *data_ptr=row_ptr+x*image.channels();
      char swap[3];
      memcpy(swap,data_ptr,sizeof(unsigned char)*image.channels());
      for(size_t c=0;c<image.channels();c++)
      {
        data_ptr[c]=swap[c]*(3-c)/3;
      } 

    }
  }

  chrono::steady_clock::time_point t2=chrono::steady_clock::now();
  chrono::duration<double> time_used=chrono::duration_cast<chrono::duration<double>>(t2-t1);
  cout<<"image process:time"<<time_used.count()<<endl;
  cv::imshow("image",image);
  cv::waitKey(0);

  cv::Mat image_another=image;
  image_another(cv::Rect(0,0,100,200)).setTo(0);
  cv::imshow("image1",image);
  cv::waitKey(0);

  image_another=image;
  image_another(cv::Rect(0,0,100,200)).setTo(122);
  cv::imshow("image2",image);
  cv::waitKey(0);

  cv::destroyAllWindows();
  return 0;


 
}
