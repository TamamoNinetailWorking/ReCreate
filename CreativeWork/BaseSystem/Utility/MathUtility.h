#pragma once

#include <math.h>
#include <random>
#include <Singleton/Singleton.h>
#include <DirectXMath.h>

using namespace DirectX;

namespace MathUtility
{

	class CRandom : public CSingleton<CRandom>
	{
	protected:
		friend class CSingleton<CRandom>;
		CRandom() : CSingleton<CRandom>()
		{
			m_mt = std::mt19937(m_rnd());
		}

		std::random_device m_rnd;
		std::mt19937 m_mt;

	public:

		template <typename Integer>
		Integer RandomRangeInteger(Integer min, Integer max)
		{
			std::uniform_int_distribution<Integer> dst = std::uniform_int_distribution<Integer>(min, max);
			return dst(m_mt);
		}

		template <typename Real>
		Real RandomRangeReal(Real min, Real max)
		{
			std::uniform_real_distribution<Real> dst = std::uniform_real_distribution<Real>(min, max);
			return dst(m_mt);
		}

	};

	inline CRandom& GetRandomizer()
	{
		return CRandom::GetInstance();
	}

	template <typename Number>
	Number Clamp(Number target, Number min, Number max)
	{
		Number returner = target;
		if (target > max)
		{
			returner = max;
		}

		if (target < min)
		{
			returner = min;
		}

		return returner;
	}


	
}