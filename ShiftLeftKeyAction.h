/*
파일명 : ShiftLeftKeyAction.h
작성일자 : 2019년 05월 14일
기능 : ShiftLeftKeyAction 정의 선언
*/
//ShiftLeftKeyAction.h
#ifndef _SHIFTLEFTKEYACTION_H
#define _SHIFTLEFTKEYACTION_H
#include "KeyAction.h"
#include "RegionController.h"

class CodeEditorForm;

class ShiftLeftKeyAction :public KeyAction {
public:
	ShiftLeftKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~ShiftLeftKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

private:
	RegionController *regionController;
};
#endif // !_RIGHTKEYACTION_H
