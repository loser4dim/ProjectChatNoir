#pragma once

#include "Matrix.hpp"

#include <array>
#include <numeric>
#include <numbers>
#include <type_traits>


#include <cmath>
#include <cstddef>

#include <iostream>


namespace loser_math{
	constexpr const RealNumber PI = RealNumber(std::numbers::pi);
	constexpr const RealNumber EPSILON = RealNumber(std::numeric_limits<RealNumber>::epsilon());

	enum Axis: std::size_t{
		X = 0,
		Y = 1,
		Z = 2,
		W = 3
	};

	using Vector3D = Vector<RealNumber, 3>;
	using Vector4D = Vector<RealNumber, 4>;
	using Matrix3D = Matrix<RealNumber, 3, 3>;
	using Matrix4D = Matrix<RealNumber, 4, 4>;

	inline std::ostream& operator<<(std::ostream& output, const RealNumber x){
		output << static_cast<RealNumber::FloatingPointType>(x);
		return output;
	}
	inline std::ostream& operator<<(std::ostream& output, const Vector3D& x){
		output << "(" << x[Axis::X] << ", " << x[Axis::Y] << ", " << x[Axis::Z] << ")";
		return output;
	}
	inline std::ostream& operator<<(std::ostream& output, const Vector4D& x){
		output << "(" << x[Axis::X] << ", " << x[Axis::Y] << ", " << x[Axis::Z] << ", " << x[Axis::W] << ")";
		return output;
	}
	inline std::ostream& operator<<(std::ostream& output, const Matrix4D& x){
		output << "[" << x[0] << "\n" << x[1] << "\n" << x[2] << "\n" << x[3] << "\n" << "]";
		return output;
	}
	inline std::ostream& operator<<(std::ostream& output, const Vector<std::float_t, 4>& x){
		output << "(" << x[Axis::X] << ", " << x[Axis::Y] << ", " << x[Axis::Z] << ", " << x[Axis::W] << ")";
		return output;
	}
	inline std::ostream& operator<<(std::ostream& output, const Matrix<std::float_t, 4, 4>& x){
		output << "[" << x[0] << "\n" << x[1] << "\n" << x[2] << "\n" << x[3] << "\n" << "]";
		return output;
	}

	inline constexpr const Vector3D cross(const Vector3D& a, const Vector3D& b) noexcept(false){
		return Vector3D{
			a[Axis::Y] * b[Axis::Z] - a[Axis::Z] * b[Axis::Y],
			a[Axis::Z] * b[Axis::X] - a[Axis::X] * b[Axis::Z],
			a[Axis::X] * b[Axis::Y] - a[Axis::Y] * b[Axis::X]
		};
	}

	inline constexpr const Vector<std::float_t, 3> cross(const Vector<std::float_t, 3>& a, const Vector<std::float_t, 3>& b) noexcept(false){
		return Vector<std::float_t, 3>{
			a[Axis::Y] * b[Axis::Z] - a[Axis::Z] * b[Axis::Y],
			a[Axis::Z] * b[Axis::X] - a[Axis::X] * b[Axis::Z],
			a[Axis::X] * b[Axis::Y] - a[Axis::Y] * b[Axis::X]
		};
	}

	inline constexpr Vector4D cross(const Vector4D& a, const Vector4D& b, const Vector4D& c) noexcept(false){
		return Vector4D(
			{
				 a[Axis::Y] * (b[Axis::Z] * c[Axis::W] - b[Axis::W] * c[Axis::Z]) + a[Axis::Z] * (b[Axis::W] * c[Axis::Y] - b[Axis::Y] * c[Axis::W]) + a[Axis::W] * (b[Axis::Y] * c[Axis::Z] - b[Axis::Z] * c[Axis::Y]),
				-a[Axis::Z] * (b[Axis::W] * c[Axis::X] - b[Axis::X] * c[Axis::W]) - a[Axis::W] * (b[Axis::X] * c[Axis::Z] - b[Axis::Z] * c[Axis::X]) - a[Axis::X] * (b[Axis::Z] * c[Axis::W] - b[Axis::W] * c[Axis::Z]),
				 a[Axis::W] * (b[Axis::X] * c[Axis::Y] - b[Axis::Y] * c[Axis::X]) + a[Axis::X] * (b[Axis::Y] * c[Axis::W] - b[Axis::W] * c[Axis::Y]) + a[Axis::Y] * (b[Axis::W] * c[Axis::X] - b[Axis::X] * c[Axis::W]),
				-a[Axis::X] * (b[Axis::Y] * c[Axis::Z] - b[Axis::Z] * c[Axis::Y]) - a[Axis::Y] * (b[Axis::Z] * c[Axis::X] - b[Axis::X] * c[Axis::Z]) - a[Axis::Z] * (b[Axis::X] * c[Axis::Y] - b[Axis::Y] * c[Axis::X])
			}
		);
	}






