#include "SaveCommand.h"
#include <afxdlgs.h>
#include <string>
#include "CodeEditorForm.h"
#include "FontMatrix.h"
#include "File.h"
#include "Glyph.h"

SaveCommand::SaveCommand(CodeEditorForm* codeEditorForm): Command(codeEditorForm){
}

SaveCommand::~SaveCommand() {

}

void SaveCommand::Execute() {
	string fileName;
	string pathName;
	string contents;

	pathName = this->codeEditorForm->file->GetFileName();

	if (pathName == "") {
		this->codeEditorForm->file->OpenDialog(FALSE);
		pathName = this->codeEditorForm->file->GetPathName();
		fileName = this->codeEditorForm->file->GetFileName();
		this->codeEditorForm->SetWindowText(fileName.c_str());
	}

	contents = this->codeEditorForm->memo->GetContents();
	this->codeEditorForm->file->Save(contents, pathName);
}