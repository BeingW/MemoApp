#include "RegionController.h"
#include "CodeEditorForm.h"
#include "CaretCoordinator.h"
#include "FontMatrix.h"
#include "Glyph.h"

RegionController::RegionController()
{
}

RegionController::RegionController(CodeEditorForm* codeEditorForm)
{
	this->codeEditorForm = codeEditorForm;

	this->standardX = 0;
	this->secondStandardX = 0;
	
	this->standardY = 0;
	this->secondStandardY = 0;

	CBrush brush;
	brush.CreateSolidBrush(RGB(37, 111, 253));
	this->backgroundColor = RGB(37, 111, 253);
	this->letterColor = RGB(255, 255, 255);
	this->brush = (HBRUSH)brush.GetSafeHandle();
	this->isBeing = FALSE;

}

RegionController::~RegionController()
{
}

HRGN RegionController::MakeRegion(Glyph* previousLine, Glyph* nextLine, Long previousMemoNumber, Long nextMemoNumber)
{
	CaretCoordinator coordinator;
	Long height;
	Long i = 0;
	Glyph* line;
	HRGN hRgn;
	Long shortestX, previousX, nextX, longestX;
	Long shortestY, previousY, nextY, longestY;
	RECT clientRect;

	if (!this->isBeing){
		this->printRgn.CreateRectRgn(0, 0, 0, 0);
		this->firstRgn.CreateRectRgn(0, 0, 0, 0);
		this->secondRgn.CreateRectRgn(0, 0, 0, 0);
		this->thirdRgn.CreateRectRgn(0, 0, 0, 0);
	}

	GetClientRect(this->codeEditorForm->GetSafeHwnd(), &clientRect);
	
	this->standardX = coordinator.GetXPos(this->codeEditorForm->fontMatrix, previousLine);
	this->secondStandardX = coordinator.GetXPos(this->codeEditorForm->fontMatrix, nextLine);

	this->standardY = coordinator.GetYPos(this->codeEditorForm->fontMatrix, previousMemoNumber);
	this->secondStandardY = coordinator.GetYPos(this->codeEditorForm->fontMatrix, nextMemoNumber);

	height = this->codeEditorForm->fontMatrix->GetHeight();

#if 0
	i = previousMemoNumber;
	while (i <= nextMemoNumber){
		line = this->codeEditorForm->memo->GetAt(i);
		this->contents += line->GetContent();
		i++;
	}
#endif

	//1.坷弗率 府哩积己
	if (standardX < secondStandardX && standardY-secondStandardY == 0) {
		previousX = coordinator.GetXPos(this->codeEditorForm->fontMatrix, previousLine);
		nextX = coordinator.GetXPos(this->codeEditorForm->fontMatrix, nextLine);

		previousY = coordinator.GetYPos(this->codeEditorForm->fontMatrix, previousMemoNumber);
		nextY = coordinator.GetYPos(this->codeEditorForm->fontMatrix, nextMemoNumber);
		nextY += height;

		CRgn zeroRgn;
		zeroRgn.CreateRectRgn(0, 0, 0, 0);

		if (zeroRgn.EqualRgn(&printRgn)){
			this->firstRgn.SetRectRgn(previousX, previousY, nextX, nextY);
		}
		else {
			this->secondRgn.SetRectRgn(previousX, previousY, nextX, nextY);
			this->firstRgn.CombineRgn(&firstRgn, &secondRgn, RGN_OR);
		}

		this->printRgn.CopyRgn(&this->firstRgn);
		this->isBeing = TRUE;
	}
	//2.哭率 府哩积己()
	else if (standardX != secondStandardX && secondStandardY - standardY == 0) {
		previousX = coordinator.GetXPos(this->codeEditorForm->fontMatrix, previousLine);
		nextX = coordinator.GetXPos(this->codeEditorForm->fontMatrix, nextLine);

		previousY = coordinator.GetYPos(this->codeEditorForm->fontMatrix, previousMemoNumber);
		previousY += height;
		nextY = coordinator.GetYPos(this->codeEditorForm->fontMatrix, nextMemoNumber);
		
		CRgn zeroRgn;
		zeroRgn.CreateRectRgn(0, 0, 0, 0);

		if (zeroRgn.EqualRgn(&printRgn)) {
			this->firstRgn.SetRectRgn(nextX, nextY, previousX, previousY);
		}
		else {
			this->secondRgn.SetRectRgn(nextX, nextY, previousX, previousY);
			this->firstRgn.CombineRgn(&firstRgn, &secondRgn, RGN_OR);
		}

		this->printRgn.CopyRgn(&this->firstRgn);
		this->isBeing = TRUE;
	}
	//3.酒贰率 府哩积己(2临)
	else if (secondStandardY-standardY == height) {
		shortestX = coordinator.GetFirstXPos();
		longestX = clientRect.bottom;
		previousX = coordinator.GetXPos(this->codeEditorForm->fontMatrix, previousLine);
		nextX = coordinator.GetXPos(this->codeEditorForm->fontMatrix, nextLine);

		shortestY = coordinator.GetYPos(this->codeEditorForm->fontMatrix, previousMemoNumber);
		longestY = coordinator.GetYPos(this->codeEditorForm->fontMatrix, nextMemoNumber);
		longestY += height;
		previousY = coordinator.GetYPos(this->codeEditorForm->fontMatrix, previousMemoNumber);
		previousY += height;
		nextY = coordinator.GetYPos(this->codeEditorForm->fontMatrix, nextMemoNumber);

		CRgn zeroRgn;
		zeroRgn.CreateRectRgn(0, 0, 0, 0);

		if (zeroRgn.EqualRgn(&printRgn)) {
			this->firstRgn.SetRectRgn(shortestX, shortestY, longestX, longestY);
			this->secondRgn.SetRectRgn(shortestX, shortestY, previousX, previousY);
			this->thirdRgn.SetRectRgn(nextX, nextY, longestX, longestY);

			this->firstRgn.CombineRgn(&this->firstRgn, &this->secondRgn, RGN_XOR);
			this->firstRgn.CombineRgn(&this->firstRgn, &this->thirdRgn, RGN_XOR);
		}
		else {
			this->firstRgn.SetRectRgn(shortestX, shortestY, longestX, longestY);
			this->secondRgn.SetRectRgn(shortestX, shortestY, previousX, previousY);
			this->thirdRgn.SetRectRgn(nextX, nextY, longestX, longestY);

			this->firstRgn.CombineRgn(&this->firstRgn, &this->secondRgn, RGN_XOR);
			this->firstRgn.CombineRgn(&this->firstRgn, &this->thirdRgn, RGN_XOR);
		}
		this->printRgn.CombineRgn(&this->printRgn, &this->firstRgn, RGN_OR);
		
		this->isBeing = TRUE;
	}
	//5.困率 府哩积己(2临)
	else if (standardY - secondStandardY == height) {
		shortestX = coordinator.GetFirstXPos();
		longestX = clientRect.bottom;
		previousX = coordinator.GetXPos(this->codeEditorForm->fontMatrix, previousLine);
		nextX = coordinator.GetXPos(this->codeEditorForm->fontMatrix, nextLine);

		shortestY = coordinator.GetYPos(this->codeEditorForm->fontMatrix, nextMemoNumber);
		longestY = coordinator.GetYPos(this->codeEditorForm->fontMatrix, previousMemoNumber);
		longestY += height;
		previousY = coordinator.GetYPos(this->codeEditorForm->fontMatrix, previousMemoNumber);
		nextY = coordinator.GetYPos(this->codeEditorForm->fontMatrix, nextMemoNumber);
		nextY += height;

		CRgn zeroRgn;
		zeroRgn.CreateRectRgn(0, 0, 0, 0);

		if (zeroRgn.EqualRgn(&printRgn)) {
			this->firstRgn.SetRectRgn(shortestX, shortestY, longestX, longestY);
			this->secondRgn.SetRectRgn(shortestX, shortestY, nextX, nextY);
			this->thirdRgn.SetRectRgn(previousX, previousY, longestX, longestY);

			this->firstRgn.CombineRgn(&this->firstRgn, &this->secondRgn, RGN_XOR);
			this->firstRgn.CombineRgn(&this->firstRgn, &this->thirdRgn, RGN_XOR);
		}
		else {
			this->firstRgn.SetRectRgn(shortestX, shortestY, longestX, longestY);
			this->secondRgn.SetRectRgn(shortestX, shortestY, previousX, previousY);
			this->thirdRgn.SetRectRgn(previousX, previousY, longestX, longestY);

			this->firstRgn.CombineRgn(&this->firstRgn, &this->secondRgn, RGN_XOR);
			this->firstRgn.CombineRgn(&this->firstRgn, &this->thirdRgn, RGN_XOR);
		}
		this->printRgn.CombineRgn(&this->printRgn, &this->firstRgn, RGN_OR);

		this->isBeing = TRUE;
	}

	//Delete 窍搁 府哩捞 吝酶登瘤 臼澜.
#if 0
	DeleteObject(firstRgn.GetSafeHandle());
	DeleteObject(secondRgn.GetSafeHandle());
	DeleteObject(thirdRgn.GetSafeHandle());
#endif
	
	hRgn = (HRGN)this->printRgn.GetSafeHandle();

	return hRgn;
}

void RegionController::DrawRegion(){
	HDC hdc;
	CDC cdc;
	CString rgnText;
	hdc = GetDC(this->codeEditorForm->m_hWnd);
	cdc.Attach(hdc);
	
	cdc.InvertRgn(&this->printRgn);

	cdc.Detach();

	ReleaseDC(this->codeEditorForm->m_hWnd, hdc);
}

void RegionController::CleanRegion(){
	if (isBeing == TRUE){
//#if 0
		firstRgn.DeleteObject();
		secondRgn.DeleteObject();
		thirdRgn.DeleteObject();
		printRgn.DeleteObject();
//#endif

#if 0
		firstRgn.CreateRectRgn(0, 0, 0, 0);
		secondRgn.CreateRectRgn(0, 0, 0, 0);
		thirdRgn.CreateRectRgn(0, 0, 0, 0);
		printRgn.CreateRectRgn(0, 0, 0, 0);
#endif 
		this->isBeing = FALSE;
	}
	
}
