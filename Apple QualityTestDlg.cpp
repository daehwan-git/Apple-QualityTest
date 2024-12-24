
// Apple QualityTestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Apple QualityTest.h"
#include "Apple QualityTestDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace cv;
using namespace std;
using namespace cv::dnn;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAppleQualityTestDlg 대화 상자



CAppleQualityTestDlg::CAppleQualityTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_APPLE_QUALITYTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAppleQualityTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAppleQualityTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TestButton, &CAppleQualityTestDlg::OnBnClickedTestbutton)
	ON_BN_CLICKED(IDC_TestButton2, &CAppleQualityTestDlg::OnBnClickedTestbutton2)
END_MESSAGE_MAP()


// CAppleQualityTestDlg 메시지 처리기

BOOL CAppleQualityTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CAppleQualityTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CAppleQualityTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (m_bmpBitmap.IsNull() == false)
		{
			// display image area
			CRect rtROI;
			GetDlgItem(IDC_Image)->GetWindowRect(&rtROI);
			int picture_sizeX = rtROI.Width();
			int picture_sizeY = rtROI.Height();

			// get picture-control dc
			CDC* pDc = m_image.GetWindowDC();
			CDC memdc;
			memdc.CreateCompatibleDC(pDc);
			memdc.SelectObject(m_bmpBitmap);

			int width = m_bmpBitmap.GetWidth();
			int height = m_bmpBitmap.GetHeight();
			pDc->StretchBlt(0, 0, picture_sizeX, picture_sizeY, &memdc, 0, 0, width, height, SRCCOPY);

			// release dc to picture-control
			m_image.ReleaseDC(pDc);
		}

		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CAppleQualityTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAppleQualityTestDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	if (m_pThread != NULL)
	{
		m_bStop = true;
		m_pThread = NULL;
	}

	if (m_pThread2 != NULL)
	{
		m_bStop = true;
		m_pThread2 = NULL;
	}

	if (m_pThread3 != NULL)
	{
		m_bStop = true;
		m_pThread3 = NULL;
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

UINT CAppleQualityTestDlg::RunThread_srcvideo(LPVOID pParam)
{
	CAppleQualityTestDlg* g_Dlg = (CAppleQualityTestDlg*)pParam;
	if (g_Dlg)
	{
		while (g_Dlg->m_bStop == false)
		{
			if (g_Dlg->m_bRun == true)
			{
				g_Dlg->Draw_src_video();
			}

			Sleep(1);
		}
	}
	return 0;
}

UINT CAppleQualityTestDlg::RunThread_dstvideo(LPVOID pParam)
{
	CAppleQualityTestDlg* g_Dlg = (CAppleQualityTestDlg*)pParam;
	if (g_Dlg)
	{
		while (g_Dlg->m_bStop == false)
		{
			if (g_Dlg->m_bRun == true)
			{
				g_Dlg->Draw_dst_video();
			}

			Sleep(1);
		}
	}

	return 0;
}

UINT CAppleQualityTestDlg::RunThread_YOLO(LPVOID pParam)
{
	CAppleQualityTestDlg* g_Dlg = (CAppleQualityTestDlg*)pParam;
	if (g_Dlg)
	{
		ifstream ifs(g_Dlg->classesFile.c_str());
		string line;
		while (getline(ifs, line))
		{
			g_Dlg->classes.push_back(line);
		}
		g_Dlg->m_net = readNetFromDarknet(g_Dlg->yolo_cfg, g_Dlg->yolo_weights);
		g_Dlg->m_net.setPreferableBackend(DNN_BACKEND_OPENCV);
		g_Dlg->m_net.setPreferableTarget(DNN_TARGET_CPU);

		while (g_Dlg->m_bStop == false)
		{
			if (g_Dlg->m_bRun1 == true)
			{
				g_Dlg->YOLO();
			}

			Sleep(1);
		}
	}

	return 0;
}


void CAppleQualityTestDlg::OnBnClickedTestbutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("ALL files(*.*)|*.*|");
	CFileDialog Dlg(TRUE, NULL, NULL, OFN_READONLY, str);
	if (Dlg.DoModal() == IDOK)
	{
		CString path = Dlg.GetPathName();
		CT2CA pszString(path);
		std::string strPath(pszString);

		video = new VideoCapture(strPath);
		if (!video->isOpened())
		{
			MessageBox(L"동영상 파일을 열 수 없습니다.");
			return;
		}
	}
	m_bRun = true;
	m_bStop = false;
	m_pThread2 = AfxBeginThread(RunThread_srcvideo, this);
}


void CAppleQualityTestDlg::OnBnClickedTestbutton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pThread = AfxBeginThread(RunThread_dstvideo, this);
}

