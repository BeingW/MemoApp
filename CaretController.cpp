//CaretController.cpp
/*
파일명 : CaretController.cpp
작성일자 : 2019년 03월 29일
작성자 : 진민국
기능 : 캐럿관련 클래스들을 관리하는 클래스
수정 : 20190410 GetXPosCaret 연산추가
*/

#include "CaretController.h"
#include "CodeEditorForm.h"
#include "FontMatrix.h"
#include "Caret.h"
#include "CaretCoordinator.h"
#include "Memo.h"

/*
함수명 : CaretController
기능 : 디폴트생성자
*/
CaretController::CaretController() {
	this->codeEditorForm = 0;
	this->caret = 0;
	this->caretCoordinator = 0;
	this->line =0;
	this->row = 0;
}

/*
함수명 : CaretController
기능 : 매개변수를 가지는 생성자
*/
CaretController::CaretController(CodeEditorForm *codeEditorForm, Glyph *line, Long row) {
	this->codeEditorForm = codeEditorForm;
	this->caret = new Caret(this->codeEditorForm);
	this->caretCoordinator = new CaretCoordinator;
	this->line = line;
	this->row = row;
	this->codeEditorForm->Add(this);
}

/*
함수명 : CaretController
기능 : 복사생성자
*/
CaretController::CaretController(const CaretController& source) {
	this->codeEditorForm = source.codeEditorForm;
	this->caretCoordinator = source.caretCoordinator;
	this->caret = source.caret;
	this->line = source.line;
	this->row = source.row;
}

/*
함수명 : ~CaretController
기능 : 소멸자
수정: 20190407 caret,caretCoordinator 동적 할당해제
*/
CaretController::~CaretController() {
	
	delete caret;
	delete caretCoordinator;
}

/*
함수명 : MakeCaret
기능 : 캐럿을 만든다.
*/
void CaretController::MakeCaret() {
	Long width=2;
	Long height;

	
	if (this->codeEditorForm->GetIsComposing() == TRUE) {
		width -= this->codeEditorForm->GetFontMatrix()->GetDoubleByteWidth();
	}
	height = this->codeEditorForm->GetFontMatrix()->GetHeight();
	
	this->caret->Make(width, height);
}

/*
함수명: MoveCaret
기능 : 캐럿을 이동한다.
수정: 20190407 매게변수 대신, 데이터멤버를 사용하도록 변경
*/
void CaretController::MoveCaret() {
	Long x;
	Long y;

	this->caretCoordinator->MakePosition(this->codeEditorForm->GetFontMatrix(), this->line, this->row);
	x = this->caretCoordinator->GetX();
	y = this->caretCoordinator->GetY();
	this->caret->Move(x, y);
}

/*
함수명: ShowCaret
기능 : 캐럿을 보여주거나 숨긴다.
*/
void CaretController::ShowCaret(bool isShow) {
	this->caret->Show(isShow);
}

/*
함수명: DeleteCaret
기능 : 캐럿을 삭제한다.
*/
void CaretController::DeleteCaret() {
	
	this->caret->Delete();
}

/*
함수명: GetXPosCaret
기능 : 현재 위치의 폭을 구한다
*/
Long CaretController::GetXPosCaret() {
	Long xPos;
	
	xPos = this->caretCoordinator->GetXPos(this->codeEditorForm->GetFontMatrix(), this->line);

	return xPos;
}

/*
함수명: Update
기능 : line과 column을 업데이트 한다.
수정 : MakeCaret, MoveCaret, ShowCaret 추가
*/
void CaretController::Update() {
	this->row = this->codeEditorForm->memo->GetCurrent();
	this->line = this->codeEditorForm->memo->GetAt(this->row);

	this->MakeCaret();
	this->MoveCaret();
	this->ShowCaret(TRUE);
}

/*
함수명: operator=
기능 : 치환 연산자
*/
CaretController& CaretController::operator=(const CaretController& source) {
	this->codeEditorForm = source.codeEditorForm;
	this->caretCoordinator = source.caretCoordinator;
	this->caret = source.caret;
	this->line = source.line;
	this->row = source.row;

	return *this;
}