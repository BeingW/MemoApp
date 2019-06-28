#include "CommandFactory.h"
#include "FontCommand.h"
#include "SaveCommand.h"
#include "SaveAsCommand.h"

CommandFactory::CommandFactory(CodeEditorForm * codeEditorForm){
	this->codeEditorForm = codeEditorForm;
}

CommandFactory::~CommandFactory(){
}

Command* CommandFactory::Make(UINT id){
	Command *command = NULL;
	
	if (id == IDM_FORMAT_FONT){
		command = new FontCommand(this->codeEditorForm);
	}
	else if (id == IDM_FILE_SAVE) {
		command = new SaveCommand(this->codeEditorForm);
	}
	else if (id == IDM_FILE_SAVEAS) {
		command = new SaveAsCommand(this->codeEditorForm);
	}
	/*
	
	switch (id)
	{
	case IDM_FORMAT_FONT :
		command = new FontCommand(this->codeEditorForm);
	case IDM_FILE_SAVE :
		command = new SaveCommand(this->codeEditorForm);
	case IDM_FILE_SAVEAS : 
		command = new SaveAsCommand(this->codeEditorForm);
	default:
		break;
	}
	*/
	return command;
}