void CAppleQualityTestDlg::Draw_src_video()
{
	CRect rect;
	CDC* pDC = GetDlgItem(IDC_Image)->GetDC();  // Picture Control에서 DC 얻기
	GetDlgItem(IDC_Image)->GetClientRect(&rect);  // Picture Control의 크기를 얻음
	int width = rect.Width();
	int height = rect.Height();

	while (video->read(m_srcVideo))
	{
		cv::resize(m_srcVideo, m_srcVideo, cv::Size(width, height));

		// OpenCV Mat을 HDC로 출력하기 위해 Mat을 BITMAP으로 변환
		CImage image;
		image.Create(m_srcVideo.cols, m_srcVideo.rows, 24);  // 24-bit BMP 이미지 생성

		// Mat 데이터를 CImage로 복사
		uchar* psrc = m_srcVideo.data;  // OpenCV Mat 데이터 포인터
		uchar* pdst = (uchar*)image.GetBits();  // CImage 데이터 포인터
		int pitch = image.GetPitch();

		// OpenCV의 Mat 데이터를 CImage로 복사하는 과정
		for (int y = 0; y < m_srcVideo.rows; y++)
		{
			memcpy(pdst, psrc, m_srcVideo.cols * 3);  // 한 줄씩 복사
			psrc += m_srcVideo.step;
			pdst += pitch;
		}
		image.Draw(pDC->m_hDC, 0, 0, width, height);

		if (waitKey(30) == 27)
			break;  // ESC 키를 누르면 종료   

		ReleaseDC(pDC);  // DC 해제
		pDC = GetDlgItem(IDC_Image)->GetDC();  // DC 다시 얻기
	}
	ReleaseDC(pDC);  // DC 해제
}

void CAppleQualityTestDlg::Draw_dst_video()
{
	m_bRun1 = false;
	m_bStop = false;
	m_pThread3 = AfxBeginThread(RunThread_YOLO, this);

	CRect rect;
	CDC* pDC = GetDlgItem(IDC_Image2)->GetDC();  // Picture Control에서 DC 얻기
	GetDlgItem(IDC_Image2)->GetClientRect(&rect);  // Picture Control의 크기를 얻음
	int width = rect.Width();
	int height = rect.Height();

	// OpenCV Mat을 HDC로 출력하기 위해 Mat을 BITMAP으로 변환
	CImage image;
	image.Create(width, height, 24);  // 24-bit BMP 이미지 생성

	// Mat 데이터를 CImage로 복사
	uchar* pdst = (uchar*)image.GetBits();  // CImage 데이터 포인터
	int pitch = image.GetPitch();
	cv::Mat displayImage(height, width, CV_8UC4, pdst);
	while (1)
	{
		m_srcVideo.copyTo(m_dstVideo);

		//cvtColor(m_dstVideo, m_dstVideo, COLOR_BGRA2BGR);

		m_bRun1 = true;

		processDetections(outs, m_dstVideo, classes, confThreshold);

		// OpenCV Mat을 HDC로 출력하기 위해 Mat을 BITMAP으로 변환
		CImage image;
		image.Create(m_dstVideo.cols, m_dstVideo.rows, 24);  // 24-bit BMP 이미지 생성

		// Mat 데이터를 CImage로 복사
		uchar* psrc = m_dstVideo.data;  // OpenCV Mat 데이터 포인터
		uchar* pdst = (uchar*)image.GetBits();  // CImage 데이터 포인터
		int pitch = image.GetPitch();

		// OpenCV의 Mat 데이터를 CImage로 복사하는 과정
		for (int y = 0; y < m_dstVideo.rows; y++)
		{
			memcpy(pdst, psrc, m_dstVideo.cols * 3);  // 한 줄씩 복사
			psrc += m_dstVideo.step;
			pdst += pitch;
		}

		// Picture Control에 이미지 출력
		image.Draw(pDC->m_hDC, 0, 0, width, height);

		if (waitKey(30) == 27)
			break;  // ESC 키를 누르면 종료

		ReleaseDC(pDC);  // DC 해제
		pDC = GetDlgItem(IDC_Image2)->GetDC();  // DC 다시 얻기
	}

	ReleaseDC(pDC);  // DC 해제
}

void CAppleQualityTestDlg::YOLO()
{
	Mat inputBlob = blobFromImage(m_dstVideo, 1 / 255.f, Size(416, 416), Scalar(), true, false);
	m_net.setInput(inputBlob);

	vector<String > outNames = m_net.getUnconnectedOutLayersNames();

	m_net.forward(outs, outNames);
}

void CAppleQualityTestDlg::processDetections(const vector<Mat>& outs, const Mat& img, const vector<string>& classes, float confThreshold)
{
	for (size_t i = 0; i < outs.size(); ++i)
	{
		float* data = (float*)outs[i].data;
		for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols) //탐지된 객체에 대해 반복
		{
			Mat scores = outs[i].row(j).colRange(5, outs[i].cols); //클래스 확률을 저장한 부분
			Point classIdPoint;
			double confidence;

			//클래스 확률 중 가장 높은 값을 찾음
			minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);

			if (confidence > confThreshold)
			{
				//객체의 bounding box 좌표 계산
				int centerX = (int)(data[0] * img.cols);
				int centerY = (int)(data[1] * img.rows);
				int width = (int)(data[2] * img.cols);
				int height = (int)(data[3] * img.rows);

				//좌상단 좌표 계산
				int left = centerX - width / 2;
				int top = centerY - height / 2;

				//bounding box 그리기

				rectangle(img, Point(left, top), Point(left + width, top + height), Scalar(0, 255, 0), 3);
				String label = format("%.2f", confidence);
				if (!classes.empty())
				{
					CV_Assert(classIdPoint.x < (int)classes.size());
					label = classes[classIdPoint.x] + ":" + label;
				}

				int baseLine;
				Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
				top = max(top, labelSize.height);
				rectangle(img, Point(left, top - round(1.5 * labelSize.height)), Point(left + round(1.5 * labelSize.width), top + baseLine), Scalar(255, 255, 255), FILLED);
				putText(img, label, Point(left, top), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 0), 1);

			}
		}
	}
}