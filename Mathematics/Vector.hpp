#pragma once

#include "RealNumber.hpp"
#include <array>
#include <cstddef>
#include <initializer_list>
#include <algorithm>

namespace loser_math{
	template<typename T = RealNumber, std::size_t N = 4>
	class Vector final{
	private:
		using SizeType = typename std::array<T, N>::size_type;
		using Reference = typename std::array<T, N>::reference;
		using ConstReference = typename std::array<T, N>::const_reference;
		using Pointer = typename std::array<T, N>::pointer;
		using ConstPointer = typename std::array<T, N>::const_pointer;
		using Iterator = typename std::array<T, N>::iterator;
		using ConstIterator = typename std::array<T, N>::const_iterator;

		std::array<T, N> element_;

	public:
		static constexpr Vector ZERO() noexcept{
			Vector new_vec;
			return new_vec;
		}
		static constexpr Vector UNIT(const std::size_t idx) noexcept{
			Vector new_vec;
			new_vec[idx] = 1.0;
			return new_vec;
		}


		constexpr Vector() noexcept: element_{static_cast<T>(0.0)}{
		}
		explicit constexpr Vector(const std::initializer_list<T>& list) noexcept{
			constexpr const auto assign = [](const T x){
				return x;
			};
			std::transform(list.begin(), list.end(), this->begin(), assign);
		}
		explicit constexpr Vector(const std::array<T, N>& arr) noexcept: element_(arr){
		}
		explicit constexpr Vector(const T(&arr)[N]) noexcept: element_(std::to_array(arr)){
		}
		~Vector() = default;

		constexpr Vector(const Vector& new_vec) noexcept: element_(new_vec.element_){
		}
		constexpr Vector(Vector&& new_vec) noexcept: element_(new_vec.element_){
		}

		constexpr Vector& operator=(const Vector& new_vec) noexcept{
			this->element_ = new_vec.element_;
			return *this;
		}
		constexpr Vector& operator=(Vector&& new_vec) noexcept{
			if(this != &new_vec){
				this->element_ = new_vec.element_;
			}
			return *this;
		}

		inline constexpr Reference operator[](const SizeType idx) noexcept{
			return element_[idx % N];
		}
		inline constexpr ConstReference operator[](const SizeType idx) const noexcept{
			return element_[idx % N];
		}

		inline constexpr Pointer data() noexcept{
			return element_.data();
		}
		inline constexpr ConstPointer data() const noexcept{
			return element_.data();
		}

		inline constexpr Iterator begin() noexcept{
			return element_.begin();
		}
		inline constexpr ConstIterator begin() const noexcept{
			return element_.begin();
		}

		inline constexpr Iterator end() noexcept{
			return element_.end();
		}
		inline constexpr ConstIterator end() const noexcept{
			return element_.end();
		}

		inline constexpr Vector operator+() const noexcept{
			Vector new_vec;
			constexpr const auto plus = [](const T x){
				return +x;
			};
			std::transform(this->begin(), this->end(), new_vec.begin(), plus);
			return new_vec;
		}
		inline constexpr Vector operator-() const noexcept{
			Vector new_vec;
			constexpr const auto minus = [](const T x){
				return -x;
			};
			std::transform(this->begin(), this->end(), new_vec.begin(), minus);
			return new_vec;
		}

		inline constexpr Vector& operator+=(const Vector& vec) noexcept{
			constexpr const auto add = [](const T x, const T y){
				return x + y;
			};
			std::transform(this->begin(), this->end(), vec.begin(), this->begin(), add);
			return *this;
		}
		inline constexpr Vector& operator-=(const Vector& vec) noexcept{
			constexpr const auto subtract = [](const T x, const T y){
				return x - y;
			};
			std::transform(this->begin(), this->end(), vec.begin(), this->begin(), subtract);
			return *this;
		}
		inline constexpr Vector& operator*=(const T scalar) noexcept{
			constexpr const auto multiple = [&scalar](const T x){
				return x * scalar;
			};
			std::transform(this->begin(), this->end(), this->begin(), multiple);
			return *this;
		}
		inline constexpr Vector& operator/=(const T scalar) noexcept{
			constexpr const auto divide = [&scalar](const T x){
				return x / scalar;
			};
			std::transform(this->begin(), this->end(), this->begin(), divide);
			return *this;
		}
#ifdef USE_REAL_MODULI
		inline constexpr Vector& operator%=(const T scalar) noexcept{
			constexpr const auto moduli = [&scalar](const T x){
				return x % scalar;
			};
			std::transform(this->begin(), this->end(), this->begin(), moduli);
			return *this;
		}
#endif
	};

	template<typename T = RealNumber, std::size_t N = 4>
	inline constexpr Vector<T, N> operator+(const Vector<T, N>& x, const Vector<T, N>& y) noexcept{
		return Vector<T, N>(x) += y;
	}
	template<typename T = RealNumber, std::size_t N = 4>
	inline constexpr Vector<T, N> operator-(const Vector<T, N>& x, const Vector<T, N>& y) noexcept{
		return Vector<T, N>(x) -= y;
	}
	template<typename T = RealNumber, std::size_t N = 4>
	inline constexpr Vector<T, N> operator*(const Vector<T, N>& x, const T scalar) noexcept{
		return Vector<T, N>(x) *= scalar;
	}
	template<typename T = RealNumber, std::size_t N = 4>
	inline constexpr Vector<T, N> operator*(const T scalar, const Vector<T, N>& x) noexcept{
		return x * scalar;
	}
	template<typename T = RealNumber, std::size_t N = 4>
	inline constexpr Vector<T, N> operator/(const Vector<T, N>& x, const T scalar) noexcept{
		return Vector<T, N>(x) /= scalar;
	}
#ifdef USE_REAL_MODULI
	template<typename T = RealNumber, std::size_t N = 4>
	inline constexpr Vector<T, N> operator%(const Vector<T, N>& x, const T scalar) noexcept{
		return Vector<T, N>(x) %= scalar;
	}
#endif

	template<typename T = RealNumber, std::size_t N = 4>
	inline constexpr bool operator==(const Vector<T, N>& x, const Vector<T, N>& y) noexcept{
		return std::equal(x.begin(), x.end(), y.begin());
	}

	template<typename T = RealNumber, std::size_t N = 4>
	inline constexpr T dot(const Vector<T, N>& x, const Vector<T, N>& y){
		return std::inner_product(x.begin(), x.end(), y.begin(), static_cast<T>(0.0));
	}

	template<typename T = RealNumber, std::size_t N = 4>
	inline constexpr T abs(const Vector<T, N>& x){
		return sqrt(dot(x, x));
	}
	template<typename T = RealNumber, std::size_t N = 4>
	inline constexpr T calcNorm(const Vector<T, N>& x){
		return abs(x);
	}
	template<typename T = RealNumber, std::size_t N = 4>
	inline constexpr T distance(const Vector<T, N>& x, const Vector<T, N>& y){
		return abs(x - y);
	}

	template<typename T = RealNumber, std::size_t N = 4>
	inline constexpr Vector<T, N> normalize(const Vector<T, N>& x){
		return x / abs(x);
	}
}
