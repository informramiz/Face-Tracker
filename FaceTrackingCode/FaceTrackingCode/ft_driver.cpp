#include <iostream>
#include "FaceTracker.h"

using namespace std;
using namespace cv;

//char * GetCurrentWorkingDirectory( );
void Start( );
void StartSimple(  );

#if 0 // this code is not used in this project and is here for some other purposes
bool lbpFaceDetector ( const Mat & image , std::vector<Rect> & dest );
void DetectGlasses();
bool DetectEyes( const cv::Mat & face , std::vector<Rect> & eye );
bool DetectSmile( const cv::Mat & face , std::vector<Rect> & smiles );
void SmileShutter( );
#endif

int main( int argc , char * args[] )
{
	/*std::string lbp_cascade_file_name = GetCurrentWorkingDirectory( );
	lbp_cascade_file_name += "\\training-files\\lbpcascade_frontalface.xml";

	std::string haar_cascade_file_name = GetCurrentWorkingDirectory( );
	haar_cascade_file_name += "\\training-files\\haarcascade_profileface.xml";*/

	//SmileShutter();
	//temp();
	Start( );
	return 0;
}

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

#if 0 // this code is not used in this project and is here for some other purposes
void SmileShutter( )
{
	std::string path = "C:\\Users\\Ramiz\\Documents\\opencv_smile_test_samples\\27.jpg";
	std::string output = "C:\\Users\\Ramiz\\Documents\\opencv_smile_test_samples\\27_1.jpg";

	Mat image = imread ( path  );

	if( image.empty() )
	{
		std::cout << "unable to load image : " << path << std::endl;
		return;
	}

	std::vector<Rect> faces;
	bool is_detected = lbpFaceDetector(image, faces);

	if( is_detected )
	{
		Mat face = image( faces[0] );
		vector<Rect> smiles;
		bool status = DetectSmile(face , smiles);  

		if( status )
		{
			cv::imshow( "smile" , face( smiles[0] ) );	
			cv::rectangle( face , smiles[0] , CV_RGB( 0 , 255 , 1 ) , 1 );
		}
	}

	cv::imshow( "image" , image );
	cv::imwrite( output , image );

	waitKey(0);
}

void DetectGlasses()
{
	std::string path = "C:\\Users\\Ramiz\\Desktop\\test images\\14.jpg";
	std::string output = "C:\\Users\\Ramiz\\Desktop\\output\\14.jpg";

	Mat image = imread ( path  );

	if( image.empty() )
	{
		std::cout << "unable to load image : " << path << std::endl;
		return;
	}

	std::vector<Rect> faces;
	lbpFaceDetector(image, faces);

	for( int i = 0 ; i < faces.size() ; i++)
	{
		Mat face = image( faces[i] );

		std::vector<Rect> eyes;
		bool status = DetectEyes( face , eyes );

		if ( status == true )
		{
			//cv::imshow("face", face);
		}

		for(int j = 0 ; j < eyes.size() ; j++)
		{
			Rect eye = eyes[j];

			//if ( ( eye.x > faces[i].x && eye.y > faces[i].y ) && ( eye.width < faces[i].width && eye.height < faces[i].height) )
			{
				//cv::imshow( "eye" , face(eye));
				cv::rectangle( face , eye , CV_RGB( 0 , 255 , 1 ) , 1 );
			}
		}

		cv::rectangle( image , faces[i] , CV_RGB( 0 , 255 , 1 ) , 1 );
	}

	cv::imshow( "image" , image );
	cv::imwrite( output , image );
	waitKey(0);
}

bool DetectSmile( const cv::Mat & face , std::vector<Rect> & smiles )
{
	std::string cascade_file_name = "C:\\opencv\\sources\\data\\haarcascades\\haarcascade_smile.xml";
	//std::string cascade_file_name = "training-files\\haarcascade_eye.xml";
	cv::CascadeClassifier classifier;

	if ( classifier.load ( cascade_file_name ) == 0 )
	{
		std::cout << "DetectSmile::unable to load training data for classifier from file : " << cascade_file_name << std::endl;
		return false;
	}

	cv::Mat grayImage ;
	if ( face.channels( ) == 3 )
		cvtColor ( face , grayImage , CV_BGR2GRAY );
	else if ( face.channels ( ) == 4 )
		cvtColor ( face , grayImage , CV_BGRA2GRAY );
	else
		grayImage = face;

	equalizeHist ( grayImage , grayImage );

	classifier.detectMultiScale ( grayImage , smiles , 1.1 , 2 , 0 | CV_HAAR_SCALE_IMAGE | CV_HAAR_FIND_BIGGEST_OBJECT  , cv::Size ( face.cols / 4 , face.rows / 4 ) );

	if ( smiles.size( ) == 0 )
	{
		std::cout << "No smile detected" << std::endl;
		return false;
	}

	std::cout << "Smiles detected: " << smiles.size( ) << std::endl;
	return true;	
}

