#pragma once
class TextAnalysisSource : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>,IDWriteTextAnalysisSource>
{
public:
	TextAnalysisSource();

	// IDWriteTextAnalysisSource:
	HRESULT STDMETHODCALLTYPE GetLocaleName(UINT32 text_position,UINT32* text_length,const WCHAR** locale_name) override;
	HRESULT STDMETHODCALLTYPE GetNumberSubstitution(UINT32 text_position,UINT32* text_length,IDWriteNumberSubstitution** number_substitution) override;
	DWRITE_READING_DIRECTION STDMETHODCALLTYPE GetParagraphReadingDirection() override;
	HRESULT STDMETHODCALLTYPE GetTextAtPosition(UINT32 text_position,const WCHAR** text_string,UINT32* text_length) override;
	HRESULT STDMETHODCALLTYPE GetTextBeforePosition(UINT32 text_position,const WCHAR** text_string,UINT32* text_length) override;

	HRESULT STDMETHODCALLTYPE RuntimeClassInitialize(std::wstring& text,
													 const std::wstring& locale_name,
													 IDWriteNumberSubstitution* number_substitution,
													 DWRITE_READING_DIRECTION reading_direction);

protected:
	~TextAnalysisSource() override;

private:
	std::wstring text_;
	std::wstring locale_name_;
	Microsoft::WRL::ComPtr<IDWriteNumberSubstitution> number_substitution_;
	DWRITE_READING_DIRECTION reading_direction_;

	
};


//
//class TextSource  : public IDWriteTextAnalysisSource
//{
//
//	IDWriteFactory* mp_factory;
//	IDWriteNumberSubstitution* mp_substitution;
//	wchar_t                      mpwsz_text[3];
//	uint32_t                     mi_text_length;
//	ULONG                        ml_ref_count;
//
//	
//
//public:
//	TextSource(CComPtr<IDWriteFactory> p_factory, CComPtr<IDWriteNumberSubstitution> p_substitution,
//		const wchar_t* pwsz_text, uint32_t i_text_length)
//
//		: mp_factory(p_factory), mp_substitution(p_substitution), ml_ref_count(0)
//	{
//		memset(mpwsz_text, 0, sizeof(mpwsz_text));
//		mi_text_length = i_text_length < 2 ? i_text_length : 2;
//		memcpy(mpwsz_text, pwsz_text, mi_text_length * sizeof(*mpwsz_text));
//	}
//	virtual ~TextSource() {}
//
//	virtual HRESULT STDMETHODCALLTYPE GetLocaleName(UINT32, UINT32*,
//		const WCHAR** ppwsz_locale_name)
//	{
//		*ppwsz_locale_name = L"en-US";
//		return S_OK;
//	}
//
//	virtual HRESULT STDMETHODCALLTYPE GetNumberSubstitution(UINT32, UINT32*,
//		IDWriteNumberSubstitution** pp_substitution)
//	{
//		mp_substitution->AddRef();
//		*pp_substitution = mp_substitution;
//		return S_OK;
//	}
//
//	virtual DWRITE_READING_DIRECTION STDMETHODCALLTYPE GetParagraphReadingDirection()
//	{
//		return DWRITE_READING_DIRECTION_LEFT_TO_RIGHT;
//	}
//
//	virtual HRESULT STDMETHODCALLTYPE GetTextAtPosition(UINT32 i_text_position, const WCHAR** ppwsz_text,
//		UINT32* pi_text_length)
//	{
//		if (i_text_position > mi_text_length)
//			return E_INVALIDARG;
//
//		*ppwsz_text = mpwsz_text + i_text_position;
//		*pi_text_length = mi_text_length - i_text_position;
//
//		return S_OK;
//	}
//
//	virtual HRESULT STDMETHODCALLTYPE GetTextBeforePosition(UINT32 i_text_position, const WCHAR** ppwsz_text,
//		UINT32* pi_text_length)
//	{
//		if (i_text_position > mi_text_length)
//			return E_INVALIDARG;
//
//		if (i_text_position == 0)
//		{
//			*ppwsz_text = NULL;
//			*pi_text_length = 0;
//			return S_OK;
//		}
//
//		*ppwsz_text = mpwsz_text;
//		*pi_text_length = i_text_position;
//		return S_OK;
//	}
//
//	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID* pp_obj)
//	{
//		if (!pp_obj)
//			return E_INVALIDARG;
//
//		*pp_obj = NULL;
//
//		if (riid == IID_IUnknown || riid == __uuidof(IDWriteTextAnalysisSource))
//		{
//			*pp_obj = (LPVOID)this;
//			AddRef();
//			return NOERROR;
//		}
//		return E_NOINTERFACE;
//	}
//
//	virtual ULONG STDMETHODCALLTYPE AddRef()
//	{
//		return InterlockedIncrement(&ml_ref_count);
//	}
//
//	virtual ULONG STDMETHODCALLTYPE Release()
//	{
//		ULONG l_ret = InterlockedDecrement(&ml_ref_count);
//		if (l_ret == 0)
//		{
//			delete this;
//		}
//
//		return l_ret;
//	}
//};
//
