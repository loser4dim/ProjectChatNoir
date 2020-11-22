#pragma once

#include "Vector.hpp"



namespace loser_math{
	//Row-priority Data Order
	//Column-priority Mathmatical Representation

	template<typename T = RealNumber, std::size_t ROW_NUM = 4, std::size_t COLUMN_NUM = 4>
	class alignas(sizeof(T)) Matrix final{
	public:
		using SizeType = typename std::array<Vector<T, COLUMN_NUM>, ROW_NUM>::size_type;
		using Reference = typename std::array<Vector<T, COLUMN_NUM>, ROW_NUM>::reference;
		using ConstReference = typename std::array<Vector<T, COLUMN_NUM>, ROW_NUM>::const_reference;
		using Pointer = typename std::array<Vector<T, COLUMN_NUM>, ROW_NUM>::pointer;
		using ConstPointer = typename std::array<Vector<T, COLUMN_NUM>, ROW_NUM>::const_pointer;
		using Iterator = typename std::array<Vector<T, COLUMN_NUM>, ROW_NUM>::iterator;
		using ConstIterator = typename std::array<Vector<T, COLUMN_NUM>, ROW_NUM>::const_iterator;

		static inline constexpr const Matrix<T, ROW_NUM, COLUMN_NUM> ZERO() noexcept(false){
			return Matrix<T, ROW_NUM, COLUMN_NUM>();
		}
		static inline constexpr const Matrix<T, ROW_NUM, COLUMN_NUM> IDENTITY() noexcept(false){
			Matrix<T, ROW_NUM, COLUMN_NUM> identity = ZERO();
			for(SizeType i(0); i < ROW_NUM; ++i){
				identity[i] = Vector<T, COLUMN_NUM>::UNIT(i);
			}
			return identity;
		}

		constexpr Matrix() noexcept(false){
			element_.fill(Vector<T, COLUMN_NUM>::ZERO());
		}
		explicit constexpr Matrix(const std::initializer_list<Vector<T, COLUMN_NUM>>& list) noexcept(false){
			constexpr const auto substitute = [](const Vector<T, COLUMN_NUM>& vec){
				return vec;
			};
			std::transform(list.begin(), list.end(), this->begin(), substitute);
		}
		~Matrix() = default;

		constexpr Matrix(const Matrix<T, ROW_NUM, COLUMN_NUM>& new_mat) noexcept(false): element_(new_mat.element_){
		}
		constexpr Matrix(Matrix<T, ROW_NUM, COLUMN_NUM>&& new_mat) noexcept: element_(new_mat.element_){
		}

		constexpr Matrix<T, ROW_NUM, COLUMN_NUM>& operator=(const Matrix<T, ROW_NUM, COLUMN_NUM>& new_mat) noexcept(false){
			if(this != &new_mat){
				this->element_ = new_mat.element_;
			}
			return *this;
		}
		constexpr Matrix<T, ROW_NUM, COLUMN_NUM>& operator=(Matrix<T, ROW_NUM, COLUMN_NUM>&& new_mat) noexcept{
			if(this != &new_mat){
				this->element_ = new_mat.element_;
			}
			return *this;
		}

	private:
		std::array<Vector<T, COLUMN_NUM>, ROW_NUM> element_;

	public:
		inline constexpr Reference operator[](const SizeType idx) noexcept(false){
			return element_[idx % ROW_NUM];
		}
		inline constexpr ConstReference operator[](const SizeType idx) const noexcept(false){
			return element_[idx % ROW_NUM];
		}

		inline constexpr Pointer data() noexcept(false){
			return element_.data();
		}
		inline constexpr ConstPointer data() const noexcept(false){
			return element_.data();
		}

		inline constexpr Iterator begin() noexcept(false){
			return element_.begin();
		}
		inline constexpr ConstIterator begin() const noexcept(false){
			return element_.begin();
		}
		inline constexpr Iterator end() noexcept(false){
			return element_.end();
		}
		inline constexpr ConstIterator end() const noexcept(false){
			return element_.end();
		}

