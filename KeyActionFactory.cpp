//KeyActionFactory.cpp

/*
파일명 : KeyActionFactory.cpp
작성일자 : 2019년 04월 15일
작성자 : 김영재
기능 : 키액션팩토리
수정 :
*/

#include "KeyActionFactory.h"
#include "LeftKeyAction.h"
#include "RightKeyAction.h"
#include "CtrlLeftKeyAction.h"
#include "CtrlRightKeyAction.h"
#include "HomeKeyAction.h"
#include "EndKeyAction.h"
#include "CtrlHomeKeyAction.h"
#include "CtrlEndKeyAction.h"
#include "ShiftRightKeyAction.h"
#include "ShiftLeftKeyAction.h"
#include "ShiftUpKeyAction.h"
#include "ShiftDownKeyAction.h"
#include "UpKeyAction.h"
#include "DownKeyAction.h"
#include "BackspaceKeyAction.h"
#include "DeleteKeyAction.h"
#include "EnterKeyAction.h"

KeyActionFactory::KeyActionFactory(CodeEditorForm* codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}

KeyActionFactory::~KeyActionFactory() {
}

KeyAction * KeyActionFactory::Make(UINT nChar) {
	KeyAction *keyAction = NULL;


	if ((GetKeyState(VK_CONTROL) < 0) && nChar == VK_LEFT) {
		keyAction = new CtrlLeftKeyAction(this->codeEditorForm);
	}
	else if ((GetKeyState(VK_CONTROL) < 0) && nChar == VK_RIGHT) {
		keyAction = new CtrlRightKeyAction(this->codeEditorForm);
	}
	else if ((GetKeyState(VK_CONTROL) < 0) && nChar == VK_HOME) {
		keyAction = new CtrlHomeKeyAction(this->codeEditorForm);
	}
	else if ((GetKeyState(VK_CONTROL) < 0) && nChar == VK_END) {
		keyAction = new CtrlEndKeyAction(this->codeEditorForm);
	}
	else if ((GetKeyState(VK_SHIFT) < 0) && nChar == VK_RIGHT) {
		keyAction = new ShiftRightKeyAction(this->codeEditorForm);
	}
	else if ((GetKeyState(VK_SHIFT) < 0) && nChar == VK_LEFT) {
		keyAction = new ShiftLeftKeyAction(this->codeEditorForm);
	}
	else if ((GetKeyState(VK_SHIFT) < 0) && nChar == VK_UP) {
		keyAction = new ShiftUpKeyAction(this->codeEditorForm);
	}
	else if ((GetKeyState(VK_SHIFT) < 0) && nChar == VK_DOWN) {
		keyAction = new ShiftDownKeyAction(this->codeEditorForm);
	}
	else if (nChar == VK_LEFT) {
		keyAction = new LeftKeyAction(this->codeEditorForm);
	}
	else if (nChar == VK_RIGHT) {
		keyAction = new RightKeyAction(this->codeEditorForm);
	}
	else if (nChar == VK_UP) {
		keyAction = new UpKeyAction(this->codeEditorForm);
	}
	else if (nChar == VK_DOWN) {
		keyAction = new DownKeyAction(this->codeEditorForm);
	}
	else if (nChar == VK_HOME) {
		keyAction = new HomeKeyAction(this->codeEditorForm);
	}
	else if (nChar == VK_END){
		keyAction = new EndKeyAction(this->codeEditorForm);
	}
	else if (nChar == VK_BACK) {
		keyAction = new BackspaceKeyAction(this->codeEditorForm);
	}
	else if (nChar == VK_DELETE) {
		keyAction = new DeleteKeyAction(this->codeEditorForm);
	}
	else if (nChar == VK_RETURN) {
		keyAction = new EnterKeyAction(this->codeEditorForm);
	}
	
	return keyAction;
}