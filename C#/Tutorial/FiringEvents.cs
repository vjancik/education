using System;

namespace FiringEvents
{
    public delegate void eventFirer(string Message);
    class Program
    {
        public event eventFirer eventFired;
        public void FirstTrigger(string Message)
        {
            Console.WriteLine("Triggered first!");
            Console.WriteLine("Delegate - {0}",Message);
        }
        public void SecondTrigger(string Message)
        {
            Console.WriteLine("Triggered second!");
            Console.WriteLine("Delegate - {0}", Message);
        }
        static void Main(string[] args)
        {
            Program prg = new Program();
            prg.eventFired += new eventFirer(prg.FirstTrigger);
            prg.eventFired += new eventFirer(prg.SecondTrigger);
            Console.WriteLine("Fired event!");
            prg.eventFired("eventFirer");
        }
        
    }
}
