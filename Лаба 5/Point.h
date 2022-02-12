#pragma once
#include <iostream>
#include <stdio.h>
using namespace std;


class Point 
{
protected:
	int x;
	int y;

public:
	Point() 
	{
		cout << "Point()\n";
		x = 0;
		y = 0;
	}
	Point(int x, int y) 
	{
		cout << "Point(int x, int y)\n";
		this->x = x;
		this->y = y;
	}
	Point(const Point& example)
	{
		cout << "Point(const Point& example)\n";
		x = example.x;
		y = example.y;
	}
	virtual ~Point() 
	{
		cout << "~Point()\n";
	}

	int GetX() {
		return x;
	}
	int GetY() {
		return y;
	}

	static float Distance(Point& a, Point& b)
	{
		return (float)sqrt((b.GetX() - a.GetX()) * (b.GetX() - a.GetX()) + (b.GetY() - a.GetY()) * (b.GetY() - a.GetY()));

	}

	void SetPos(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	virtual string Classname() 
	{
		return "Point";
	}
	virtual bool IsA(string s) 
	{
		return s == "Point";
	}
	virtual void ShowMessage()
	{
		cout << "Point\n";
	}

	void virtual Move(int dx, int dy) 
	{
		x += dx;
		y += dy;
	}
};

class Point3D : public Point 
{
protected:
	int z;
public:
	Point3D()
	{
		cout << "Point3D()\n";
		z = 0;
	}
	Point3D(int x, int y, int z) : Point(x, y)
	{
		cout << "Point3D(int x, int y, int z)\n";
		this->z = z;
	}
	Point3D(const Point3D& example) : Point(example) 
	{
		cout << "Point3D(const Point3D& example)\n";
		z = example.z;
	}
	~Point3D() override 
	{
		cout << "~Point3D()\n";
	}

	int GetZ()
	{
		return z;
	}

	static float Distance(Point3D& a, Point3D& b)
	{
		return (float)sqrt((b.GetX() - a.GetX()) * (b.GetX() - a.GetX()) + (b.GetY() - a.GetY()) * (b.GetY() - a.GetY()) + (b.GetZ() - a.GetZ()) * (b.GetZ() - a.GetZ()));
	}

	string Classname() override
	{
		return "Point3D";
	}
	bool IsA(string s) override
	{
		return s == "Point3D" || Point::IsA(s);
	}
	void ShowMessage() override
	{
		cout << "Point3D\n";
	}

	void Move(int dx, int dy, int dz)
	{
		x += dx;
		y += dy;
		z += dz;
	}
};

class Point4D : public Point3D
{
protected:
	int w;
public:
	Point4D() 
	{
		cout << "Point4D()\n";
		w = 0;
	}
	Point4D(int x, int y, int z, int w) : Point3D(x, y, z)
	{
		this->w = w;
	}
	Point4D(const Point4D& example) : Point3D(example) 
	{
		w = example.w;
	}
	~Point4D() override 
	{
		cout << "~Point4D()\n";
	}

	int GetW()
	{
		return w;
	}

	string Classname() override 
	{
		return "Point4D";
	}
	bool IsA(string s) override
	{
		return s == "Point4D" || Point3D::IsA(s);
	}
	void ShowMessage() override 
	{
		cout << "Point4D\n";
	}

	void Move(int dx, int dy, int dz, int dw)
	{
		x += dx;
		y += dy;
		z += dz;
		w += dw;
	}
};