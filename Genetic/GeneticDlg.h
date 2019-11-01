
// GeneticDlg.h: 头文件

#pragma once


// CGeneticDlg 对话框
class CGeneticDlg : public CDialogEx
{
// 构造
public:
	CGeneticDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GENETIC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
private:
	CString m_eval;
	double m_lower;
	double m_upper;
	double m_group_size;
	int m_epoch;
	double m_ov_probability;
	double m_va_probability;
};