		inline constexpr const Matrix<T, ROW_NUM, COLUMN_NUM> operator+() const noexcept(false){
			return Matrix<T, ROW_NUM, COLUMN_NUM>(*this);
		}
		inline constexpr const Matrix<T, ROW_NUM, COLUMN_NUM> operator-() const noexcept(false){
			Matrix<T, ROW_NUM, COLUMN_NUM> ret = Matrix<T, ROW_NUM, COLUMN_NUM>::ZERO();
			constexpr const auto minus = [](const Vector<T, COLUMN_NUM>& vec){
				return -vec;
			};
			std::transform(this->begin(), this->end(), ret.begin(), minus);
			return ret;
		}

		inline constexpr Matrix<T, ROW_NUM, COLUMN_NUM>& operator+=(const Matrix<T, ROW_NUM, COLUMN_NUM>& right_mat) noexcept(false){
			constexpr const auto add = [](const Vector<T, COLUMN_NUM>& x, const Vector<T, COLUMN_NUM>& y){
				return x + y;
			};
			std::transform(this->begin(), this->end(), right_mat.begin(), this->begin(), add);

			return *this;
		}
		inline constexpr Matrix<T, ROW_NUM, COLUMN_NUM>& operator-=(const Matrix<T, ROW_NUM, COLUMN_NUM>& right_mat) noexcept(false){
			constexpr const auto subtract = [](const Vector<T, COLUMN_NUM>& x, const Vector<T, COLUMN_NUM>& y){
				return x - y;
			};
			std::transform(this->begin(), this->end(), right_mat.begin(), this->begin(), subtract);

			return *this;
		}
		inline constexpr Matrix<T, ROW_NUM, COLUMN_NUM>& operator*=(const T scalar) noexcept(false){
			Matrix<T, ROW_NUM, COLUMN_NUM> ret = Matrix<T, ROW_NUM, COLUMN_NUM>::ZERO();
			const auto multiple = [=](const Vector<T, COLUMN_NUM>& vec){
				return vec * scalar;
			};
			std::transform(this->begin(), this->end(), this->begin(), multiple);
			return *this;
		}
		inline constexpr Matrix<T, ROW_NUM, COLUMN_NUM>& operator/=(const T scalar) noexcept(false){
			Matrix<T, ROW_NUM, COLUMN_NUM> ret = Matrix<T, ROW_NUM, COLUMN_NUM>::ZERO();
			const auto divide = [=](const Vector<T, COLUMN_NUM>& vec){
				return vec / scalar;
			};
			std::transform(this->begin(), this->end(), this->begin(), divide);
			return *this;
		}
	};



	template<typename T = RealNumber, std::size_t ROW_NUM = 4, std::size_t COLUMN_NUM = 4>
	inline constexpr const Matrix<T, ROW_NUM, COLUMN_NUM> operator+(const Matrix<T, ROW_NUM, COLUMN_NUM>& left_mat, const Matrix<T, ROW_NUM, COLUMN_NUM>& right_mat) noexcept(false){
		return Matrix<T, ROW_NUM, COLUMN_NUM>(left_mat) += right_mat;
	}
	template<typename T = RealNumber, std::size_t ROW_NUM = 4, std::size_t COLUMN_NUM = 4>
	inline constexpr const Matrix<T, ROW_NUM, COLUMN_NUM> operator-(const Matrix<T, ROW_NUM, COLUMN_NUM>& left_mat, const Matrix<T, ROW_NUM, COLUMN_NUM>& right_mat) noexcept(false){
		return Matrix<T, ROW_NUM, COLUMN_NUM>(left_mat) -= right_mat;
	}
	template<typename T = RealNumber, std::size_t ROW_NUM = 4, std::size_t COLUMN_NUM = 4>
	inline constexpr const Matrix<T, ROW_NUM, COLUMN_NUM> operator*(const Matrix<T, ROW_NUM, COLUMN_NUM>& mat, const T scalar) noexcept(false){
		return Matrix<T, ROW_NUM, COLUMN_NUM>(mat) *= scalar;
	}
	template<typename T = RealNumber, std::size_t ROW_NUM = 4, std::size_t COLUMN_NUM = 4>
	inline constexpr const Matrix<T, ROW_NUM, COLUMN_NUM> operator*(const T scalar, const Matrix<T, ROW_NUM, COLUMN_NUM>& mat) noexcept(false){
		return mat * scalar;
	}
	template<typename T = RealNumber, std::size_t ROW_NUM = 4, std::size_t COLUMN_NUM = 4, std::size_t NEW_COLUMN_NUM = 4>
	inline constexpr const Matrix<T, ROW_NUM, NEW_COLUMN_NUM> operator*(const Matrix<T, ROW_NUM, COLUMN_NUM>& left_mat, const Matrix<T, COLUMN_NUM, NEW_COLUMN_NUM>& right_mat) noexcept(false){
		Matrix<T, ROW_NUM, NEW_COLUMN_NUM> ret = Matrix<T, ROW_NUM, NEW_COLUMN_NUM>::ZERO();
		for(std::size_t i(0); i < ROW_NUM; ++i){
			for(std::size_t j(0); j < COLUMN_NUM; ++j){
				for(std::size_t k(0); k < NEW_COLUMN_NUM; ++k){
					ret[i][k] += left_mat[i][j] * right_mat[j][k];
				}
			}
		}
		return ret;
	}

