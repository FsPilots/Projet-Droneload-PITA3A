#ifndef C_Camera_H
#define C_Camera_H

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <pthread.h>

#include <opencv2/opencv.hpp>


#include "wxImagePanel.h"





#define FRONT 1
#define BOTTOM 2

class C_Camera
{
    private:
        int m_type ; // type de la cam�ra (FRONT ou BOTTOM)
        cv::VideoCapture m_cap;
        cv::Mat m_frame;
        cv::Mat m_frame2;
        int m_deviceID ;
        int m_apiID ;
        char m_name[256] ;
        int m_frame_width ;
        int m_frame_height ;
        bool m_ShowImage ;
        bool m_ReccodImage ;     // pour savoir si on enregistre ou non la vid�o
        bool m_IsRunning ;
        void ImageProcessing_WindowsDetection() ;
        void ImageProcessing_PointLaserDetection() ;
        int m_GreyLevelThreshold ;
        int m_OpenKernelSize ;
        int m_TopHatKernelSize ;
        int m_MaxRayon ;
        int m_MinArea ;
        int m_MoyenneMin ;
        int m_SigmaMax ;
        int m_SymetryCondition ;
        int m_HorizCondition ;
        int m_ProxyCondition ;

        void XYStabilizeProcessing_harris() ;
        //void XYStabilizeProcessing_TVL() ;

        wxImagePanel *m_imagepanel;

        bool ShowImage();
        double m_Altitude ;
        int m_TimeAltitude ;


        //donn�es concernant les fenetres
        int m_Center_x ;
        int m_Center_y ;
        int m_error_x;
        int m_error_y;







        int m_CameraActivity ;

    public:
        C_Camera();
        ~C_Camera();
        pthread_t m_CameraThread;
        pthread_mutex_t m_CameraMutex ;

        int Setup ( int i_channel, int i_type, char * i_name ) ;

        int Run() ;
        void ToggleRecording () ;
        bool IsRecording() ;
        void ToggleShowing () ;
        bool IsShowing() ;

        void ImageProcessing_QRCodeDetection() ;

        void SetRenderPanel ( wxImagePanel* i_imagepanel ) {m_imagepanel = i_imagepanel;};
        void SetCameraActivity ( int i_CameraActivity ) {m_CameraActivity = i_CameraActivity;};

        double GetAltitude() { return m_Altitude ; } ;
        double GetTimeAltitude() { return m_TimeAltitude ; } ;
        double GetCameraActivity() { return m_CameraActivity ; } ;


        double GetCenter_x() { return m_Center_x ; } ;
        double GetCenter_y() { return m_Center_y ; } ;
        void SetCenter_x ( double i_Center_x ) {m_Center_x = i_Center_x;};
        void SetCenter_y ( double i_Center_y ) {m_Center_y = i_Center_y;};



        void Correction_Distortions_Camera_Frontale ();



        int Geterrorx(){return m_error_x;};
        int Geterrory(){return m_error_y;};






} ;
#endif /* C_PortSerie_H */
