#pragma once

#include <math.h>
#include <windows.h>
#include <iosfwd>
#include <limits>
#include "utils.h"

namespace pnGF{

	struct Vector2D {
		double x;
		double y;

		Vector2D() :x(0.0), y(0.0) {}
		Vector2D(double a, double b) :x(a), y(b) {}

		//将向量的两个分量置为0
		void Zero() { x = 0.0, y = 0.0; }

		//判断是否为零向量
		bool isZero() const { return (x*x + y * y) < MinDouble; }

		//返回长度
		inline double Length()const;

		//返回长度的根号
		inline double LengthSq() const;

		//归一化
		inline void Normalize();

		inline double Dot(const Vector2D& v2) const;

		inline int Sign(const Vector2D& v2)const;

		inline Vector2D Perp() const;

		inline void Truncate(double max);

		inline double Distance(const Vector2D &v2)const;

		inline double DistanceSq(const Vector2D &v2)const;

		inline void Reflect(const Vector2D& norm);

		inline Vector2D GetReverse() const;

		//重载操作符
		const Vector2D& operator+=(const Vector2D &rhs) {
			x += rhs.x;
			y += rhs.y;

			return *this;
		}

		const Vector2D& operator-=(const Vector2D &rhs) {
			x -= rhs.x;
			y -= rhs.y;

			return *this;
		}

		const Vector2D& operator*=(const double &rhs) {
			x *= rhs;
			y *= rhs;

			return *this;
		}

		const Vector2D& operator/=(const double &rhs) {
			x /= rhs;
			y /= rhs;

			return *this;
		}

		bool operator==(const Vector2D& rhs) { return (isEqual(x, rhs.x) && isEqual(y, rhs.y)); }

		bool operator!=(const Vector2D& rhs) { return(x != rhs.x) || (y!=rhs.y); }
	};

	//更多的操作符重载
	inline Vector2D operator*(const Vector2D &lhs, double rhs);
	inline Vector2D operator*(double lhs, const Vector2D &rhs);
	inline Vector2D operator-(const Vector2D &lhs, const Vector2D &rhs);
	inline Vector2D operator+(const Vector2D &lhs, const Vector2D &rhs);
	inline Vector2D operator/(const Vector2D &lhs, double val);
	std::ostream& operator<<(std::ostream& os, const Vector2D& rhs);
	std::ifstream& operator>>(std::ifstream& is, Vector2D& lhs);

	//---------------------------成员函数定义
	
	//-----长度 Length
	//
	// 返回值 : 返回2D向量的长度
	//-----------------------------------------------
	inline double Vector2D::Length()const {
		return sqrt(x * x + y * y);
	}

	//-----长度平方值 LengthSq
	//
	// 返回值: 返回2D向量长度的平方
	//-----------------------------------------------
	inline double Vector2D::LengthSq()const {
		return (x * x + y * y);
	}



	//-------------------------
	// 函数名:  Vec2DDot
	// 参数:	另一个2D向量
	// 返回值:  点乘的结果
	inline double Vector2D::Dot(const Vector2D& v2) const {
		return x * v2.x + y * v2.y;
	}
	
	//枚举常量
	enum { clockwise = 1, anticlockwise = -1 };
	//-------------------------
	// 函数名:  Sign 符号函数
	// 参数:	另一个向量 v2
	// 返回值:  返回它与向量 的顺时针关系,clockwise=1,else aniclockwise
	inline int Vector2D::Sign(const Vector2D& v2) const {
		if (y*v2.x > x*v2.y)
		{
			return anticlockwise;
		}
		else
			return clockwise;
	}


	//-------------------------
	// 函数名:  Perpendicular
	// 参数: -void
	// 返回值:  返回此向量的垂直向量
	inline Vector2D Vector2D::Perp()const {
		return Vector2D(-y, x);
	}

	//-------------------------
	// 函数名: Distance 距离 
	// 参数:  想计算距离的另一个向量
	// 返回值:  double 距离值
	inline double Vector2D::Distance(const Vector2D &v2) const {
		double ySeparation = v2.y - y;
		double xSeparation = v2.x - x;
		return sqrt(ySeparation * ySeparation + xSeparation * xSeparation);
	}

	//-------------------------
	// 函数名: Distance 距离的平方 
	// 参数:  想计算距离的另一个向量
	// 返回值:  double 距离值的平方
	inline double Vector2D::DistanceSq(const Vector2D &v2) const {
		double ySeparation = v2.y - y;
		double xSeparation = v2.x - x;
		return ySeparation * ySeparation + xSeparation * xSeparation;
	}


	//-------------------------
	// 函数名:  Truncate 截断
	// 参数: 最大值
	// 返回值:  -void
	inline void Vector2D::Truncate(double max) {
		if (this->Length()>max)
		{
			this->Normalize();
			*this *= max;
		}
	}


