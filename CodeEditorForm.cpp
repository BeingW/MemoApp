//CodeEditorForm.cpp
/*
파일명 : CodeEditorForm.cpp
작성일자 : 2019년 03월 27일
작성자 : 김영재
기능 : CodeEditorForm (View)
수정 : Line 의 GetContents 를 이용한 글 출력
		20190402 OnFontMenuClicked 기능구현 , OnClose에 저장기능 구현
		20190403 OnSaveMenuClicked 기능구현, OnSaveAsMenuClicked 기능 구현
		20190411 OnPaint 글자 높이수정
*/

#include "CodeEditorForm.h"
#include "Memo.h"
#include "Line.h"
#include "SingleByteLetter.h"
#include "DoubleByteLetter.h"
#include "resource.h"
#include "File.h"
#include "CaretController.h"
#include "CaretCoordinator.h"
#include "FontMatrix.h"
#include "KeyActionFactory.h"
#include "KeyAction.h"
#include "CommandFactory.h"
#include "Command.h"
#include "GlyphFactory.h"
#include "WriteState.h"
#include "WriteStateAppend.h"
#include "WriteStateInsert.h"
#include "RegionController.h"
#include <afxdlgs.h>
#include <string>
using namespace std;

BEGIN_MESSAGE_MAP(CodeEditorForm, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CHAR()
	ON_MESSAGE(WM_IME_STARTCOMPOSITION, OnImeStartComposition)
	ON_MESSAGE(WM_IME_COMPOSITION, OnImeComposition)
	ON_MESSAGE(WM_IME_CHAR, OnImeChar)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_PAINT()
	ON_COMMAND_RANGE(IDM_FORMAT_FONT, IDM_FILE_LOAD, OnMenuClicked)
#if 0
	ON_COMMAND(IDM_FORMAT_FONT, OnFontMenuClicked)
	ON_COMMAND(IDM_FILE_SAVE, OnSaveMenuClicked)
	ON_COMMAND(IDM_FILE_SAVEAS, OnSaveAsMenuClicked)
#endif
	ON_COMMAND(IDM_FILE_LOAD, OnLoadMenuClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


CodeEditorForm::CodeEditorForm() {
	this->isComposing = FALSE;
	this->current = NULL;
	this->memo = NULL;
	this->file = NULL;
	this->caretController = NULL;
	this->fontMatrix = NULL;
}

int CodeEditorForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);
	Long memoCurrent;

	this->textDC = GetDC();

	this->memo = new Memo;
	this->current = new Line;
	this->file = new File;
	this->fontMatrix = new FontMatrix(this->textDC);
	this->memo->Add(this->current);
	memoCurrent = this->memo->GetCurrent();
	this->caretController = new CaretController(this, this->current, memoCurrent);
	
	//this->font->CreateFontA(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial")); 
	//this->dc->SelectObject(font);
	this->oldFont = NULL;

	this->states[0] = WriteStateAppend::WriteAppendInstance(this);
	this->states[1] = WriteStateInsert::WriteInsertInstance(this); 
	this->state = this->states[0];

	this->regionController = new RegionController(this);

	ReleaseDC(this->textDC);
	this->Notify();
	return 0;
}

void CodeEditorForm::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	
	this->state->ChangeState();

	this->state->OnChar(nChar, nRepCnt, nFlags);

	this->Notify();
	Invalidate();
}

LRESULT CodeEditorForm::OnImeStartComposition(WPARAM wParam, LPARAM lParam) {
	this->state->ChangeState();

	this->state->OnImeStartComposition(wParam, lParam);

	this->Notify();
	Invalidate();

	return 0;
}

LRESULT CodeEditorForm::OnImeComposition(WPARAM wParam, LPARAM lParam) {

	this->state->ChangeState();

	this->state->OnImeComposition(wParam, lParam);

	this->Notify();
	Invalidate();

	return 0;	
}

LRESULT CodeEditorForm::OnImeChar(WPARAM wParam, LPARAM lParam) {
	
	this->state->ChangeState();

	this->state->OnImeChar(wParam, lParam);

	this->Notify();
	Invalidate();

	return 0;
}

void CodeEditorForm::OnLButtonDown(UINT nFlags, CPoint cPoint) {
	Long memoCurrent;
	Long lineLength;
	Long lineCurrent;
	Long xPos = 0;
	CaretCoordinator caretCoordinator;
	
	this->memo->Move(cPoint.y / this->fontMatrix->GetHeight());
	memoCurrent = this->memo->GetCurrent();
	this->current = this->memo->GetAt(memoCurrent);
	lineCurrent=this->current->First();
	lineLength = this->current->GetLength();

	while (lineCurrent<lineLength && cPoint.x >= xPos) {
		lineCurrent=this->current->Next();
		xPos = caretCoordinator.GetXPos(this->fontMatrix, this->current);
	}
	this->Notify();
	Invalidate();
}

