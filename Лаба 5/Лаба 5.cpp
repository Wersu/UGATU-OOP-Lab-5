#include <iostream>
#include<stdio.h>
#include "Point.h"
using namespace std;

class Base
{
public:
    int num;
    Base() 
    {
        cout << "Base()\n";
        num = 0;
    }
    Base(Base* obj) 
    {
        cout << "Base(Base* obj)\n";
        num = (*obj).num;
    }
    Base(Base& obj)
    {
        cout << "Base(Base& obj)\n";
        num = obj.num;
    }
    virtual ~Base() 
    {
        cout << "~Base()\n";
    }

    void NonVirtualLinkMethod()
    {
        cout << "Base :: NonVirtualLinkMethod()\n";
        NonVirtualSubLinkMethod();
    }
    void NonVirtualSubLinkMethod()
    {
        cout << "Base :: NonVirtualSubLinkMethod()\n";
    }

    void VirtualLinkMethod() 
    {
        cout << "Base ::VirtualLinkMethod()\n";
        VirtualSubLinkMethod();
    }
    virtual void VirtualSubLinkMethod()
    {
        cout << "Base :: VirtualSubLinkMethod()\n";
    }

    void NonVirtualMethod() 
    {
        cout << "Base :: NonVirtualMethod()\n";
    }
    virtual void VirtualMethod() 
    {
        cout << "Base :: VirtualMethod()\n";
    }
};

class Desc : public Base 
{
public:
    int k = num;
    Desc() 
    {
        cout << "Desc()\n";
        k = 0;
    }
    Desc(Desc* obj) 
    {
        cout << "Desc(Desc* obj)\n";
        k = (*obj).k;
    }
    Desc(Desc& obj) 
    {
        cout << "Desc(Desc& obj)\n";
        k = obj.k;
    }
    ~Desc() override 
    {
        cout << "~Desc()\n";
    }

    void NonVirtualSubLinkMethod()
    {
        cout << "Desc :: NonVirtualSubLinkMethod() \n";
    }

    void VirtualSubLinkMethod() override
    {
        cout << "Desc :: VirtualSubLinkMethod()\n";
    }
    void NonVirtualMethod()
    {
        cout << "Desc :: NonVirtualMethod()\n";
    }
    void VirtualMethod()
    {
        cout << "Desc :: VirtualMethod()\n";
    }
};

void PrintStaticBase(Base obj)
{
    cout << "PrintStaticBase(Base obj)\n";
}
void PrintPointerBase(Base* obj)
{
    cout << "PrintPointerBase(Base* obj)\n";
}
void PrintRefBase(Base& obj)
{
    cout << "PrintRefBase(Base& obj)\n";
}

Base GetStaticBase() 
{
    cout << endl <<"GetStaticBase" << endl;
    Base base;
    return base;
}
Base* GetPointerBase() 
{
    cout << endl << "GetPointerBase" << endl;
    Base base;
    return &base;
}

Base& GetRefBase() 
{
    cout << endl << " GetRefBase" << endl;
    Base base;
    return base;
}




void SmartPointer()
{
    //unique_ptr
    {
        unique_ptr<Point> p1(new Point(5, 10));

        unique_ptr<Point> p2 = move(p1);  //p2 = point(5, 10), p1 = empty
    }


    //shared_ptr
    {
        shared_ptr<Point> p2;
        {
            shared_ptr<Point> p1(new Point(5, 10));

            p2 = p1;         //p2 = p1 = point(5, 10)
        }
        //p1 = null, p2 = point(5, 10)
    }
}

void DefaultNOverrideMethods()
{
    Point3D test1;
    Point3D test2(5, 5, 10);

    // определения

    // перекрываемых методов
    test1.SetPos(10, 20); // наследуемый метод
    cout << "x = " << test1.GetX() << " y = " << test1.GetY() << " z = " << test1.GetZ() << endl;

    cout << "Distance = " << Point3D::Distance(test1, test2)<<endl; // перекрываемый метод

    //виртуальных методов
    test1.ShowMessage(); // наследуемый виртуальный метод (override)
    test1.SetPos(0, 0); // метод базового класса

}

void TypeCast()
{

    // реализация 
    
    // безопасного приведения типов(вручную)
    const int N = 10;
    Point* points[N];
    for (int i = 0; i < N; i++) {
        switch (rand() % 3)
        {
        case 0:
            points[i] = new Point();
            break;
        case 1:
            points[i] = new Point3D();
            break;
        case 2:
            points[i] = new Point4D();
            break;
        default:
            break;
        }
    }

    for (int i = 0; i < N; i++) {
        if (points[i]->IsA("Point3D"))
            ((Point3D*)points[i])->Move(1, 1, 1);
    }
    for (int i = 0; i < N; i++) {
        if (points[i]->Classname() == "Point3D"|| points[i]->Classname() == "Point4D")
            ((Point3D*)points[i])->Move(1, 1, 1);
    }
    
    // безопасного приведения типов(dynamic_cast)
    for (int i = 0; i < N; i++) {
        if (dynamic_cast<Point3D*>(points[i]))   //if Point => NULL
            ((Point3D*)points[i])->Move(1, 1, 1);
    }
    for (int i = 0; i < N; i++) 
        delete points[i];

}

void LinkMethods()
{
    Desc desc;
    desc.NonVirtualLinkMethod();//Вызываем метод, который вызывает не виртуальный метод
    desc.VirtualLinkMethod();//Вызываем метод, который вызывает виртуальный переопределённый метод
}

void NonVirtualMethods()
{
    Base* base = new Base();
    base->NonVirtualMethod();//Вызовится метод внутри Base
    delete base;
    Desc* desc = new Desc();
    desc->NonVirtualMethod();//Вызовится метод внутри Desc
    delete desc;
    Base* baseDesc = new Desc();
    baseDesc->NonVirtualMethod();//Вызовится метод внутри Base
    delete baseDesc;
}

void VirtualMethods()
{
    Base* base = new Base();
    base->VirtualMethod();//Вызовится метод внутри Base
    delete base;
    Desc* desc = new Desc();
    desc->VirtualMethod();//Вызовится метод внутри Desc
    delete desc;
    Base* baseDesc = new Desc();
    baseDesc->VirtualMethod();//Вызовится метод внутри Desc
    delete baseDesc;
}

void ShowBase()
{
    Base b1, b2, b3;
    PrintStaticBase(b1);
    PrintPointerBase(&b2);
    PrintRefBase(b3);
}

void GetBase()
{
    Base base1, base2, base3;

    base1 = GetStaticBase();

    base2 = GetPointerBase();     
 
    base3 = GetRefBase();       
    cout << endl;
}

int main() 
{
    setlocale(LC_ALL, "rus");
    
    cout << "DefaultNOverrideMethods" << endl;
    DefaultNOverrideMethods();

    cout << endl << endl << "TypeCast"<<endl;
    TypeCast();

    cout << endl << endl << "LinkMethods" << endl;
    LinkMethods();

    cout << endl << endl << "NonVirtualMethods" << endl;
    NonVirtualMethods();
    
    cout << endl << endl << "VirtualMethods" << endl;
    VirtualMethods();
    
    cout << endl << endl << "ShowBase" << endl;
    ShowBase();
    
    cout << endl << endl << "GetBase" << endl;
    GetBase();
}
