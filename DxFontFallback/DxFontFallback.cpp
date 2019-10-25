// DxFontFallback.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "FontFallbackConst.h"
#include "MapCharacters.h"
#include <iostream>

int main()
{
	MapCharacters map;

	map.init();
	map.CreateFontFallBack();

	for (auto i = 0; i < DWriteFontFallback::SampleConstants::MaxTextBlocks1; i++)
	{
		std::wstring str_text = DWriteFontFallback::SampleConstants::TextStrings1[i].TextString;
		if (!str_text.empty())
			map.MapChar(str_text);
	}
	return S_OK;
}
