#pragma once

#include <vector>


namespace fff
{

struct IntPoint
{
	int X, Y;

	IntPoint() : X(0), Y(0)
	{}

	IntPoint(int _X, int _Y) : X(_X), Y(_Y)
	{}

	IntPoint(const IntPoint& Others) : X(Others.X), Y(Others.Y)
	{}

	inline IntPoint& operator = (const IntPoint& Others)
	{
		if (this != &Others)
		{
			X = Others.X;
			Y = Others.Y;
		}
		return *this;
	}

	inline IntPoint operator + (const IntPoint& Others) const
	{
		return IntPoint(X + Others.X, Y + Others.Y);
	}

	inline IntPoint operator - (const IntPoint& Others) const
	{
		return IntPoint(X - Others.X, Y - Others.Y);
	}

};

struct Vector
{
	float X, Y, Z;

	Vector() : X(0), Y(0), Z(0)
	{}

	Vector(float _X, float _Y, float _Z) : X(_X), Y(_Y), Z(_Z)
	{}

	Vector(const Vector& Others) : X(Others.X), Y(Others.Y), Z(Others.Z)
	{}

	inline Vector& operator = (const Vector& Others)
	{
		if (this != &Others)
		{
			X = Others.X;
			Y = Others.Y;
			Z = Others.Z;
		}
		return *this;
	}

	inline Vector operator + (const Vector& Others) const
	{
		return Vector(X + Others.X, Y + Others.Y, Z + Others.Z);
	}

	inline Vector operator - (const Vector& Others) const
	{
		return Vector(X - Others.X, Y - Others.Y, Z - Others.Z);
	}

	static Vector Cross(const Vector& A, const Vector& B)
	{
		return Vector(A.Y*B.Z - A.Z*B.Y, A.Z*B.X - A.X*B.Z, A.X*B.Y - A.Y*B.X);
	}

	static Vector Barycentric(const Vector& A, const Vector& B, const Vector& C, const Vector& P)
	{
		Vector Coord = Cross(Vector(B.X - A.X, C.X - A.X, A.X - P.X), Vector(B.Y - A.Y, C.Y - A.Y, A.Y - P.Y));
		if (std::abs(Coord.Z) < 1)
		{
			return Vector(-1.f, 1.f, 1.f);
		}
		return Vector(1.f - (Coord.X + Coord.Y) / Coord.Z, Coord.X / Coord.Z, Coord.Y / Coord.Z);
	}

	static Vector Barycentric(const IntPoint& A, const IntPoint& B, const IntPoint& C, const IntPoint& P)
	{
		Vector Coord = Cross(Vector(B.X - A.X, C.X - A.X, A.X - P.X), Vector(B.Y - A.Y, C.Y - A.Y, A.Y - P.Y));
		if (std::abs(Coord.Z) < 1)
		{
			return Vector(-1.f, 1.f, 1.f);
		}
		return Vector(1.f - (Coord.X + Coord.Y) / Coord.Z, Coord.X / Coord.Z, Coord.Y / Coord.Z);
	}

};



} // namespace fff
