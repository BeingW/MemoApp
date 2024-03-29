//DownKeyAction.cpp

/*
파일명 : DownKeyAction.cpp
작성일자 : 2019년 04월 15일
작성자 : 김영재
기능 : 아래쪽 방향키
수정 :
*/

#include "DownKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "CaretCoordinator.h"

//매개변수가 있는 생성자
DownKeyAction::DownKeyAction(CodeEditorForm *codeEditorForm) :KeyAction(codeEditorForm) {
}

//소멸자
DownKeyAction::~DownKeyAction() {
}

void DownKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	Long previousX;
	Long currentX;
	Long memoCurrent;
	Long lineCurrent;
	Long lineLength;
	Long previous;
	CaretCoordinator caretCoordinator;

	previousX = caretCoordinator.GetXPos(this->codeEditorForm->GetFontMatrix(), this->codeEditorForm->current);
	previous = this->codeEditorForm->memo->GetCurrent();
	memoCurrent = this->codeEditorForm->memo->Next();

	if (memoCurrent != previous) {
		this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
		this->codeEditorForm->current->First();
		lineLength = this->codeEditorForm->current->GetLength();
		lineCurrent = this->codeEditorForm->current->GetCurrent();
		currentX = caretCoordinator.GetXPos(this->codeEditorForm->GetFontMatrix(), this->codeEditorForm->current);

		while (currentX < previousX && lineCurrent != lineLength) {
			lineCurrent = this->codeEditorForm->current->Next();
			currentX = caretCoordinator.GetXPos(this->codeEditorForm->GetFontMatrix(), this->codeEditorForm->current);
		}
	}
}