	//-------------------------
	// 函数名:  Refleft 反射向量
	// 参数:  -向量
	// 返回值:  -void
	inline void Vector2D::Reflect(const Vector2D& norm) {
		*this += 2.0 * this->Dot(norm) * norm.GetReverse();
	}


	//-------------------------
	// 函数名:  GetReverse 反向量
	// 参数: -void
	// 返回值:  该向量的反向量
	inline Vector2D Vector2D::GetReverse()const {
		return Vector2D(-this->x, -this->y);
	}


	//-------------------------
	// 函数名:  Normalize 单位化向量
	// 参数:	-void
	// 返回值:  -void
	inline void Vector2D::Normalize() {
		double vector_length = this->Length();

		if (vector_length>std::numeric_limits<double>::epsilon())
		{
			this->x /= vector_length;
			this->y /= vector_length;
		}
	}

	//一些额外的操作函数

	//-------------------------
	// 函数名:  POINTStoVector
	// 参数: WinSDK中的 POINTS 转向量
	// 返回值:  与p同位置的Vector2D向量对象
	inline Vector2D POINTStoVector(const POINTS& p)
	{
		return Vector2D(p.x, p.y);
	}

	//-------------------------
	// 函数名:  POINTtoVector
	// 参数: WinSDK中的 POINTS 转向量
	// 返回值:  与p同位置的Vector2D向量对象
	inline Vector2D POINTtoVector(const POINT& p)
	{
		return Vector2D((double)p.x, (double)p.y);
	}

	//-------------------------
	// 函数名:  VectorToPOINTS
	// 参数: Vector2D转Points
	// 返回值:  与Vector2D同位置的POINTS点
	inline POINTS VectorToPOINTS(const Vector2D& v)
	{
		POINTS p;
		p.x = (short)v.x;
		p.y = (short)v.y;

		return p;
	}

	//-------------------------
	// 函数名:  VectorToPOINT
	// 参数: Vector2D向量
	// 返回值:  与Vector2D同位置的POINT点
	inline POINT VectorToPOINT(const Vector2D& v)
	{
		POINT p;
		p.x = (long)v.x;
		p.y = (long)v.y;

		return p;
	}


	//-------------------------
	/// 函数名:  Vec2DNormalize
	/// 参数: Vector2D v
	/// 返回值: 返回一个向量的单位向量
	inline Vector2D Vec2DNormalize(const Vector2D &v)
	{
		Vector2D vec = v;

		double vector_length = vec.Length();

		if (vector_length > std::numeric_limits<double>::epsilon())
		{
			vec.x /= vector_length;
			vec.y /= vector_length;
		}

		return vec;
	}


	//============================================================
	
	///-------------------------
	/// 函数名:  NotInsideRegion
	/// 参数: p 点，top_left 左上角，bot_rgt 右下角
	/// 返回值:  如果点在区域内，则返回false,否则返回true
	inline bool NotInsideRegion(Vector2D p,
		Vector2D top_left,
		Vector2D bot_rgt)
	{
		return (p.x < top_left.x) || (p.x > bot_rgt.x) ||
			(p.y < top_left.y) || (p.y > bot_rgt.y);
	}


	//-------------------------
	/// 函数名:  InsideRegion
	/// 参数: p 点，top_left 左上角，bot_rgt 右下角
	/// 返回值:  如果点在区域内，则返回true,否则返回false
	inline bool InsideRegion(Vector2D p,
		Vector2D top_left,
		Vector2D bot_rgt)
	{
		return !((p.x < top_left.x) || (p.x > bot_rgt.x) ||
			(p.y < top_left.y) || (p.y > bot_rgt.y));
	}

	//----------------------
	/// 重载操作符
	inline Vector2D operator*(const Vector2D &lhs, double rhs)
	{
		Vector2D result(lhs);
		result *= rhs;
		return result;
	}

	inline Vector2D operator*(double lhs, const Vector2D &rhs)
	{
		Vector2D result(rhs);
		result *= lhs;
		return result;
	}

	//overload the - operator
	inline Vector2D operator-(const Vector2D &lhs, const Vector2D &rhs)
	{
		Vector2D result(lhs);
		result.x -= rhs.x;
		result.y -= rhs.y;

		return result;
	}

	//overload the + operator
	inline Vector2D operator+(const Vector2D &lhs, const Vector2D &rhs)
	{
		Vector2D result(lhs);
		result.x += rhs.x;
		result.y += rhs.y;

		return result;
	}

	//overload the / operator
	inline Vector2D operator/(const Vector2D &lhs, double val)
	{
		Vector2D result(lhs);
		result.x /= val;
		result.y /= val;

		return result;
	}

}

