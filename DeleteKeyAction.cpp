//DeleteKeyAction.cpp


#include "DeleteKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"

DeleteKeyAction::DeleteKeyAction(CodeEditorForm *codeEditorForm) :KeyAction(codeEditorForm) {
}

DeleteKeyAction::~DeleteKeyAction() {
}

void DeleteKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

	Glyph *next;

	Glyph *letter;
	Long lineCurrent;
	Long lineLength;
	Long memoCurrent;
	Long memoLength;
	Long nextLength;
	Long i = 0;
	Long lineCurrentx;// REMOVE  수정후 삭제
	Long lineLengthx;// REMOVE  수정후 삭제

	lineCurrent = this->codeEditorForm->current->GetCurrent();
	lineLength = this->codeEditorForm->current->GetLength();

	if(lineCurrent < lineLength) {
		this->codeEditorForm->current->Remove(lineCurrent);
		lineCurrentx = this->codeEditorForm->current->GetCurrent();// REMOVE  수정후 삭제
		lineLengthx = this->codeEditorForm->current->GetLength();// REMOVE  수정후 삭제
		
		if (lineCurrent == lineLength -1 && lineCurrentx == lineLengthx - 1) {// REMOVE  수정후 삭제
			this->codeEditorForm->current->Last();
		}
	}
	else {
		memoCurrent = this->codeEditorForm->memo->GetCurrent();
		memoLength = this->codeEditorForm->memo->GetLength();
		
		if (memoCurrent < memoLength-1) {
			next = this->codeEditorForm->memo->GetAt(memoCurrent + 1);
			nextLength = next->GetLength();
			
			while (i < nextLength) {
				letter = next->GetAt(i);
				this->codeEditorForm->current->Add(letter->Clone());
				i++;
			}
			this->codeEditorForm->memo->Remove(memoCurrent + 1);
			this->codeEditorForm->current->Move(lineCurrent);
		}
	}
	this->codeEditorForm->Invalidate();

#if 0
	Glyph *letter;
	Long lineCurrent;
	Long lineLength;
	Long memoCurrent;
	Long memoLength;
	Long i = 0;
	Long lineCurrentx;
	Long lineLengthx;

	lineCurrent = this->codeEditorForm->current->GetCurrent();
	lineLength = this->codeEditorForm->current->GetLength();

	if (lineCurrent < lineLength) {
		this->codeEditorForm->current->Remove(lineCurrent);
		lineCurrentx = this->codeEditorForm->current->GetCurrent();
		lineLengthx = this->codeEditorForm->current->GetLength();

		if (lineCurrent == lineLength - 1 && lineCurrentx == lineLengthx - 1) {
			this->codeEditorForm->current->Last();
		}
	}
	else {
		memoCurrent = this->codeEditorForm->memo->GetCurrent();
		memoLength = this->codeEditorForm->memo->GetLength();

		if (memoCurrent < memoLength - 1) {
			this->codeEditorForm->current = this->codeEditorForm->memo->GetAt(memoCurrent + 1);

			while (i < this->codeEditorForm->current->GetLength()) {
				letter = this->codeEditorForm->current->GetAt(i);
				this->codeEditorForm->current->Add(letter->Clone());
				i++;
			}
			this->codeEditorForm->memo->Remove(memoCurrent + 1);
			this->codeEditorForm->current->Move(lineCurrent);
		}
	}
	this->codeEditorForm->Invalidate();
#endif
}