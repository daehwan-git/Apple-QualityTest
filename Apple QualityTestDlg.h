
// Apple QualityTestDlg.h: 헤더 파일
// 
#include "opencv2/opencv.hpp"
#include <opencv2/dnn/dnn.hpp>
#include <string.h>
#include <iostream>
#include <fstream>
//

#pragma once

using namespace cv;
using namespace std;
using namespace cv::dnn;

// CAppleQualityTestDlg 대화 상자
class CAppleQualityTestDlg : public CDialogEx
{
// 생성입니다.
public:
	CAppleQualityTestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_APPLE_QUALITYTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedTestbutton();
	afx_msg void OnBnClickedTestbutton2();
	afx_msg void OnDestroy();

	string yolo_cfg = "C:/Users/82108/source/repos/QualityTest1/tiny.cfg";
	string yolo_weights = "C:/Users/82108/source/repos/QualityTest1/tiny.weights";
	String classesFile = "C:/Users/82108/source/repos/QualityTest1/tiny.names";

	cv::Mat m_srcImage; // 입력 : 파일에서 읽어 들인 버퍼 변수
	cv::Mat m_dstImage; // 출력 : 필터 처리후 최종 결과 버퍼 변수
	CImage m_bmpBitmap;
	CStatic m_image;
	BITMAPINFO* m_pBitmapInfo_src; // Bitmap 정보를 담고 있는 구조체
	BITMAPINFO* m_pBitmapInfo_dst; // Bitmap 정보를 담고 있는 구조체

	void YOLO();
	void img_YOLO();
	void processDetections(const vector<Mat>& outs, const Mat& img, const vector<string>& classes, float confThreshold);
	vector<string> classes;
	vector<Mat> outs;
	Net m_net;
	Mat img_frame;
	Mat m_srcVideo;
	Mat m_srcVideo_resize;
	Mat m_dstVideo;
	VideoCapture* video;
	void Draw_src_video();
	void Draw_dst_video();
	float confThreshold = 0.6;
	CWinThread* m_pThread;
	CWinThread* m_pThread2;
	CWinThread* m_pThread3;
	bool m_bStop, m_bRun;
	bool m_bRun1;
	static UINT RunThread_srcvideo(LPVOID pParam);
	static UINT RunThread_dstvideo(LPVOID pParam);
	static UINT RunThread_YOLO(LPVOID pParam);
};
