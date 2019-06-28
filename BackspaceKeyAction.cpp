//BackspaceKeyAction.cpp
/*
파일명 : BackspaceKeyAction.cpp
작성일자 : 2019년 04월 17일
작성자 : 김영재
기능 : 백스페이스 키
수정 :
*/

#include "BackspaceKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"

BackspaceKeyAction::BackspaceKeyAction(CodeEditorForm *codeEditorForm) :KeyAction(codeEditorForm) {
}

BackspaceKeyAction::~BackspaceKeyAction() {
}

void BackspaceKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long lineCurrent;
	Long memoCurrent;
	Long ret;
	Long cloneLength;
	Long i = 0;
	Glyph *previous;
	Glyph *letter;
	Long lineLength;

	lineCurrent = this->codeEditorForm->current->GetCurrent();
	lineLength = this->codeEditorForm->current->GetLength();

	if (lineCurrent > 0) {
		this->codeEditorForm->current->Remove(lineCurrent - 1);

		if (this->codeEditorForm->current->GetCurrent() < this->codeEditorForm->current->GetLength()) {
			this->codeEditorForm->current->Previous();
		}
	}
	else {
		memoCurrent = this->codeEditorForm->memo->GetCurrent();
		previous = this->codeEditorForm->current;
		ret = this->codeEditorForm->memo->Previous();

		if (ret != memoCurrent) {
			this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(ret);
			lineLength = this->codeEditorForm->current->GetLength(); //로직추가 else후 current의 Length와 if후 current의 Length는 사용량이 다름 
			cloneLength = previous->GetLength();

			while (i < cloneLength) {
				letter = previous->GetAt(i);
				this->codeEditorForm->current->Add(letter->Clone());
				i++;
			}

			this->codeEditorForm->memo->Remove(ret + 1);
			this->codeEditorForm->current->Move(lineLength); // 로직추가 백스페이스로 현재줄을 지울 시 이전줄의 사용량으로 캐럿 이동
		}
	}
}