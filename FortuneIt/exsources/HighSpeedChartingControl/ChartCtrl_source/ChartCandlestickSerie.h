/*
 *
 *	ChartCandlestickSerie.h
 *
 *	Written by Cédric Moonen (cedric_moonen@hotmail.com)
 *
 *
 *
 *	This code may be used for any non-commercial and commercial purposes in a compiled form.
 *	The code may be redistributed as long as it remains unmodified and providing that the 
 *	author name and this disclaimer remain intact. The sources can be modified WITH the author 
 *	consent only.
 *	
 *	This code is provided without any garanties. I cannot be held responsible for the damage or
 *	the loss of time it causes. Use it at your own risks
 *
 *	An e-mail to notify me that you are using this code is appreciated also.
 *
 *
 */

#pragma once
#include "ChartSerieBase.h"

//! Point structure used as template parameter for candlestick series
struct SChartCandlestickPoint
{
	SChartCandlestickPoint() { }
	
	SChartCandlestickPoint(int IndexVal, COleDateTime TimeVal, double OpenVal,
		double HighVal, double LowVal, double CloseVal) :
		Index(IndexVal), Time(TimeVal), Open(OpenVal), High(HighVal),
		Low(LowVal), Close(CloseVal) { }
	
	//! The X value of the point (usually, a time)
	int Index;
	//! The X value of the point (usually, a time)
	COleDateTime Time;
	//! The open market price
	double Open;
	//! The high market price
	double High;
	//! The low market price
	double Low;
	//! The close market price
	double Close;
	//! The close market price
	double Volume;
	//! The close market price
	double Amount;
	//! The close market price
	double Tor;


	//! Returns the X value of the point
	int GetIndex() const { return Index; }
	//! Returns the X value of the point
	double GetTime() const { return Time; }
	//! Returns the X value of the point
	double GetX() const { return GetIndex(); }
	//! Returns the Y value of the point, which is the average between low and high
	double GetY() const { return (Low+High)/2; }
	//! Returns the minimum X value of the point
	double GetXMin() const { return GetX(); }
	//! Returns the maximum X value of the point
	double GetXMax() const { return GetX(); }
	//! Returns the minimum Y value of the point (the low value)
	double GetYMin() const { return Low; }
	//! Returns the maximum Y value of the point (the high value)
	double GetYMax() const { return High; }

};

//! Specialization of a CChartSerieBase to display a candlestick series.
/**
	Each point in the series has an X value (the time), a high value 
	(the highest market price), a low value (the lowest market price), 
	an open value (the market price at the opening) and a close value 
	(the market price at the closing).
**/
class CChartCandlestickSerie : public CChartSerieBase<SChartCandlestickPoint>
{
public:
	//! Constructor
	CChartCandlestickSerie(CChartCtrl* pParent);
	//! Destructor
	~CChartCandlestickSerie();

	//! Tests if a certain screen point is on the series.
	/**
		@param screenPoint
			The screen point to test
		@param uIndex
			If the point is close to a specific point of the series, its index is stored here.
		@return true if the point is on the series
	**/
	bool IsPointOnSerie(const CPoint& screenPoint, unsigned& uIndex) const;

	//! Adds a new point in the series
	/**
		@param XVal
			The X value of the point (the time)
		@param Low
			The lowest market price 
		@param High
			The highest market price
		@param Open
			The market price at the opening
		@param Close
			The market price at the closing
	**/
	void AddPoint(double Time, double Open, double High, 
				  double Low, double Close);
	//! Sets the width (in pixels) of all candlestick points in the series
	void SetWidth(int Width, bool bRefreshCtrl = true);
	//! Returns the width (in pixels) of a point in the series
	int  GetWidth()		{ return m_iCandlestickWidth; }

	int Cycle() const { return m_Cycle; }
	void Cycle(int val) { m_Cycle = val; }


protected:
	//! Draws the legend icon for the series.
	/**
		@param pDC
			The device context used to draw
		@param rectBitmap
			The rectangle in which to draw the legend icon
	**/
    void DrawLegend(CDC* pDC, const CRect& rectBitmap) const;

	//! Draws the most recent points of the series.
	/**
		This function should only draw the points that were not previously 
		drawn.
		@param pDC
			The device context used to draw
	**/
	void Draw(CDC* pDC);
	//! Redraws the full series.
	/**
		@param pDC
			The device context used to draw
	**/
	void DrawAll(CDC *pDC);

private:
	//! Draws a candle stick point
	void DrawCandleStick(CDC *pDC, int pointIndex);
	void DrawCandleStick(CDC *pDC, SChartCandlestickPoint Point);

	//! Adjust the candlestick width according to screen
	int AdjustCankestickWidthAccordingToScreen();

	//! The candlestick width
	int m_iCandlestickWidth;
	//! The Cycle of the Serie
	int m_Cycle; // DAY = 6 (default)


	// Caches the pen and brushes to avoid creating them for each point
	mutable CBrush ShadowBrush;
	mutable CPen PositivePen;
	mutable CPen NegtivePen;
	mutable CPen ShadowPen;
	mutable CBrush BrushFill;
	mutable CBrush BrushEmpty;
};