	template<typename T = RealNumber, std::size_t ROW_NUM = 4, std::size_t COLUMN_NUM = 4>
	inline constexpr const Vector<T, ROW_NUM> operator*(const Matrix<T, ROW_NUM, COLUMN_NUM>& mat, const Vector<T, COLUMN_NUM>& vec) noexcept(false){
		Vector<T, ROW_NUM> ret;
		const auto multiple = [&](const Vector<T, COLUMN_NUM>& column){
			return dot(column, vec);
		};
		std::transform(mat.begin(), mat.end(), ret.begin(), multiple);
		return ret;
	}


	template<typename T = RealNumber, std::size_t ROW_NUM = 4, std::size_t COLUMN_NUM = 4>
	inline constexpr const Matrix<T, ROW_NUM, COLUMN_NUM> operator/(const Matrix<T, ROW_NUM, COLUMN_NUM>& mat, const T scalar) noexcept(false){
		return Matrix<T, ROW_NUM, COLUMN_NUM>(mat) /= scalar;
	}

	template<typename T = RealNumber, std::size_t ROW_NUM = 4, std::size_t COLUMN_NUM = 4>
	inline constexpr const bool operator==(const Matrix<T, ROW_NUM, COLUMN_NUM>& left_mat, const Matrix<T, ROW_NUM, COLUMN_NUM>& right_mat) noexcept(false){
		return std::equal(left_mat.begin(), left_mat.end(), right_mat.begin(), right_mat.end());
	}
	template<typename T = RealNumber, std::size_t ROW_NUM = 4, std::size_t COLUMN_NUM = 4>
	inline constexpr const bool operator!=(const Matrix<T, ROW_NUM, COLUMN_NUM>& left_mat, const Matrix<T, ROW_NUM, COLUMN_NUM>& right_mat) noexcept(false){
		return !(left_mat == right_mat);
	}

	template<typename T = RealNumber, std::size_t ROW_NUM = 4, std::size_t COLUMN_NUM = 4>
	inline constexpr const Matrix<T, COLUMN_NUM, ROW_NUM> transpose(const Matrix<T, ROW_NUM, COLUMN_NUM>& mat) noexcept(false){
		Matrix<T, COLUMN_NUM, ROW_NUM> ret = Matrix<T, COLUMN_NUM, ROW_NUM>::ZERO();
		for(std::size_t i(0); i < ROW_NUM; ++i){
			for(std::size_t j(0); j < COLUMN_NUM; ++j){
				ret[i][j] = mat[j][i];
			}
		}
		return ret;
	}

	template<typename T = RealNumber, std::size_t N = 4>
	inline constexpr const T trace(const Matrix<T, N, N>& mat) noexcept(false){
		T ret = static_cast<T>(1.0);
		for(std::size_t i(0); i < N; ++i){
			ret *= mat[i][i];
		}
		return ret;
	}

