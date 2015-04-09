using System;

public class Customer
{
    private int m_id = -1;
    //public int ID { get; set; } //auto implemented property which does pretty much the same thing as the default one but with less coding :)
    public int ID // an ID property of class Customer
    {
        get
        {
            return m_id; //returning m_id when the program calls for Customer.ID
        }
        set
        {
            m_id = value; //assigning a value to m_id when the program assigns a value to Customer.ID
        }
    }

    private string m_name = string.Empty;
    //public string Name { get; set; }
    public string Name
    {
        get
        {
            return m_name;
        }
        set
        {
            m_name = value; //to make a property read only dont include set{} and to make it write only dont include get{}
        }
    }
}

public class CustomerManagerWithProperties
{
    public static void Main()
    {
        Customer cust = new Customer();

        cust.ID = 1;
        cust.Name = "Amelio Rosales";

        Console.WriteLine(
                "ID: {0}, Name: {1}",
                cust.ID,
                cust.Name);

        Console.ReadKey();
    }
}

// OVERLOADED INDEXERS

/*
class OvrIndexer
{
    private string[] myData;
    private int         arrSize;

    public OvrIndexer(int size)
    {
        arrSize = size;
        myData = new string[size];

        for (int i=0; i < size; i++)
        {
            myData[i] = "empty";
        }
    }

    public string this[int pos] //an indexer - array form of properties
    {
        get
       {
            return myData[pos];
        }
        set
       {
            myData[pos] = value;
        }
    }
    public string this[string data] //another indexer for the same object making it an overloaded indexer
    {
        get
       {
            int count = 0;
            for (int i=0; i < arrSize; i++)
            {
                if (myData[i] == data)
                {
                    count++;
                }
            }
            return count.ToString();
        }
        set
       {
            for (int i=0; i < arrSize; i++)
            {
                if (myData[i] == data)
                {
                    myData[i] = value;
                }
            }
        }
    }

    static void Main(string[] args)
    {
        int size = 10;
        OvrIndexer myInd = new OvrIndexer(size);

        myInd[9] = "Some Value";
        myInd[3] = "Another Value";
        myInd[5] = "Any Value";

        myInd["empty"] = "no value";

        Console.WriteLine("\nIndexer Output\n");

        for (int i=0; i < size; i++)
        {
            Console.WriteLine("myInd[{0}]: {1}", i, myInd[i]); //prints out all the objects in the array
        }

        Console.WriteLine("\nNumber of \"no value\" entries: {0}", myInd["no value"]); //counts the number of "no value" strings in the array
    }
}
*/