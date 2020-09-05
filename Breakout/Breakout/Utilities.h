#pragma once
#include <iostream>
namespace util
{
	/// <summary>
	/// Clamps the given value in a given range.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="n">Value to clamp</param>
	/// <param name="lower">Lower range value</param>
	/// <param name="upper">Upper range value</param>
	/// <returns></returns>
	template <typename T>
	T clamp(const T& n, const T& lower, const T& upper) {
		return std::max(lower, std::min(n, upper));
	}
}