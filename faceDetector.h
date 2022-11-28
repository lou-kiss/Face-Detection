#pragma once

#include <iostream>
#include <string>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
//This header includes definition of 'rectangle()' function//
#include <opencv2/imgproc/imgproc.hpp>
//This header includes the definition of Cascade Classifier//
#include <opencv2/objdetect/objdetect.hpp>


using namespace std;
using namespace cv;

string trainedClassifierLocation = "C:/Users/30694/Documents/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml";
string trainedEyeLocation = "C:/Users/30694/Documents/opencv/sources/data/haarcascades/haarcascade_eye.xml";

int videoDetection() {
    //// 1. Load Haar feature-based cascade classifiers 

    CascadeClassifier faceCascade;
    CascadeClassifier eyesCascade;

    faceCascade.load(trainedClassifierLocation);
    eyesCascade.load(trainedEyeLocation);

    //// 2. Open camera and capture live video
    VideoCapture videoCapture(0);
    Mat inputFrame;
    Mat inputFrameGray;

    while (true) {
        // Read video frames and convert to grayscale
        videoCapture.read(inputFrame);
        cvtColor(inputFrame, inputFrameGray, COLOR_BGR2GRAY);

        //// 3. Find areas with faces using Haar cascade classifier
        vector<Rect> faces;
        faceCascade.detectMultiScale(inputFrameGray, faces);

        for (size_t i = 0; i < faces.size(); i++) {
            Point faceCenter{ faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2 };
            Size halfFace{ faces[i].width / 2, faces[i].height / 2 };

            // input, center, axes, angle=0, startAngle=0, endAngle=360, color, thickness=2
            ellipse(inputFrame, faceCenter, halfFace, 0, 0, 360, Scalar(255, 0, 255), 2);

            // Get the region of interest : face rectangle sub-frame in gray and colored
            Mat faceROIGray{ inputFrameGray(faces[i]) };

            //// 4. Find areas with eyes in faces using Haar cascade classifier
            vector<Rect> eyes;

            eyesCascade.detectMultiScale(faceROIGray, eyes);
            for (size_t j = 0; j < eyes.size(); j++) {
                Point eyeCenter{ faces[i].x + eyes[j].x + eyes[j].width / 2,
                                      faces[i].y + eyes[j].y + eyes[j].height / 2 };
                int radius{ cvRound((eyes[j].width + eyes[j].height) * 0.25) };
                // input, center, radius, color, thickness=2
                circle(inputFrame, eyeCenter, radius, Scalar(255, 0, 0), 2);
            }
        }

        //// 5. Show the output video
        imshow("Face Detection - OpenCV", inputFrame);
        if (waitKey(20) == 27) break; // Wait Esc key to end program  
    }
}

int imageDetection() {
    // Read image and Convert image to grayscale//
    Mat image;
    image = imread("C:\\Users\\30694\\source\\repos\\myCPP\\MyDumbPhoto.jpg");

    if (image.empty()) {
        // fail, bail out !
        cout << "Could not load image.";
        return -1;
    }

    Mat inputImageGray;
    cvtColor(image, inputImageGray, COLOR_BGR2GRAY);

    CascadeClassifier faceCascade;
    CascadeClassifier eyesCascade;

    faceCascade.load(trainedClassifierLocation);
    eyesCascade.load(trainedEyeLocation);

    //We are going to use a rectangular vector for the faces and the boundary//
    vector<Rect>faces;
    vector<Rect>boundary;

    //Detecting the faces included in the image matrix//
    faceCascade.detectMultiScale(image, faces);

    if (faces.size() < 1) {
        cout << "Could not find a face in the image";
        return 1;
    }

    // 1st step is Face Detection and Eyes Detection. //

    for (size_t i = 0; i < faces.size(); i++) {
        Point faceCenter{ faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2 };
        Size halfFace{ faces[i].width / 2, faces[i].height / 2 };

        // input, center, axes, angle=0, startAngle=0, endAngle=360, color, thickness=2
        ellipse(image, faceCenter, halfFace, 0, 0, 360, cv::Scalar(255, 0, 255), 2);

        // Get the region of interest : face rectangle sub-frame in gray and colored
        Mat faceROIGray{ image(faces[i]) };

        //// 4. Find areas with eyes in faces using Haar cascade classifier
        vector<Rect> eyes;
        eyesCascade.detectMultiScale(faceROIGray, eyes);

        vector <Point> eyeCenterVector;
        for (size_t j = 0; j < eyes.size(); j++) {
            Point eyeCenter{ faces[i].x + eyes[j].x + eyes[j].width / 2,
                                  faces[i].y + eyes[j].y + eyes[j].height / 2 };

            eyeCenterVector.push_back(eyeCenter);
            int radius{ cvRound((eyes[j].width + eyes[j].height) * 0.25) };

            // input, center, radius, color, thickness=2
            circle(image, eyeCenter, radius, cv::Scalar(255, 0, 0), 2);
        }
    }

    //Illustration of the Detected Face//
    namedWindow("Image Face Detection");
    imshow("Image Face Detection", image);
    waitKey(0);
    return 0;
}