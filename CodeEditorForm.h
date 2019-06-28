/*
파일명 : CodeEitorForm.h
작성일자 : 2019년 03월 27일
작성자 : 허수진
기능 : CodeEitorForm CFrameWnd 선언
*/
//CodeEitorForm.h

#pragma once

#ifndef _CODEEDITORFORM_H
#define _CODEEDITORFORM_H

#include "Subject.h"
#include <afxwin.h>
#include <string>

using namespace std;

typedef signed long int Long;

class Glyph;
class Memo;
class FontMatrix;
class File;
class CaretController;
class WriteState;
class WriteStateAppend;
class WriteStateInsert;
class RegionController;
class CodeEditorForm :public CFrameWnd, public Subject {
public:
	CodeEditorForm();
public:
	Glyph *current;
	Glyph *memo;
	CDC *textDC;
	//CDC *cdc;
	CFont font;
	CFont* oldFont;
	CPoint cPoint;
	CaretController *caretController;
	FontMatrix *fontMatrix;
	File *file;
	BOOL isComposing;
	WriteState* state;
	WriteState* states[2];
	RegionController *regionController;
	//CDC TextDc = CDC();
#if 0
	WriteState* writeState;
	WriteStateAppend* writeStateAppend;
	WriteStateInsert* writeStateInsert;
#endif
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnImeStartComposition(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImeComposition(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImeChar(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint cPoint);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnPaint();
	afx_msg void OnMenuClicked(UINT id);
#if 0
	afx_msg void OnFontMenuClicked();
	afx_msg void OnSaveMenuClicked();
	afx_msg void OnSaveAsMenuClicked();
#endif
	afx_msg void OnLoadMenuClicked();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
public:
	BOOL GetIsComposing() const;
	FontMatrix* GetFontMatrix() const;
	void TakeIn(string text);
private:
	
};
inline BOOL CodeEditorForm::GetIsComposing() const {
	return this->isComposing;
}
inline FontMatrix* CodeEditorForm::GetFontMatrix() const {
	return this->fontMatrix;
}
#endif //_CODEEDITORFORM_H