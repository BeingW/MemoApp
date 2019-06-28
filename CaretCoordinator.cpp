//CaretCoordinator.cpp
/*
파일명 : CaretCoordinator.cpp
작성일자 : 2019년 03월 29일
작성자 : 김영재
기능 : 캐럿의 위치지정
수정 :
*/

#include "CaretCoordinator.h"
#include "Glyph.h"
#include "FontMatrix.h"
#include "SingleByteLetter.h"
#include "DoubleByteLetter.h"
#include <string>
using namespace std;

/*
함수명: CaretCoordinator
기능: 생성자
*/
CaretCoordinator::CaretCoordinator()
{
	this->x = 0;
	this->y = 0;
}

/*
함수명: CaretCoordinator
기능: 복사생성자
*/
CaretCoordinator::CaretCoordinator(const CaretCoordinator& source) {
	this->x = source.x;
	this->y = source.y;
}

/*
함수명: ~CaretCoordinator
기능: 소멸자
*/
CaretCoordinator::~CaretCoordinator() {
}

/*
함수명: MakePosition
기능: 위치를 만든다ㅣ
수정: 20190407 x좌표 구하는 반복문 수정
*/
void CaretCoordinator::MakePosition(FontMatrix *fontMatrix, Glyph *line, Long row) {

	this->GetXPos(fontMatrix, line);
	this->GetYPos(fontMatrix, row);
}


/*
함수명: GetFirstXPos
기능: 첫번째 위치의 X 를 구한다.
수정:
*/
Long CaretCoordinator::GetFirstXPos()
{
	this->x = 0;

	return x;
}


/*
함수명: GetXPos
기능: 현재 위치의 폭을 구한다
수정: 
*/
Long CaretCoordinator::GetXPos(FontMatrix *fontMatrix, Glyph *line) {
	Long i = 0;
	Glyph *letter;
	string content;
	Long code;

	this->x = 0;
	while (i < line->GetCurrent()) {
		letter = line->GetAt(i);
		if (dynamic_cast<SingleByteLetter*>(letter)) {
			content = letter->GetContents();
			code = content.at(0);
			this->x += fontMatrix->GetSingleByteWidth(code);
		}
		else if (dynamic_cast<DoubleByteLetter*>(letter)) {
			this->x += fontMatrix->GetDoubleByteWidth();
		}
		i++;
	}

	return this->x;
}

/*
함수명: GetLastXPos
기능: 마지막 위치의 X를 구한다.
수정:
*/
Long CaretCoordinator::GetLastXPos(FontMatrix * fontMatrix, Glyph * line)
{
	Long i = 0;
	Glyph *letter;
	string content;
	Long code;

	this->x = 0;
	while (i < line->GetLength()) {
		letter = line->GetAt(i);
		if (dynamic_cast<SingleByteLetter*>(letter)) {
			content = letter->GetContents();
			code = content.at(0);
			this->x += fontMatrix->GetSingleByteWidth(code);
		}
		else if (dynamic_cast<DoubleByteLetter*>(letter)) {
			this->x += fontMatrix->GetDoubleByteWidth();
		}
		i++;
	}

	return this->x;
}

Long CaretCoordinator::GetYPos(FontMatrix * fontMatrix, Long row) {

	this->y = row * (fontMatrix->GetHeight());

	return this->y;
}

/*
함수명: operator=
기능: 치환연산자
*/
CaretCoordinator& CaretCoordinator::operator=(const CaretCoordinator& source) {
	this->x = source.x;
	this->y = source.y;
	
	return *this;
}