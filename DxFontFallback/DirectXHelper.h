#pragma once
#include "pch.h"
namespace DX
{
	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			throw std::exception("Error");
			//_com_issue_error(hr);
		}
	}
}