	template<typename T = RealNumber, std::size_t ROW_NUM = 4, std::size_t COLUMN_NUM = 4>
	inline constexpr const Matrix<T, ROW_NUM, COLUMN_NUM> computeDirectProduct(const Vector<T, ROW_NUM>& left_vec, const Vector<T, COLUMN_NUM>& right_vec) noexcept(false){
		Matrix<T, ROW_NUM, COLUMN_NUM> ret = Matrix<T, ROW_NUM, COLUMN_NUM>::ZERO();
		for(std::size_t i(0); i < ROW_NUM; ++i){
			for(std::size_t j(0); j < COLUMN_NUM; ++j){
				ret[i][j] = left_vec[i] * right_vec[j];
			}
		}
		return ret;
	}

	template<typename T = RealNumber, std::size_t N = 4>
	inline constexpr const Matrix<T, N, N> createHouseholderMatrix(const Vector<T, N>& vec) noexcept(false){
		return Matrix<T, N, N>::IDENTITY() - static_cast<T>(2.0) * computeDirectProduct(vec, vec);
	}

	template<typename T = RealNumber, std::size_t N = 4>
	inline constexpr const Matrix<T, N, N> wedge(const Vector<T, N>& a, const Vector<T, N>& b) noexcept(false){
		return computeDirectProduct(a, b) - computeDirectProduct(b, a);
	}

	template<typename T = RealNumber, std::size_t ROW_NUM = 4, std::size_t COLUMN_NUM = 4>
	inline constexpr const std::pair<Matrix<T, ROW_NUM, ROW_NUM>, Matrix<T, ROW_NUM, COLUMN_NUM>> decomposeQR(const Matrix<T, ROW_NUM, COLUMN_NUM>& mat) noexcept(false){
		Matrix<T, COLUMN_NUM, ROW_NUM> ret = Matrix<T, COLUMN_NUM, ROW_NUM>::ZERO();
#ifdef _DEBUG
		assert(ROW_NUM >= COLUMN_NUM);
#endif
		Matrix<T, ROW_NUM, ROW_NUM> Q = Matrix<T, ROW_NUM, ROW_NUM>::IDENTITY();
		Matrix<T, ROW_NUM, COLUMN_NUM> R = mat;

		for(std::size_t i(0); i < COLUMN_NUM; ++i){
			Vector<T, ROW_NUM> x;
			for(size_t j(i); j < COLUMN_NUM; ++j){
				x[j] = R[j][i];
			}
			Vector<T, ROW_NUM> y;
			y[i] = abs(x);

			if(abs(x - y) > std::numeric_limits<T>::epsilon()){
				Matrix<T, ROW_NUM, ROW_NUM> householder = createHouseholderMatrix(normalize(x - y));
				for(size_t j(0); j < i; ++j){
					householder[j][j] = static_cast<T>(1.0);
				}
				Q = householder * Q;

				R = householder * R;
			}
		}
		return std::pair<Matrix<T, ROW_NUM, ROW_NUM>, Matrix<T, ROW_NUM, COLUMN_NUM>>(transpose(Q), R);
	}
#include <iostream>
	template<typename T = RealNumber, std::size_t N = 4>
	inline constexpr const Vector<T, N> solveSimultaneousEquation(const Matrix<T, N, N>& mat, const Vector<T, N>& right_vec) noexcept(false){
		const auto [Q, R] = decomposeQR(mat);
		Vector<T, N> new_right_vec = transpose(Q) * right_vec;
		Vector<T, N> solution;
		for(std::size_t i(0); i < N; ++i){
			T sum = 0.0;
			const std::size_t idx_i = N - (i + 1);
			for(std::size_t j(0); j < i; ++j){
				const std::size_t idx_j = N - (j + 1);
				sum += R[idx_i][idx_j] * solution[idx_j];
			}

			solution[idx_i] = (new_right_vec[idx_i] - sum) / R[idx_i][idx_i];
		}
		return solution;
	}

}