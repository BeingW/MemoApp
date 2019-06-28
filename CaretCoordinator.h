//CaretCoordinator.h
/*
파일명 : CaretCoordinator.h
작성일자 : 2019년 03월 29일
작성자 : 김영재
기능 : 캐럿의 위치를 지정한다
수정 : 20190410 GetXPos 연산추가
*/

#ifndef _CARETCOORDINATOR_H
#define _CARETCOORDINATOR_H

typedef signed long int Long;

class Glyph;
class FontMatrix;
class CaretCoordinator {
public:
	CaretCoordinator();
	CaretCoordinator(const CaretCoordinator& source);
	~CaretCoordinator();
	void MakePosition(FontMatrix *fontMatrix, Glyph *line, Long column);
	Long GetFirstXPos();
	Long GetXPos(FontMatrix *fontMatrix, Glyph *line);
	Long GetLastXPos(FontMatrix *fontMatrix, Glyph *line);
	Long GetYPos(FontMatrix *fontMatrix, Long row);
	CaretCoordinator& operator=(const CaretCoordinator& source);
	Long GetX() const;
	Long GetY() const;

private:
	Long x;
	Long y;
};

inline Long CaretCoordinator::GetX()const {
	return this->x;
}

inline Long CaretCoordinator::GetY()const {
	return this->y;
}

#endif //_CARETCOORDINATOR_H