bool DetectEyes( const cv::Mat & face , std::vector<Rect> & eyes )
{
	std::string cascade_file_name = "training-files\\haarcascade_mcs_eyepair_small.xml";
	//std::string cascade_file_name = "training-files\\haarcascade_eye.xml";
	cv::CascadeClassifier classifier;

	if ( classifier.load ( cascade_file_name ) == 0 )
	{
		std::cout << "DetectEyes::unable to load training data for classifier from file : " << cascade_file_name << std::endl;
		return false;
	}

	cv::Mat grayImage ;
	if ( face.channels( ) == 3 )
		cvtColor ( face , grayImage , CV_BGR2GRAY );
	else if ( face.channels ( ) == 4 )
		cvtColor ( face , grayImage , CV_BGRA2GRAY );
	else
		grayImage = face;

	equalizeHist ( grayImage , grayImage );

	classifier.detectMultiScale ( grayImage , eyes , 1.1 , 2 , 0 | CV_HAAR_SCALE_IMAGE | CV_HAAR_FIND_BIGGEST_OBJECT  , cv::Size ( face.cols / 10 , face.rows / 10 ) );

	if ( eyes.size( ) == 0 )
	{
		std::cout << "No eye detected" << std::endl;
		return false;
	}

	std::cout << "Eyes detected: " << eyes.size( ) << std::endl;
	return true;	
}

bool lbpFaceDetector ( const Mat & image , std::vector<Rect> & output_faces )
{
	//string faceCascadeName = "training-files\\lbpcascade_frontalface.xml";
	string faceCascadeName = "training-files\\haarcascade_frontalface_default.xml";
	CascadeClassifier classifier;

	if ( classifier.load ( faceCascadeName ) == 0 )
	{
		cout << "unable to load training data for classifier" << endl;
		return false;
	}

	Mat grayImage ;
	if ( image.channels( ) == 3 )
		cvtColor ( image , grayImage , CV_BGR2GRAY );
	else if ( image.channels ( ) == 4 )
		cvtColor ( image , grayImage , CV_BGRA2GRAY );
	else
		grayImage = image;

	equalizeHist ( grayImage , grayImage );
	classifier.detectMultiScale ( grayImage , output_faces );

	if ( output_faces.size( ) == 0 )
	{
		cout << "No face detected" << endl;
		return false;
	}

	std::cout << "faces detected : " << output_faces.size() << std::endl;
	return true;
}

#endif //#if 0

void Start(  )
{
	int option = 0;

	do
	{
		std::cout << "=======Please select video source from options below=======" << std::endl;
		std::cout << "1. Webcam" << std::endl;
		std::cout << "2. Video file" << std::endl;
		std::cout << "Enter your choice : ";
		std::cin >> option;

		if ( option > 2 || option < 1 )
			std::cerr << "Invalid option selected" << std::endl;

	}while( option > 2 || option < 1 );

	std::string video_file_name;
	if ( option == 2 )
	{
		do
		{
			std::cout << "Enter file name (no space in name): " ;
			std::cin >> video_file_name;

			if ( video_file_name.empty( ) )
			{
				std::cerr << "Please enter a file name" << std::endl;
			}

		}while( video_file_name.empty( ) );
	}

	std::cout << "Face Tracking starting....Click on video window and press any key to stop tracking" << std::endl;

	FaceTracker face_tracker;
	
	if ( option == 1 )
		face_tracker.StartCamShift( );
	else if ( option == 2 )
		face_tracker.StartCamShift( video_file_name );
}

void StartSimple(  )
{
	std::cout << "Face Tracking starting....Click on video window and press any key to stop tracking" << std::endl;
	waitKey( 100 );

	FaceTracker face_tracker;
	face_tracker.StartCamShift( );
}