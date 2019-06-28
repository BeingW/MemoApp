
/*
파일명 : ShiftLeftKeyAction.cpp
작성일자 : 2019년 05월 14일
작성자 : 
기능 : 쉬프트 왼쪽 방향키 선택영역 설정
수정 :
*/

#include "ShiftLeftKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "FontMatrix.h"
#include "CaretCoordinator.h"
#include "RegionController.h"

ShiftLeftKeyAction::ShiftLeftKeyAction(CodeEditorForm *codeEditorForm) :KeyAction(codeEditorForm) {

}

ShiftLeftKeyAction:: ~ShiftLeftKeyAction() {

}

void ShiftLeftKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

	Glyph* previousLine;
	Glyph* nextLine;
	Long previousMemoCurrent, nextMemoCurrent;
	Long ret;
	Long lineCurrent;
	Long memoCurrent;

	previousMemoCurrent = this->codeEditorForm->memo->GetCurrent();
	previousLine = this->codeEditorForm->current->Clone();

	ret = this->codeEditorForm->current->GetCurrent();
	lineCurrent = this->codeEditorForm->current->Previous();

	if (ret == lineCurrent) {
		ret = this->codeEditorForm->memo->GetCurrent();
		memoCurrent = this->codeEditorForm->memo->Previous();

		if (ret != memoCurrent) {
			this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent);
			this->codeEditorForm->current->Last();
		}
	}

	nextMemoCurrent = this->codeEditorForm->memo->GetCurrent();
	nextLine = this->codeEditorForm->current->Clone();

	this->codeEditorForm->regionController->MakeRegion(previousLine, nextLine, previousMemoCurrent, nextMemoCurrent);

	this->codeEditorForm->Invalidate();
}
