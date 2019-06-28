/*
파일명 : RightKeyAction.h
작성일자 : 2019년 05월 02일
작성자 : 허수진
기능 : ShiftRightKeyAction 정의 선언
*/
//ShiftRightKeyAction.h
#ifndef _SHIFTRIGHTKEYACTION_H
#define _SHIFTRIGHTKEYACTION_H
#include "KeyAction.h"
#include "RegionController.h"

class CodeEditorForm;

class ShiftRightKeyAction :public KeyAction {
public:
	ShiftRightKeyAction(CodeEditorForm *codeEditorForm);
	virtual ~ShiftRightKeyAction();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

private:
	RegionController *regionController;
};
#endif // !_RIGHTKEYACTION_H