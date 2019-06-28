//FontMatrix.cpp
/*파일명: FontMatrix.cpp
	작성일자 : 2019년 03월 29일
	작성자 : 김영재
	기능 : 폰트의 너비와 높이를 구한다.
	수정 :
	*/

#include "FontMatrix.h"
#include <string>
using namespace std;

/*
함수명 : FontMatrix
기능 : 매개변수 생성자
수정 : 폭 연산 수정
*/
FontMatrix::FontMatrix(CDC *dc) {
	char code[3] = { 0, };
	int i;
	CSize sz;

	for (i = 1; i < 129; i++) {
		code[0] = i;
		sz = dc->GetTextExtent(code);
		this->widths[i] = (BYTE)sz.cx;
	}

	this->widths[0] = 0;

	strcpy(code, "한");
	sz = dc->GetTextExtent(code);
	this->widths[129] = (BYTE)sz.cx;
	this->height = sz.cy;

}

/*
함수명 : FontMatrix
기능 : 복사 생성자
*/
FontMatrix::FontMatrix(const FontMatrix& source) {
	Long i;
	
	for (i = 0; i < 129; i++) {
		this->widths[i] = source.widths[i];
	}
	this->height = source.height;
}

/*
함수명 : ~FontMatrix
기능 : 소멸자
*/
FontMatrix::~FontMatrix() {
}

/*
함수명 : GetSingleByteWidth
기능 : widths에서 width를 가져온다
*/
Long FontMatrix::GetSingleByteWidth(Long code) {
	return this->widths[code];
}

/*
함수명 : GetDoubleByteWidth
기능 : widths에서 width를 가져온다
*/
Long FontMatrix::GetDoubleByteWidth() {
	return this->widths[129];
}

/*
함수명 : GetLetterHeight
기능 : height를 가져온다
*/
Long FontMatrix::GetLetterHeight() {
	return this->height;
}

/*
함수명 : operator=
기능 : 치환 연산자
*/
FontMatrix& FontMatrix::operator=(const FontMatrix& source) {
	Long i;
	
	for (i = 0; i < 129; i++) {
		this->widths[i] = source.widths[i];
	}
	this->height = source.height;

	return *this;
}