#pragma once




class MapCharacters
{
public:
	HRESULT init();
	HRESULT CreateFontFallBack();
	HRESULT MapChar(std::wstring buffer);
	HRESULT DumpInformations(std::wstring buffer, int index,Microsoft::WRL::ComPtr <IDWriteFont> dw_font);
private:
	Microsoft::WRL::ComPtr<IDWriteFactory2>							directwriteFactory_ = nullptr;
	std::map<int, Microsoft::WRL::ComPtr<IDWriteFontFallback>>		fallbackList_;

};

