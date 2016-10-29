#pragma once
#include <array>
#include <cassert>

namespace XR
{
	template <int N, class T, class PointT>
	inline T get(const PointT& pt)
	{
		return reinterpret_cast<const T*>(&pt)[N];
	}

	class BoundingBox
	{
	public:
		template <class PointT>
		BoundingBox(const PointT& pt) { init(pt); }

		template <class ForwardIterator>
		BoundingBox(ForwardIterator a, ForwardIterator b);

		template <class PointT>
		inline void init(const PointT& pt);

		template <class PointT>
		inline void include(const PointT& pt);

		double xmin() const { return rep[0]; }
		double ymin() const { return rep[1]; }
		double zmin() const { return rep[2]; }
		double xmax() const { return rep[3]; }
		double ymax() const { return rep[4]; }
		double zmax() const { return rep[5]; }

		double min(int id) { assert(id < 3 && id >= 0); return rep[id]; }
		double max(int id) { assert(id < 3 && id >= 0); return rep[id+3]; }

		const double* data() const { return rep.data(); }

	protected:
		std::array<double, 6> rep;
	};


	template <class ForwardIterator>
	BoundingBox::BoundingBox(ForwardIterator a, ForwardIterator b)
	{
		assert(a != b);
		init(*a);
		while (++a != b)
			include(*a);
	}

	template <class PointT>
	void BoundingBox::init(const PointT& pt)
	{
		typedef typename PointT::Scalar T;
		rep[0] = get<0, T>(pt);
		rep[1] = get<1, T>(pt);
		rep[2] = get<2, T>(pt);
		rep[3] = get<0, T>(pt);
		rep[4] = get<1, T>(pt);
		rep[5] = get<2, T>(pt);
	}

	template <class PointT>
	void BoundingBox::include(const PointT& pt)
	{
		typedef typename PointT::Scalar T;
		if (xmin() > get<0, T>(pt))
			rep[0] = get<0, T>(pt);
		else if (xmax() < get<0, T>(pt))
			rep[3] = get<0, T>(pt);

		if (ymin() > get<1, T>(pt))
			rep[1] = get<1, T>(pt);
		else if (ymax() < get<1, T>(pt))
			rep[4] = get<1, T>(pt);

		if (zmin() > get<2, T>(pt))
			rep[2] = get<2, T>(pt);
		else if (zmax() < get<2, T>(pt))
			rep[5] = get<2, T>(pt);
	}

	template <class PointT>
	void normalizeCoords(const PointT& c, const PointT& d, PointT& pt)
	{
		pt -= c;
		pt /= d / 2;
	}

}