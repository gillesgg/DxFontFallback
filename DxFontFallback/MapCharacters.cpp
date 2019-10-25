#include "pch.h"
#include "DirectXHelper.h"
#include "TextAnalysisSource.h"
#include "FontFallbackConst.h"
#include "MapCharacters.h"


HRESULT MapCharacters::init()
{
	HRESULT hr = S_OK;

	if (FAILED(hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(directwriteFactory_), static_cast<IUnknown**>(&directwriteFactory_))))
	{
		ATLTRACE(L"Unable to initialize DirectWrite");
		return hr;
	}
	return (hr);
}


HRESULT MapCharacters::CreateFontFallBack()
{

	Microsoft::WRL::ComPtr<IDWriteFontFallbackBuilder> fallbackBuilder;
	Microsoft::WRL::ComPtr<IDWriteFontFallback> systemFallback;
	Microsoft::WRL::ComPtr<IDWriteFontFallback> customFallback;
	Microsoft::WRL::ComPtr<IDWriteFactory2> dwriteFactory = directwriteFactory_.Get();

	DX::ThrowIfFailed(dwriteFactory->GetSystemFontFallback(&systemFallback));

	fallbackList_[DWriteFontFallback::SampleConstants::FontFallbackSystem] = systemFallback;

	DWRITE_UNICODE_RANGE range[] = {
		{0x00000, 0xffffffff},
	};
	WCHAR const* fallbackEmoji[1] = { DWriteFontFallback::SampleConstants::EmojiFontFamilyName };

	DX::ThrowIfFailed(dwriteFactory->CreateFontFallbackBuilder(&fallbackBuilder));
	DX::ThrowIfFailed(fallbackBuilder->AddMapping(range, 1, fallbackEmoji, 1));
	DX::ThrowIfFailed(fallbackBuilder->CreateFontFallback(&customFallback));
	fallbackList_[DWriteFontFallback::SampleConstants::FontFallbackEmoji] = customFallback;
	customFallback = nullptr;
	fallbackBuilder = nullptr;

	DX::ThrowIfFailed(dwriteFactory->CreateFontFallbackBuilder(&fallbackBuilder));
	DX::ThrowIfFailed(fallbackBuilder->AddMapping(range, 1, fallbackEmoji, 1));
	DX::ThrowIfFailed(fallbackBuilder->AddMappings(systemFallback.Get()));
	DX::ThrowIfFailed(fallbackBuilder->CreateFontFallback(&customFallback));
	customFallback = nullptr;
	fallbackBuilder = nullptr;


	fallbackList_[DWriteFontFallback::SampleConstants::FontFallbackEmojiSystem] = customFallback;

	WCHAR const* fallbackEmojiSymbol[2] = {
		DWriteFontFallback::SampleConstants::EmojiFontFamilyName,
		DWriteFontFallback::SampleConstants::SymbolFontFamilyName,
	};

	DX::ThrowIfFailed(dwriteFactory->CreateFontFallbackBuilder(&fallbackBuilder));
	DX::ThrowIfFailed(fallbackBuilder->AddMapping(range, 1, fallbackEmojiSymbol, 2));
	DX::ThrowIfFailed(fallbackBuilder->CreateFontFallback(&customFallback));

	fallbackList_[DWriteFontFallback::SampleConstants::FontFallbackEmojiSymbol] = customFallback;
	customFallback = nullptr;
	fallbackBuilder = nullptr;


	DX::ThrowIfFailed(dwriteFactory->CreateFontFallbackBuilder(&fallbackBuilder));
	DX::ThrowIfFailed(fallbackBuilder->AddMapping(range, 1, fallbackEmojiSymbol, 2));
	DX::ThrowIfFailed(fallbackBuilder->AddMappings(systemFallback.Get()));
	DX::ThrowIfFailed(fallbackBuilder->CreateFontFallback(&customFallback));
	fallbackList_[DWriteFontFallback::SampleConstants::FontFallbackEmojiSymbolSystem] = customFallback;
	WCHAR const* fallbackSymbol[1] = { DWriteFontFallback::SampleConstants::SymbolFontFamilyName };
	customFallback = nullptr;
	fallbackBuilder = nullptr;

	DX::ThrowIfFailed(dwriteFactory->CreateFontFallbackBuilder(&fallbackBuilder));
	DX::ThrowIfFailed(fallbackBuilder->AddMapping(range, 1, fallbackSymbol, 1));
	DX::ThrowIfFailed(fallbackBuilder->CreateFontFallback(&customFallback));
	fallbackList_[DWriteFontFallback::SampleConstants::FontFallbackSymbol] = customFallback;
	customFallback = nullptr;
	fallbackBuilder = nullptr;

	DX::ThrowIfFailed(dwriteFactory->CreateFontFallbackBuilder(&fallbackBuilder));
	DX::ThrowIfFailed(fallbackBuilder->AddMapping(range, 1, fallbackSymbol, 1));
	DX::ThrowIfFailed(fallbackBuilder->AddMappings(systemFallback.Get()));
	DX::ThrowIfFailed(fallbackBuilder->CreateFontFallback(&customFallback));

	fallbackList_[DWriteFontFallback::SampleConstants::FontFallbackSymbolSystem] = customFallback;
	return S_OK;
}


