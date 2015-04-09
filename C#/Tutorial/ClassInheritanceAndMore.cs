using System;

/*public class parentClass
{
    public parentClass()
    {
        Console.WriteLine("Parent Constructor.");
    }

    public void print()
    {
        Console.WriteLine("I'm a Parent Class.");
    }
}

public class childClass : parentClass // childClass extends (:) parentClass
{
    public childClass()
    {
        Console.WriteLine("Child Constructor.");
    }
    static void Main(string[] args)
    {
        childClass child = new childClass(); //child class constructor, runs parentClass constructor first, then childClass constructor
        child.print(); //child class has access to parentClass public/protected methods
        Console.ReadLine();
    }
}*/

public class Parent
{
    string parentString;
    public Parent()
    {
        Console.WriteLine("Parent Constructor.");
    }
    public Parent(string myString)
    {
        parentString = myString;
        Console.WriteLine(parentString);
    }
    public void print()
    {
        Console.WriteLine("I'm a Parent Class.");
    }
}

public class Child : Parent
{
    public Child() : base("From Derived") //default child constructor calling Parent(string) constructor instead, using base
    {
        Console.WriteLine("Child Constructor.");
    }
    public new void print()
    {
        base.print(); // calling Parent.print() method using base.
        Console.WriteLine("I'm a Child Class.");
    }
    public static void Main()
    {
        Child child = new Child();
        child.print();
        ((Parent)child).print(); // explicit Parent.print() calling from a child object
    }
}

//!! override methods (of derived classes) can override virtual methods (of parent classes) at runtime (polymorphism)
