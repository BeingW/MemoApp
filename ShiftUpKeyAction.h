//ShiftUpKeyAction.h
#ifndef _SHIFTUPKEYACTION_H
#define _SHIFTUPKEYACTION_H
#include "KeyAction.h"

typedef signed long int Long;

class CodeEditForm;
class ShiftUpKeyAction : public KeyAction {
public:
	ShiftUpKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~ShiftUpKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif //_SHIFTUPKEYACTION_H