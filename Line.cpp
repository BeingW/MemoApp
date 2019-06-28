/*
파일명 : Line.h
//Line.cpp
작성일자 : 2019년 03월 27일
작성자 : 허수진
기능 : 생성자, 복사생성자, 소멸자, , 문자열 만들기, 연산자= 선언
수정 : 1900402 GetContents 정의(Tab처리)
*/
#include "Line.h"
#include "iterator.h"


/*
함수명 : Line
기능 : 생성자
*/
Line::Line(Long capacity) :Composite(capacity) {
}

/*
함수명 : Line
기능 : 복사 생성자
*/
Line::Line(const Line& source) : Composite(source) {
	}

/*
함수명 : ~Line
기능 : 소멸자
*/
Line::~Line() {
}


/*
함수명 : Add
기능 : Add 오버라이드
*/
Long Line::Add(Glyph* glyph) {
	if (this->capacity > this->length) {
		this->current = glyphs.Store(this->length, glyph) + 1;
	}
	else {
		this->current = glyphs.AppendFromRear(glyph) + 1;
		this->capacity++;
	}
	this->length++;
	return this->current;
}

Long Line::Add(Glyph * glyph, Long index) {
	Composite::Add(glyph, index);
	
	this->current++;

	return this->current;
}
#if 0
Long Line::Remove(Long index) {

	Long changedIndex = index - 1;

	if (this->glyphs[changedIndex] != 0) {
		delete this->glyphs[changedIndex];
	}

	this->glyphs.Delete(changedIndex);
	this->capacity--;
	this->length--;

	if (this->length > 0 && this->current > this->length - 1) {
		this->current--; //--로 변경
	}
	//추가
	else if (this->length <= 0) {
		this->current = 0;
	}

	return -1;
}
#endif
/*
함수명 : LeftWord
기능 : 왼쪽으로 한 단어 이동
*/
Long Line::LeftWord() {
	Glyph *letter;
	string contents;

	if (this->current == 0) {
		this->current++;
	}

	letter = this->glyphs.GetAt(this->current - 1);
	contents = letter->GetContents();

	while (this->current > 0 && contents[0] == ' ') {
		this->Previous();
		if (this->current > 0) {
			letter = this->glyphs.GetAt(this->current - 1);
			contents = letter->GetContents();
		}
	}
	while (this->current > 0 && contents[0] != ' ') {
		this->Previous();
		if (this->current > 0) {
			letter = this->glyphs.GetAt(this->current - 1);
			contents = letter->GetContents();
		}
	}

	return this->current;
}

/*
함수명 : RightWord
기능 : 오른쪽으로 한 단어 이동
*/
Long Line::RightWord() {
	Glyph *letter;
	string contents;

	if (this->current < this->length)
	{
		letter = this->glyphs.GetAt(this->current);
		contents = letter->GetContents();
	}

	while (this->current < this->length && contents[0] != ' ') {
		this->Next();
		if (this->current < this->length)
		{
			letter = this->glyphs.GetAt(this->current);
			contents = letter->GetContents();
		}
	}

	while (this->current < this->length && contents[0] == ' ') {
		this->Next();
		letter = this->glyphs.GetAt(this->current);
		if (this->current < this->length)
		{
			letter = this->glyphs.GetAt(this->current);
			contents = letter->GetContents();
		}
	}

	return this->current;
}

/*
함수명 : Clone
기능 : 복사한다
*/
Glyph* Line::Clone() {
	return new Line(*this);
}

/*
함수명 : Getcontent
기능 : 글자를 가져온다.
*/
string Line::GetContent() {
	Glyph *letter;

	letter = this->GetAt(this->current - 1);
	
	return letter->GetContents();
}

/*
함수명 : Getcontents
기능 : 문자열을 만든다
*/
string Line::GetContents() {
	string text = "";
	string contents;

	Iterator<Glyph*>*iterator = this->CreateItorator();

	for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
		
		contents = iterator->CurrentItem()->GetContents();
		
		text += contents;
	}
	return text;
}


/*
함수명 : operator=
기능 : 치환 연산자
*/
Line& Line::operator=(const Line& source) {
	Composite::operator=(source);
	return *this;
}