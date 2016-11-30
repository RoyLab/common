#pragma once
#include <vector>
#include <algorithm>

namespace XR
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

    template <class T>
    class RecursiveVector:
        public std::vector<T>
    {
        typedef std::vector<T> Base;
    public:
        const_reference operator[](size_type _Pos) const { return Base::operator[](_Pos % size()); }
        reference operator[](size_type _Pos) { return Base::operator[](_Pos % size()); }
    };
}

namespace std
{
    template<class _RanIt,
        class _Pr> inline
        pair<_RanIt, _RanIt>
        my_guess(_RanIt _First, _RanIt _Last, _Pr& _Pred)
    {
        _RanIt Mid = _First;
        --_Last;
        while (Mid != _Last)
        {
            _RanIt Comp = Mid; ++Comp;
            if (!_Pred(*Mid, *Comp))
            {
                std::swap(*Mid, *Comp);
                std::swap(Mid, Comp);
            }
            else
            {
                std::swap(*Comp, *_Last);
                --_Last;
            }
        }
        _RanIt Mid_1 = Mid; ++Mid_1;
        return pair<_RanIt, _RanIt>(Mid, Mid_1);
    }

    template<class _RanIt,
        class _Diff,
        class _Pr> inline
        void _Sort_unchecked2(_RanIt _First, _RanIt _Last, _Diff _Ideal, _Pr& _Pred)
    {	// order [_First, _Last), using _Pred
        _Diff _Count;
        while (1 < (_Count = _Last - _First))
        {	// divide and conquer by quicksort
            pair<_RanIt, _RanIt> _Mid =
                my_guess(_First, _Last, _Pred);

            if (_Mid.first - _First < _Last - _Mid.second)
            {	// loop on second half
                _Sort_unchecked2(_First, _Mid.first, _Ideal, _Pred);
                _First = _Mid.second;
            }
            else
            {	// loop on first half
                _Sort_unchecked2(_Mid.second, _Last, _Ideal, _Pred);
                _Last = _Mid.first;
            }
        }
    }

    template<class _RanIt,
        class _Pr> inline
        void _Sort_unchecked22(_RanIt _First, _RanIt _Last, _Pr& _Pred)
    {	// order [_First, _Last), using _Pred
        _Sort_unchecked2(_First, _Last, _Last - _First, _Pred);
    }

    template<class _RanIt,
        class _Pr> inline
        void quicksort(_RanIt _First, _RanIt _Last, _Pr _Pred)
    {	// order [_First, _Last), using _Pred
        _DEBUG_RANGE(_First, _Last);
        _Sort_unchecked22(_Unchecked(_First), _Unchecked(_Last), _Pred);
    }
}
