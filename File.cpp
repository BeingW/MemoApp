/*
파일명 : File.cpp
작성일자 : 2019년 04월 02일
작성자 : 김영재
기능 : 파일 클래스 (저장기능)
수정 :20190403 OpenDialog 기능 구현
*/

//File.cpp

#include "File.h"
#include <iostream>
#include <fstream>
#include <afxdlgs.h>


/*
함수명: File
기능: 디폴트 생성자
수정 : 20190404 fileName 수정
*/
File::File() {
	this->pathName = "";
	this->fileName = "*.txt";
}

/*
함수명: File
기능: 매개변수 생성자
*/
File::File(string pathName, string fileName) {
	this->pathName = pathName;
	this->fileName = fileName;
}

/*
함수명: File
기능: 복사 생성자
*/
File::File(const File& source) {
	this->pathName = source.pathName;
	this->fileName = source.fileName;
}

/*
함수명: ~File
기능: 소멸자
*/
File::~File() {
}

/*
함수명: Save
기능: 저장하다
*/
void File::Save(string contents, string pathName) {
	fstream fs;

	fs.open(pathName, ios::out);

	if (!fs.bad()) {
		fs << contents;
		fs.flush();
		fs.close();
	}
}

/*
함수명: Load
기능: 불러오다
*/
string File::Load(string pathName) {
	fstream fs;
	string text = "";
	char line[256];

	fs.open(pathName, ios::in);

	if (fs.is_open()) {
		while (fs.getline(line, 256)) {
			text += (line);
			text += '\n';
		}
	}
	fs.close();

	return text;
}

/*
함수명: OpenDialog
기능: Load, Save를 선택적으로 FileName, PathName을 가져온다
수정 : Load, Save 통합 20190404 cFileDialog 3번째 매개변수 수정
*/
void File::OpenDialog(bool isOpen) {
	char szFilter[] = "텍스트 문서(*.txt)|*.txt|모든 파일||";
	CString fileName;

	if (isOpen == TRUE) {
		fileName = "";
	}
	else {
		fileName = this->fileName.c_str();
	}
	
	CFileDialog cFileDialog(isOpen, ".txt", fileName, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter, NULL, 0, NULL);
	if (cFileDialog.DoModal() == IDOK) {
		this->fileName = cFileDialog.GetFileName();
		this->pathName = cFileDialog.GetPathName();
	}
}

/*
함수명: operator=
기능: 치환 연산자
*/
File& File::operator=(const File& source) {
	this->pathName = source.pathName;
	this->fileName = source.fileName;

	return *this;
}