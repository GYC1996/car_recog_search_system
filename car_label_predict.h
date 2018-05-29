#ifndef PREDICT_CAR_H
#define PREDICT_CAR_H

#endif // PREDICT_CAR_H
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utils/trace.hpp>
using namespace cv;
using namespace cv::dnn;
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;
/* Find best class for the blob (i. e. class with maximal probability) */
static void getMaxClass(const Mat &probBlob, int *classId, double *classProb)
{
    Mat probMat = probBlob.reshape(1, 1); //reshape the blob to 1x1000 matrix
    Point classNumber;
    minMaxLoc(probMat, NULL, classProb, NULL, &classNumber);
    *classId = classNumber.x;
}
static std::vector<String> readClassNames(const char *filename )
{
    std::vector<String> classNames;
    std::ifstream fp(filename);
    if (!fp.is_open())
    {
        std::cerr << "File with classes labels not found: " << filename << std::endl;
        exit(-1);
    }
    std::string name;
    while (!fp.eof())
    {
        std::getline(fp, name);
        if (name.length())
            classNames.push_back( name.substr(name.find(' ')+1) );
    }
    fp.close();
    return classNames;
}

class CarPredict{
    public:
    void predict(Mat img);
    int getId() { return id; }
    int getId2() { return id2; }
    double getProb() { return confidence; }
    double getProb2() { return confidence2; }
    string getName() { return name; }
    string getName2() { return name2; }
    double getTime() { return costtime; }
    CarPredict();
    //~CarPredict();

    private:
    int id,id2;
    double confidence,confidence2;
    string name,name2;
    double costtime;
    Net net;
    std::vector<String> classNames;
    std::vector<String> classNames2;
};

CarPredict::CarPredict()
{
     CV_TRACE_FUNCTION();

     cout<<"MKLLLL"<<endl;

    cv::String modelTxt = "caffenet_two_labels.prototxt";
    //cout<<modelTxt<<"  "<<modelBin<<endl;
    cv::String const modelBin = "caffenet_train_iter_48700.caffemodel";
    //googlenet_car281_iter_48700.caffemodel
    //caffnet_car281_iter_48700.caffemodel
    String classNameFile = "label.txt";
    String classNameFile2= "label2.txt";

    try {
        net = dnn::readNetFromCaffe(modelTxt, modelBin);
        //net = dnn::readNetFromCaffe("net.prototxt","googlenet2_car281_iter_48700.caffemodel");
    }
    catch (const cv::Exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        if (net.empty())
        {
            std::cerr << "Can't load network by using the following files: " << std::endl;
            std::cerr << "prototxt:   " << modelTxt << std::endl;
            std::cerr << "caffemodel: " << modelBin << std::endl;
            std::cerr << "bvlc_googlenet.caffemodel can be downloaded here:" << std::endl;
            std::cerr << "http://dl.caffe.berkeleyvision.org/bvlc_googlenet.caffemodel" << std::endl;
            exit(-1);
        }
    }
    classNames = readClassNames(classNameFile.c_str());
    classNames2=readClassNames(classNameFile2.c_str());
}


void CarPredict::predict(Mat img)
{
    if (img.empty())
    {
        std::cerr << "img is empty." << std::endl;
        exit(-1);
    }
    //GoogLeNet accepts only 224x224 BGR-images
    //caffenet accepts only 227*227 BGR-image
    Mat inputBlob = blobFromImage(img, 1.0f, Size(227, 227),
                                      Scalar(78, 76, 75), false);   //Convert Mat to batch of images
    vector<Mat>prob;
    vector<String>outBlobName;
    outBlobName.push_back("prob_type");//输出层名
    outBlobName.push_back("prob_color");
    cv::TickMeter t;
    t.start();
    net.setInput(inputBlob, "data");        //set the network input
    net.forward(prob,outBlobName);         //compute output
    //net.setInput(inputBlob, "data");
    //Mat prob2= net.forward("prob_color");
    t.stop();
    int classId,classId2;
    double classProb,classProb2;
    getMaxClass(prob[0], &classId, &classProb);//find the best class
    getMaxClass(prob[1], &classId2, &classProb2);//prob[0] prob[1]分别输出10和281个向量

    id = classId;
    id2=classId2;
    name = classNames.at(classId);
    name2=classNames2.at(classId2);
    confidence = classProb;
    confidence2 = classProb2;
    costtime = (double)t.getTimeMilli() / t.getCounter();
}