	inline constexpr const Vector4D computeTriangleCircumcenter(const Vector4D& v0, const Vector4D& v1, const Vector4D& v2) noexcept(false){
		Matrix3D mat{
			Vector3D{dot(v0 - v1, v0), dot(v0 - v1, v1), dot(v0 - v1, v2)},
			Vector3D{dot(v1 - v2, v0), dot(v1 - v2, v1), dot(v1 - v2, v2)},
			Vector3D{1.0, 1.0, 1.0}
		};
		Vector3D norm_difference{
			(dot(v0, v0) - dot(v1, v1)) / 2.0,
			(dot(v1, v1) - dot(v2, v2)) / 2.0,
			1.0
		};

		Vector<RealNumber, 3> solution = solveSimultaneousEquation(mat, norm_difference);

		return solution[0] * v0 + solution[1] * v1 + solution[2] * v2;
	}

	inline constexpr const Vector4D computeTetrahedronCircumcenter(const Vector4D& v0, const Vector4D& v1, const Vector4D& v2, const Vector4D& v3) noexcept(false){
		Matrix4D mat{
			Vector4D{dot(v0 - v1, v0), dot(v0 - v1, v1), dot(v0 - v1, v2), dot(v0 - v1, v3)},
			Vector4D{dot(v1 - v2, v0), dot(v1 - v2, v1), dot(v1 - v2, v2), dot(v1 - v2, v3)},
			Vector4D{dot(v2 - v3, v0), dot(v2 - v3, v1), dot(v2 - v3, v2), dot(v2 - v3, v3)},
			Vector4D{static_cast<RealNumber>(1.0), static_cast<RealNumber>(1.0), static_cast<RealNumber>(1.0), static_cast<RealNumber>(1.0)}
		};
		Vector4D norm_difference{
			(dot(v0, v0) - dot(v1, v1)) / static_cast<RealNumber>(2.0),
			(dot(v1, v1) - dot(v2, v2)) / static_cast<RealNumber>(2.0),
			(dot(v2, v2) - dot(v3, v3)) / static_cast<RealNumber>(2.0),
			static_cast<RealNumber>(1.0)
		};

		Vector4D solution = solveSimultaneousEquation(mat, norm_difference);

		return solution[0] * v0 + solution[1] * v1 + solution[2] * v2 + solution[3] * v3;
	}

	inline constexpr const Vector4D computeHypersphereCenter(const Vector4D& v0, const Vector4D& v1, const Vector4D& v2, const Vector4D& v3, const Vector4D& circumcenter, const RealNumber radius) noexcept(false){
		const RealNumber r = distance(circumcenter, v0);
		return circumcenter + sqrt(radius * radius - r * r) * normalize(cross(v1 - v0, v2 - v0, v3 - v0));
	}

	inline constexpr const Vector4D computeHypersphereCenter(const Vector4D& v0, const Vector4D& v1, const Vector4D& v2, const Vector4D& v3, const RealNumber radius) noexcept(false){
		return computeHypersphereCenter(v0, v1, v2, v3, computeTetrahedronCircumcenter(v0, v1, v2, v3), radius);
	}


	/*
	using RealNumber = std::float_t;
	using Vector3D = std::array<RealNumber, 3>;
	using Vector4D = std::array<RealNumber, 4>;
	using Matrix4D = std::array<Vector4D, 4>;

	enum class Axis: std::size_t{
		X = 0,
		Y = 0,
		Z = 0,
		W = 0
	};

	Vector4D operator+(const Vector4D& x, const Vector4D& y) noexcept(false);
	Vector4D operator-(const Vector4D& x, const Vector4D& y) noexcept(false);





	Vector4D cross(const Vector4D& x, const Vector4D& y, const Vector4D& z) noexcept(false);
	*/
}