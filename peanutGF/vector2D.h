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

		//������������������Ϊ0
		void Zero() { x = 0.0, y = 0.0; }

		//�ж��Ƿ�Ϊ������
		bool isZero() const { return (x*x + y * y) < MinDouble; }

		//���س���
		inline double Length()const;

		//���س��ȵĸ���
		inline double LengthSq() const;

		//��һ��
		inline void Normalize();

		inline double Dot(const Vector2D& v2) const;

		inline int Sign(const Vector2D& v2)const;

		inline Vector2D Perp() const;

		inline void Truncate(double max);

		inline double Distance(const Vector2D &v2)const;

		inline double DistanceSq(const Vector2D &v2)const;

		inline void Reflect(const Vector2D& norm);

		inline Vector2D GetReverse() const;

		//���ز�����
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

	//����Ĳ���������
	inline Vector2D operator*(const Vector2D &lhs, double rhs);
	inline Vector2D operator*(double lhs, const Vector2D &rhs);
	inline Vector2D operator-(const Vector2D &lhs, const Vector2D &rhs);
	inline Vector2D operator+(const Vector2D &lhs, const Vector2D &rhs);
	inline Vector2D operator/(const Vector2D &lhs, double val);
	std::ostream& operator<<(std::ostream& os, const Vector2D& rhs);
	std::ifstream& operator>>(std::ifstream& is, Vector2D& lhs);

	//---------------------------��Ա��������
	
	//-----���� Length
	//
	// ����ֵ : ����2D�����ĳ���
	//-----------------------------------------------
	inline double Vector2D::Length()const {
		return sqrt(x * x + y * y);
	}

	//-----����ƽ��ֵ LengthSq
	//
	// ����ֵ: ����2D�������ȵ�ƽ��
	//-----------------------------------------------
	inline double Vector2D::LengthSq()const {
		return (x * x + y * y);
	}



	//-------------------------
	// ������:  Vec2DDot
	// ����:	��һ��2D����
	// ����ֵ:  ��˵Ľ��
	inline double Vector2D::Dot(const Vector2D& v2) const {
		return x * v2.x + y * v2.y;
	}
	
	//ö�ٳ���
	enum { clockwise = 1, anticlockwise = -1 };
	//-------------------------
	// ������:  Sign ���ź���
	// ����:	��һ������ v2
	// ����ֵ:  ������������ ��˳ʱ���ϵ,clockwise=1,else aniclockwise
	inline int Vector2D::Sign(const Vector2D& v2) const {
		if (y*v2.x > x*v2.y)
		{
			return anticlockwise;
		}
		else
			return clockwise;
	}


	//-------------------------
	// ������:  Perpendicular
	// ����: -void
	// ����ֵ:  ���ش������Ĵ�ֱ����
	inline Vector2D Vector2D::Perp()const {
		return Vector2D(-y, x);
	}

	//-------------------------
	// ������: Distance ���� 
	// ����:  �����������һ������
	// ����ֵ:  double ����ֵ
	inline double Vector2D::Distance(const Vector2D &v2) const {
		double ySeparation = v2.y - y;
		double xSeparation = v2.x - x;
		return sqrt(ySeparation * ySeparation + xSeparation * xSeparation);
	}

	//-------------------------
	// ������: Distance �����ƽ�� 
	// ����:  �����������һ������
	// ����ֵ:  double ����ֵ��ƽ��
	inline double Vector2D::DistanceSq(const Vector2D &v2) const {
		double ySeparation = v2.y - y;
		double xSeparation = v2.x - x;
		return ySeparation * ySeparation + xSeparation * xSeparation;
	}


	//-------------------------
	// ������:  Truncate �ض�
	// ����: ���ֵ
	// ����ֵ:  -void
	inline void Vector2D::Truncate(double max) {
		if (this->Length()>max)
		{
			this->Normalize();
			*this *= max;
		}
	}


	//-------------------------
	// ������:  Refleft ��������
	// ����:  -����
	// ����ֵ:  -void
	inline void Vector2D::Reflect(const Vector2D& norm) {
		*this += 2.0 * this->Dot(norm) * norm.GetReverse();
	}


	//-------------------------
	// ������:  GetReverse ������
	// ����: -void
	// ����ֵ:  �������ķ�����
	inline Vector2D Vector2D::GetReverse()const {
		return Vector2D(-this->x, -this->y);
	}


	//-------------------------
	// ������:  Normalize ��λ������
	// ����:	-void
	// ����ֵ:  -void
	inline void Vector2D::Normalize() {
		double vector_length = this->Length();

		if (vector_length>std::numeric_limits<double>::epsilon())
		{
			this->x /= vector_length;
			this->y /= vector_length;
		}
	}

	//һЩ����Ĳ�������

	//-------------------------
	// ������:  POINTStoVector
	// ����: WinSDK�е� POINTS ת����
	// ����ֵ:  ��pͬλ�õ�Vector2D��������
	inline Vector2D POINTStoVector(const POINTS& p)
	{
		return Vector2D(p.x, p.y);
	}

	//-------------------------
	// ������:  POINTtoVector
	// ����: WinSDK�е� POINTS ת����
	// ����ֵ:  ��pͬλ�õ�Vector2D��������
	inline Vector2D POINTtoVector(const POINT& p)
	{
		return Vector2D((double)p.x, (double)p.y);
	}

	//-------------------------
	// ������:  VectorToPOINTS
	// ����: Vector2DתPoints
	// ����ֵ:  ��Vector2Dͬλ�õ�POINTS��
	inline POINTS VectorToPOINTS(const Vector2D& v)
	{
		POINTS p;
		p.x = (short)v.x;
		p.y = (short)v.y;

		return p;
	}

	//-------------------------
	// ������:  VectorToPOINT
	// ����: Vector2D����
	// ����ֵ:  ��Vector2Dͬλ�õ�POINT��
	inline POINT VectorToPOINT(const Vector2D& v)
	{
		POINT p;
		p.x = (long)v.x;
		p.y = (long)v.y;

		return p;
	}


	//-------------------------
	/// ������:  Vec2DNormalize
	/// ����: Vector2D v
	/// ����ֵ: ����һ�������ĵ�λ����
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
	/// ������:  NotInsideRegion
	/// ����: p �㣬top_left ���Ͻǣ�bot_rgt ���½�
	/// ����ֵ:  ������������ڣ��򷵻�false,���򷵻�true
	inline bool NotInsideRegion(Vector2D p,
		Vector2D top_left,
		Vector2D bot_rgt)
	{
		return (p.x < top_left.x) || (p.x > bot_rgt.x) ||
			(p.y < top_left.y) || (p.y > bot_rgt.y);
	}


	//-------------------------
	/// ������:  InsideRegion
	/// ����: p �㣬top_left ���Ͻǣ�bot_rgt ���½�
	/// ����ֵ:  ������������ڣ��򷵻�true,���򷵻�false
	inline bool InsideRegion(Vector2D p,
		Vector2D top_left,
		Vector2D bot_rgt)
	{
		return !((p.x < top_left.x) || (p.x > bot_rgt.x) ||
			(p.y < top_left.y) || (p.y > bot_rgt.y));
	}

	//----------------------
	/// ���ز�����
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

