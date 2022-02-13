#pragma once

template<size_t N>
struct StaticString {
	std::array<char, N> val;

	constexpr StaticString(const char(&in)[N]) : val{} { std::copy(in, in + N, val.begin()); }

	QString toString() const {
		return QString::fromUtf8(val.data());
	}
};