#include "FontCommand.h"
#include <afxdlgs.h>
#include "CodeEditorForm.h"
#include "FontMatrix.h"

FontCommand::FontCommand(CodeEditorForm* codeEditorForm) :Command(codeEditorForm){
	this->codeEditorForm = codeEditorForm;
}

FontCommand::~FontCommand() {

}

void FontCommand::Execute() {
	CFontDialog fontdlg;
	LOGFONT logfont;
	//CClientDC cdc(this->codeEditorForm);
	HDC dc;

	dc = GetDC(this->codeEditorForm->m_hWnd);
	if (fontdlg.DoModal() == IDOK) {

		if (this->codeEditorForm->oldFont != NULL) {
			//cdc.SelectObject(this->codeEditorForm->oldFont);
			SelectObject(dc, this->codeEditorForm->oldFont->GetSafeHandle());
			this->codeEditorForm->font.DeleteObject();
		}
		ReleaseDC(this->codeEditorForm->m_hWnd, dc);
		fontdlg.GetCurrentFont(&logfont);
		this->codeEditorForm->font.CreateFontIndirect(&logfont);
	
	}

	this->codeEditorForm->Invalidate();
}
