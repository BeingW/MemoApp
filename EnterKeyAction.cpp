#include "EnterKeyAction.h"
#include "CodeEditorForm.h"
#include "Glyph.h"
#include "Line.h"

EnterKeyAction::EnterKeyAction(CodeEditorForm * codeEditorForm) :KeyAction(codeEditorForm) {
}

EnterKeyAction::~EnterKeyAction() {
}

void EnterKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph *line;
	Glyph *letter;
	//Long memoCurrent;
	//Long memoLength;
	Long lineCurrent;
	Long lineLength;
	Long i;

		line = new Line;
		//memoCurrent = this->codeEditorForm->memo->GetCurrent();
		//memoLength = this->codeEditorForm->memo->GetLength();
		lineCurrent = this->codeEditorForm->current->GetCurrent();
		lineLength = this->codeEditorForm->current->GetLength();

		//현재 글자의 위치가 끝이라면 개행 
		if (lineCurrent == lineLength) {
			this->codeEditorForm->memo->Add(line);
		}
		else //끝이 아니라면 현재 글자이후를 개행
		{
			i = lineCurrent;

			while (i < lineLength) {
				letter = this->codeEditorForm->current->GetAt(i);
				line->Add(letter->Clone());
				i++;
			}

			i = lineLength;

			while (i > lineCurrent) {
				this->codeEditorForm->current->Remove(lineCurrent);
				i--;
			}
			this->codeEditorForm->memo->Add(line, this->codeEditorForm->memo->GetCurrent() + 1);
		}
		this->codeEditorForm->current = line;
		this->codeEditorForm->current->First();
}