HRESULT MapCharacters::MapChar(std::wstring buffer)
{
	HRESULT												hr;
	float												f_scale;
	UINT32												i_mapped_length = 0;
	Microsoft::WRL::ComPtr <IDWriteFont>				dw_font;
	Microsoft::WRL::ComPtr<TextAnalysisSource>			text;
	Microsoft::WRL::ComPtr<IDWriteNumberSubstitution>	number_substitution_;
	Microsoft::WRL::ComPtr <IDWriteFontCollection>		fontcollection;

	Microsoft::WRL::MakeAndInitialize<TextAnalysisSource>(&text, buffer, std::wstring(L"en-us"), number_substitution_.Get(),DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);

	DX::ThrowIfFailed(directwriteFactory_->CreateNumberSubstitution(DWRITE_NUMBER_SUBSTITUTION_METHOD_NONE,L"en-us", true /* ignoreUserOverride */,&number_substitution_));	

	for (auto item : fallbackList_)
	{
		if (item.second != nullptr)
		{
			hr = item.second->MapCharacters(text.Get(), 0,static_cast<UINT32> (buffer.length()), fontcollection.Get(), nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, &i_mapped_length, &dw_font, &f_scale);
			

			if (dw_font != nullptr)
			{
				DumpInformations(buffer, item.first, dw_font);
			}
		}
	}
	return S_OK;
}

HRESULT MapCharacters::DumpInformations(std::wstring buffer, int index1, Microsoft::WRL::ComPtr <IDWriteFont> dw_font)
{
	UINT32 index;

	Microsoft::WRL::ComPtr <IDWriteFontFamily> pFontFamily = nullptr;
	Microsoft::WRL::ComPtr <IDWriteLocalizedStrings> pFamilyNames = nullptr;

		BOOL exists = false;
		HRESULT hr;

		if (FAILED(hr = dw_font->GetFontFamily(&pFontFamily)))
		{
			ATLTRACE(L"Unable to get font family");
			return hr;
		}

		if (FAILED(hr = pFontFamily->GetFamilyNames(&pFamilyNames)))
		{
			ATLTRACE(L"Unable to get font name");
			return hr;
		}
		wchar_t localeName[LOCALE_NAME_MAX_LENGTH];

		// Get the default locale for this user.
		int defaultLocaleSuccess = GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH);
		// If the default locale is returned, find that locale name, otherwise use "en-us".
		if (defaultLocaleSuccess)
		{
			hr = pFamilyNames->FindLocaleName(localeName, &index, &exists);
		}
		else
		{
			hr = pFamilyNames->FindLocaleName(L"en-us", &index, &exists);
		}

		// If the specified locale doesn't exist, select the first on the list.
		if (!exists)
			index = 0;

		UINT32 length = 0;

		hr = pFamilyNames->GetStringLength(index, &length);

		// Allocate a string big enough to hold the name.
		wchar_t* name = new (std::nothrow) wchar_t[length + 1];

		if (SUCCEEDED(hr = pFamilyNames->GetString(index, name, length + 1)))
		{
			ATLTRACE(L"buffer=%s , fallback implementation=%s , font name=%s, \n", buffer.c_str(), DWriteFontFallback::SampleConstants::FontFallbackDescriptions[index1].c_str(), name);
		}
		delete[] name;

	return S_OK;
}