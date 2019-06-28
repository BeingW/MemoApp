#pragma once
//ShiftDownKeyAction.h
#ifndef _SHIFTDOWNKEYACTION_H
#define _SHIFTDOWNKEYACTION_H
#include "KeyAction.h"

typedef signed long int Long;

class CodiEditorForm;
class ShiftDownKeyAction : public KeyAction {
public:
	ShiftDownKeyAction(CodeEditorForm *codeEditForm);
	virtual ~ShiftDownKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif //_SHIFTDOWNKEYACTION_H
