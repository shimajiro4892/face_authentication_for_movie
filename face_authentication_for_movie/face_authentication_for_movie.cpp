// face_authentication_for_movie.cpp : 動画上の人間の顔を検知し追跡する

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <vector>;

using namespace cv;
using namespace std;

int main()
{
	//使用する顔認識学習ファイルを設定する
	//OpenCVのdataフォルダーの中にあるやつをお好みで設定
	string cascade_path = "haarcascade_frontalface_alt2.xml";
	//対象の動画ファイルを読み込む
	VideoCapture capture = VideoCapture("test.mp4");
	//総フレーム数取得
	int Max_frame = capture.get(CV_CAP_PROP_FRAME_COUNT);

	//ローカル変数
	int frame_count;	//フレームカウント
	Mat frame;			//1フレーム分の画像を読み出す
	Mat frame_gray;		//読み出した画像をグレー画像に変換する
	
	//総フレーム回数分ループを回す
	for ( frame_count = 0; frame_count< Max_frame; frame_count++)
	{
		//フレームを読み込む
		capture.read(frame);
		//グレー画像作成
		cvtColor(frame, frame_gray, CV_BGR2GRAY);
		//ヒストグラム平坦化
		equalizeHist(frame_gray, frame_gray);
		//カスケード分類器の特徴量を取得
		vector <Rect> faces;
		CascadeClassifier cascade;
		cascade.load(cascade_path);
		cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 2);
		//検出した顔を描画する&出力する
		for (auto it = faces.begin(); it != faces.end(); ++it)
		rectangle(frame, it->tl(), it->br(), Scalar(0, 255, 255), 2, 8, 0);
		imshow("test", frame);
		waitKey(1);
	}
	destroyAllWindows();
	return 0;
}