void CodeEditorForm::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	KeyActionFactory keyActionFactory(this);
	KeyAction *keyAction;

	keyAction = keyActionFactory.Make(nChar);
	if (keyAction != NULL) {
		keyAction->OnKeyDown(nChar, nRepCnt, nFlags);
	}

#if 0
	if ( !((GetKeyState(VK_SHIFT))) < 0){
		this->regionController->CleanRegion();
	}
#endif

	this->Notify();
	Invalidate();
}

void CodeEditorForm::OnSetFocus(CWnd * pOldWnd){

	this->caretController->ShowCaret(TRUE);
}

void CodeEditorForm::OnKillFocus(CWnd * pNewWnd){
	
	this->caretController->ShowCaret(FALSE);
}

void CodeEditorForm::OnPaint() {
	Long memoLength;
	Glyph *line;
	Long i = 0;
	string content = "";
	CString cText;
	Long height;
	CPaintDC dc(this);
	CPaintDC rgnDC(this);
	Long stringNumber = 0;

	oldFont = dc.SelectObject(&font);

	//기존폰트매트릭스가 있을 때, 매트릭스를 지운다.
	if (fontMatrix != NULL) {
		delete fontMatrix;
	}

	fontMatrix = new FontMatrix(&dc);

	memoLength = this->memo->GetLength();
	this->ScreenToClient(&this->cPoint);
	while (i < memoLength) {
		line = this->memo->GetAt(i);

		content = line->GetContents();
		stringNumber = content.length();
		height = this->fontMatrix->GetHeight();
		cText = CString(content.c_str());
		
		dc.TextOut(0, i * height, cText, stringNumber);
		i++;
	}

	if (this->regionController->GetIsBeing() == TRUE){
		this->regionController->DrawRegion();
	}
	
	this->Notify();
}

void CodeEditorForm::OnMenuClicked(UINT id) {
	CommandFactory commandFactory(this);
	Command *command;
	command = commandFactory.Make(id);

	if (command != NULL){
		command->Execute();
	}
}

/*
함수명: OnLoadMenuClicked
기능: 불러오다
수정 :
*/
void CodeEditorForm::OnLoadMenuClicked() {
	int messageBox;
	string contents;
	string pathName;
	string fileName;
	string text;

	messageBox = MessageBox("저장하시겠습니까?", "저장", MB_YESNOCANCEL);

	switch (messageBox) {
	case IDYES:
		fileName = this->file->GetFileName();

		if (fileName == "*.txt") {
			this->file->OpenDialog(FALSE);
			pathName = this->file->GetPathName();
			fileName = this->file->GetFileName();
			this->SetWindowText(fileName.c_str());
		}

		contents = this->memo->GetContents();
		this->file->Save(contents, pathName);
		break;

	default:
		break;
	}

	this->file->OpenDialog(TRUE);
	pathName = this->file->GetPathName();
	fileName = this->file->GetFileName();
	text = this->file->Load(pathName);
	this->SetWindowText(fileName.c_str());
	this->TakeIn(text);
	Invalidate();
}

/*
함수명: TakeIn
기능: 텍스트를 기존메모에 끼운다
수정 : 
*/
void CodeEditorForm::TakeIn(string text) {
	Glyph *memo;
	Glyph *line;
	Glyph *letter;
	char content[3] = { 0, };
	Long i = 0;
	Long textSize;
	Long contentASCIICODE;

	memo = new Memo;
	line = new Line;

	memo->Add(line);
	textSize = text.length();
	
	while (i < textSize) {
		content[0] = text[i];

		if (content[0] != '\r') {

			if (content[0] != '\n') {
				contentASCIICODE = Long(content[0]);

				if (32 <= contentASCIICODE && contentASCIICODE <= 126 || contentASCIICODE == 9) {
					letter = new SingleByteLetter(content[0]);
					
				}
				else {

					letter = new DoubleByteLetter(content);
				}
				line->Add(letter);
			}
			else {
				line = new Line;
				memo->Add(line);
			}
		}
		i++;
	}
	this->memo = memo;
}

/*
함수명: OnClose
기능: 창을 닫는다
수정 : Cancle 수정 필요
*/
void CodeEditorForm::OnClose() {
	int messageBox;

	messageBox = MessageBox((LPCTSTR)"저장하시겠습니까?", (LPCTSTR)"저장", MB_YESNOCANCEL);
	if (messageBox == IDYES || messageBox == IDNO) {
		if (messageBox == IDYES) {
			//this->OnSaveMenuClicked();
		}

		if (this->memo != NULL) {
			delete this->caretController;
			delete this->memo;
		}
		CFrameWnd::OnClose();
	}
}