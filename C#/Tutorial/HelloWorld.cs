using System;

namespace Lesson1 //solution name (progrma name)
{
    class Program //logical class name
    {
        static void Main(string[] args) //Main method of main class
        {
            //decide:
            Console.WriteLine("Hello world!"); //basic output
            Console.WriteLine("Whats your name?");
            Console.WriteLine("My name is {0}.", Console.ReadLine()); //dynamic input
            string myInput = Console.ReadLine();
            int myInt = Int32.Parse(myInput); //streaming string into integer EPIIIIC
            Console.WriteLine("{0}", myInt);
            string[] names = { "Cheryl", "Joe", "Matt", "Robert" };
            foreach (string person in names) // foreach pozname
            {
                Console.WriteLine("{0} ", person);
            }
            outputClass oCls = new outputClass("Nice string there man...");
            oCls.printString();
            Console.ReadLine(); //basic cin.get();
            //goto decide; //loop refference
        }
    }

    class outputClass
    {
        string outputString;
        public outputClass(string inputString) //constructor - same name as class name , destructor same as in C++
        {
            outputString = inputString; //class member initialization
        }
        public outputClass() : this("Default Constructor String") { } //default constructor - zavola constructor ktory ocakava parameter string
        public void printString() //public method
        {
            Console.WriteLine("{0}", outputString);
        }
    }
}
