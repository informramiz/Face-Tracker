//#include <iostream>
//#include <string>
//#include <opencv\cv.h>
////#include <cor.h>
//#include <opencv2\opencv.hpp>
//#include <direct.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//using namespace cv;
//
//void DetectAndDisplay( cv::CascadeClassifier face_cascade , cv::CascadeClassifier eye_cascade , cv::Mat frame );
//bool StartTracking( const std::string & video_file_name , const std::string & cascade_file_name );
//bool StartTracking( const std::string & cascade_file_name );
//void ShowOptions( );
//char * GetCurrentWorkingDirectory( );
//void BlurFace( cv::Mat & face );
//
//int main ( int argc , char * args[] )
//{
//	std::string video_file_name = "E:\\sample_video.mp4";
//	std::string lbp_face_cascade_name = "E:\\lbpcascade_frontalface.xml";
//
//	Mat mat;
//	
//	ShowOptions( );
//	return 0;	
//}
//
//char * GetCurrentWorkingDirectory( )
//{
//	char * buffer = NULL;
//	if ( ( buffer = _getcwd( NULL , 0 ) ) == NULL )
//	{
//		std::cerr << "Unable to get current working directory" << std::endl;
//		exit(1);
//	}
//
//	return buffer;
//}
//
//void ShowOptions( )
//{
//	std::string current_working_directory = GetCurrentWorkingDirectory( );
//	//std::string lbp_face_cascade_name = current_working_directory + "\\lbpcascade_frontalface.xml";
//	std::string lbp_face_cascade_name = current_working_directory + "\\lbpcascade_frontalface.xml";
//	std::string haar_face_cascade_name = current_working_directory + "\\haarcascade_frontalface_alt.xml";
//
//	int option = 0;
//
//	do
//	{
//		std::cout << "=======Please select vidoe source from options below=======" << std::endl;
//		std::cout << "1. Cam" << std::endl;
//		std::cout << "2. Video file" << std::endl;
//		std::cout << "Enter your choice : ";
//		std::cin >> option;
//
//		if ( option > 2 || option < 1 )
//			std::cerr << "Invalid option selected" << std::endl;
//
//	}while( option > 2 || option < 1 );
//
//	std::string video_file_name;
//	if ( option == 2 )
//	{
//		do
//		{
//			std::cout << "Enter file name (no space in name): " ;
//			std::cin >> video_file_name;
//
//			if ( video_file_name.empty( ) )
//				std::cerr << "Please enter a file name" << std::endl;
//
//		}while( video_file_name.empty( ) );
//	}
//
//	std::cout << std::endl;
//	int algorithm_type = 0;
//	do
//	{
//		std::cout << "=======Please select algorithm type=======" << std::endl;
//		std::cout << "1. LBP (less accurate/fast)" << std::endl;
//		std::cout << "2. HAAR (accurate/slow)" << std::endl;
//		std::cout << "Enter your choice : ";
//		std::cin >> algorithm_type;
//
//		if ( algorithm_type < 1 || algorithm_type > 2 )
//			std::cerr << "Inavlid option selected" << std::endl;
//
//	}while( algorithm_type < 1 || algorithm_type > 2 );
//
//	std::cout << "Face Tracking started....Press any key to stop tracking" << std::endl;
//
//	if ( option == 1 )
//	{
//		if ( algorithm_type == 1 )
//			StartTracking( lbp_face_cascade_name );
//		else if ( algorithm_type == 2 )
//			StartTracking( haar_face_cascade_name );
//	}
//	else if ( option == 2 )
//	{
//		if ( algorithm_type == 1 )
//			StartTracking( video_file_name , lbp_face_cascade_name );
//		else if ( algorithm_type == 2 )
//			StartTracking( video_file_name , haar_face_cascade_name );	
//	}
//}
//
//bool StartTracking( const std::string & video_file_name , const std::string & cascade_file_name )
//{
//	cv::VideoCapture video_capture( video_file_name );
//	CascadeClassifier face_cascade;
//	CascadeClassifier eye_cascade;
//
//	if ( video_capture.isOpened( ) == false )
//	{
//		std::cerr << "Could not open video file " << video_file_name << std::endl;
//		return false;
//	}
//
//	if ( face_cascade.load( cascade_file_name ) == false )
//	{
//		std::cerr << "Could not load face cascade file : " << cascade_file_name << std::endl;
//		return false;
//	}
//
//	namedWindow( "face" );
//	for( ;; )
//	{
//		Mat frame;
//		video_capture >> frame;
//		if ( frame.empty( ) == true )
//		{
//			std::cerr << "Frame empty--break" << std::endl;
//			return false;
//		}
//
//		DetectAndDisplay ( face_cascade , eye_cascade , frame );
//		//QDetectAndTrack( frame );
//		if( waitKey ( 2 ) >= 0 )
//			break;
//	}
//
//	return true;
//}
//
//bool StartTracking( const std::string & cascade_file_name )
//{
//	cv::VideoCapture video_capture( 0 );
//	CascadeClassifier face_cascade;
//	CascadeClassifier eye_cascade;
//
//	if ( video_capture.isOpened( ) == false )
//	{
//		std::cerr << "Could not open camera" << std::endl;
//		return false;
//	}
//
//	if ( face_cascade.load( cascade_file_name ) == false )
//	{
//		std::cerr << "Could not load face_cascade file : " << cascade_file_name << std::endl;
//		return false;
//	}
//
//	namedWindow( "face" );
//	for( ;; )
//	{
//		Mat frame;
//		video_capture >> frame;
//		if ( frame.empty( ) == true )
//		{
//			std::cerr << "Frame empty--break" << std::endl;
//			return false;
//		}
//
//		DetectAndDisplay ( face_cascade , eye_cascade , frame );
//		//QDetectAndTrack( frame );
//		if( waitKey ( 2 ) >= 0 )
//			break;
//	}
//
//	return true;
//}
//
//void DetectAndDisplay( cv::CascadeClassifier face_cascade , cv::CascadeClassifier eye_cascade , cv::Mat frame )
//{
//	std::vector<cv::Rect> faces;
//	cv::Mat frame_gray;
//
//	cv::cvtColor( frame , frame_gray , CV_BGR2GRAY );
//	equalizeHist ( frame_gray , frame_gray );
//
//	cv::Size face_size = cv::Size( frame_gray.cols/4 , frame_gray.cols/4 );
//	face_cascade.detectMultiScale ( frame_gray , faces , 1.1 , 3 , 0 | CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING , face_size );
//	
//
//	for( int i = 0 ; i < faces.size( ) ; i++ )
//	{
//		BlurFace( frame( faces[i] ) );
//		cv::rectangle( frame , faces[i] , CV_RGB( 0 , 255 , 1 ) , 1 );
//	}
//
//	imshow( "face" , frame );
//} 
//
//bool haarDetector ( const cv::Mat & image , cv::Mat & dest )
//{
//	std::string faceCascadeName = "haarcascade_frontalface_alt.xml";
//	cv::CascadeClassifier classifier;
//
//	if ( classifier.load ( faceCascadeName ) == 0 )
//	{
//		std::cout << "unable to load training data for classifier" << std::endl;
//		return false;
//	}
//
//	cv::Mat grayImage ;
//	if ( image.channels( ) == 3 )
//		cvtColor ( image , grayImage , CV_BGR2GRAY );
//	else if ( image.channels ( ) == 4 )
//		cvtColor ( image , grayImage , CV_BGRA2GRAY );
//	else
//		grayImage = image;
//
//	cv::equalizeHist ( grayImage , grayImage );
//	std::vector<cv::Rect> faces;
//	classifier.detectMultiScale ( grayImage , faces , 1.1 , 2 , 0 | CV_HAAR_SCALE_IMAGE | CV_HAAR_FIND_BIGGEST_OBJECT , cv::Size ( 80 , 80 ) );
//
//	if ( faces.size( ) == 0 )
//	{
//		std::cout << "No face detected" << std::endl;
//		return false;
//	}
//
//	dest = grayImage ( faces[0] );
//	return true;
//}
//
//bool lbpFaceDetector ( const cv::Mat & image , cv::Mat & dest )
//{
//	std::string faceCascadeName = "lbpcascade_frontalface.xml";
//	cv::CascadeClassifier classifier;
//
//	if ( classifier.load ( faceCascadeName ) == 0 )
//	{
//		std::cout << "unable to load training data for classifier" << std::endl;
//		return false;
//
//	}
//
//	cv::Mat grayImage ;
//	if ( image.channels( ) == 3 )
//		cvtColor ( image , grayImage , CV_BGR2GRAY );
//	else if ( image.channels ( ) == 4 )
//		cvtColor ( image , grayImage , CV_BGRA2GRAY );
//	else
//		grayImage = image;
//
//	equalizeHist ( grayImage , grayImage );
//	std::vector<cv::Rect> faces;
//	classifier.detectMultiScale ( grayImage , faces , 1.1 , 2 , 0 | CV_HAAR_SCALE_IMAGE  , cv::Size ( 80 , 80 ) );
//
//	if ( faces.size( ) == 0 )
//	{
//		std::cout << "No face detected" << std::endl;
//		return false;
//	}
//
//	dest = grayImage ( faces[0] );
//	return true;
//}
//
//void StartEdgeDetection( const std::string & video_file_name )
//{
//	cv::VideoCapture video_capture( video_file_name );
//
//	if ( video_capture.isOpened( ) == false )
//	{
//		std::cerr << "Could not open video file" << std::endl;
//		exit( 1 );
//	}
//
//	namedWindow ( "edges" );
//	Mat edges;
//	for( ;; )
//	{
//		Mat frame;
//		video_capture >> frame;
//		cvtColor( frame , edges , CV_BGR2GRAY );
//		
//		GaussianBlur( edges , edges , Size( 7 , 7 ) , 1.5 , 1.5 );
//		Canny ( edges , edges , 0 , 30 , 3 );
//		imshow ( "edges" , edges );
//
//		if( waitKey ( 30 ) >= 0 )
//			break;
//	}
//}
//
//void BlurFace( cv::Mat & face )
//{
//	//GaussianBlur( face , face , Size( 7 , 7 ) , 100 , 100 );
//	medianBlur( face , face , 51 );
//}