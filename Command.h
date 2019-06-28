//Command.h

#pragma once

#ifndef _COMMAND_H
#define _COMMAND_H
#include <afxwin.h>
#include <string>
#include "CodeEditorForm.h"

using namespace std;

class CodeEditorForm;
class Command {
	public:
		Command(CodeEditorForm* codeEdtiorForm);
		virtual ~Command() = 0;
		virtual void Execute() {};

	protected:
		CodeEditorForm *codeEditorForm;
};

#endif //_COMMAND_H

