#pragma once

#include <cmath>
#include <cstddef>
#include <limits>
#include <numeric>
#include <numbers>
#include <compare>
#include <algorithm>

#include <cassert>
#include <iostream>

namespace loser_math{
	class alignas(sizeof(std::double_t)) RealNumber final{
	public:
		//Built-in Floating Point Type to be Used
		using FloatingPointType = std::double_t;
	private:
		//Machinical Epsilon
		static constexpr const FloatingPointType EPSILON_ = std::numeric_limits<FloatingPointType>::epsilon();

		//Floating-point Decimal
		FloatingPointType value_;

	public:
		//Default Constructor using Delegating Constructor
		constexpr RealNumber() noexcept: RealNumber(0.0){
		}
		//Constructor from Built-in Type
		constexpr RealNumber(const FloatingPointType new_value) noexcept: value_(new_value){
		}
		//Default Destroctor
		~RealNumber() = default;

		//Copy Constructor
		constexpr RealNumber(const RealNumber& new_scalar) noexcept: value_(new_scalar.value_){
		}
		//move Constructor
		constexpr RealNumber(RealNumber&& new_scalar) noexcept: value_(new_scalar.value_){
		}

		//Copy Assignment Operator
		constexpr RealNumber& operator=(const RealNumber& new_scalar) noexcept{
			this->value_ = new_scalar.value_;
			return *this;
		}
		//Move Assignment Operator
		constexpr RealNumber& operator=(RealNumber&& new_scalar) noexcept{
			if(this != &new_scalar){
				this->value_ = new_scalar.value_;
			}
			return *this;
		}

		//Conversion to Built-in Type
		explicit constexpr operator FloatingPointType() const noexcept{
			return this->value_;
		}


		inline constexpr RealNumber operator+() const noexcept{
			return RealNumber(+this->value_);
		}
		inline constexpr RealNumber operator-() const noexcept{
			return RealNumber(-this->value_);
		}

		inline constexpr RealNumber& operator+=(const RealNumber x) noexcept{
			this->value_ += x.value_;
			return *this;
		}
		inline constexpr RealNumber& operator-=(const RealNumber x) noexcept{
			this->value_ -= x.value_;
			return *this;
		}
		inline constexpr RealNumber& operator*=(const RealNumber x) noexcept{
			this->value_ *= x.value_;
			return *this;
		}
		inline constexpr RealNumber& operator/=(const RealNumber x) noexcept{
			this->value_ /= x.value_;
			return *this;
		}
#ifdef USE_REAL_MODULI
		inline RealNumber& operator%=(const RealNumber x) noexcept{
			this->value_ = std::fmod(this->value_, x.value_);
			return *this;
		}
#endif

		friend inline constexpr std::strong_ordering operator<=>(const RealNumber x, const RealNumber y) noexcept{
			const RealNumber::FloatingPointType different = x.value_ - y.value_;

			if(different > RealNumber::EPSILON_){
				return std::strong_ordering::greater;
			}
			else if(different < -RealNumber::EPSILON_){
				return std::strong_ordering::less;
			}
			return std::strong_ordering::equal;
		}
		friend inline constexpr bool operator==(const RealNumber x, const RealNumber y) noexcept{
			return (x <=> y) == std::strong_ordering::equal;
		}
	};

	inline constexpr RealNumber operator+(const RealNumber x, const RealNumber y) noexcept{
		return RealNumber(x) += y;
	}
	inline constexpr RealNumber operator-(const RealNumber x, const RealNumber y) noexcept{
		return RealNumber(x) -= y;
	}
	inline constexpr RealNumber operator*(const RealNumber x, const RealNumber y) noexcept{
		return RealNumber(x) *= y;
	}
	inline constexpr RealNumber operator/(const RealNumber x, const RealNumber y) noexcept{
		return RealNumber(x) /= y;
	}
#ifdef USE_REAL_MODULI
	inline constexpr RealNumber operator%(const RealNumber x, const RealNumber y) noexcept{
		return RealNumber(x) %= y;
	}
#endif

	template<typename ...Args>
	inline constexpr RealNumber sum(const Args& ...rest) noexcept{
		return (... + rest);
	}
	template<typename ...Args>
	inline constexpr RealNumber prod(const Args& ...rest) noexcept{
		return (... * rest);
	}


	inline constexpr RealNumber sqrt(const RealNumber base) noexcept(false){
		RealNumber root = base / 2.0;
		RealNumber prev = 0.0;

		while(root != prev){
			prev = root;
			root = (root + base / root) / 2.0;
		}

		return root;
	}

	template<typename ...Args>
	inline constexpr RealNumber average(const RealNumber first, const Args& ...rest) noexcept{
		return sum(first, rest...) / (1 + sizeof...(rest));
	}

	inline constexpr RealNumber sgn(const RealNumber x) noexcept{
		if(x > 0.0){
			return 1.0;
		}
		else if(x < 0.0){
			return -1.0;
		}

		return 0.0;
	}

	inline constexpr RealNumber abs(const RealNumber scalar) noexcept{
		if(scalar < 0.0){
			return -scalar;
		}
		return scalar;
	}

	inline constexpr RealNumber min(const RealNumber x, const RealNumber y) noexcept{
		if(x > y){
			return y;
		}
		return x;
	}
	inline constexpr RealNumber max(const RealNumber x, const RealNumber y) noexcept{
		if(x < y){
			return y;
		}
		return x;
	}

	inline constexpr RealNumber calcKroneckerDelta(const std::size_t i, const std::size_t j) noexcept{
		if(i == j){
			return 1.0;
		}
		return 0.0;
	}

	inline constexpr RealNumber calcLeviCitivaSymbol(const std::size_t i, const std::size_t j) noexcept{
		if(i == 1 && j == 2){
			return 1.0;
		}
		if(i == 2 && j == 1){
			return -1.0;
		}
		return 0.0;
	}

}
