#pragma once

namespace XRwy
{
	template <class T>
	class ArrayWrapper
	{
	public:
		ArrayWrapper(T* arr, size_t sz) :
			m_data(arr), m_size(sz) {}

		size_t size() const { return m_size; }
		T& operator[](int idx) { return m_data[idx]; }
		const T& operator[](int idx) const { return m_data[idx]; }

		T& at(int idx) { return m_data[idx]; }
		const T& at(int idx) const { return m_data[idx]; }
	private:
		const size_t m_size;
		T* m_data;
	};
}