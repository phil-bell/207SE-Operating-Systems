using System;

namespace nameBlock
{
    class Program
    {
        static void Main(string[] args)
        {
            string name = "Philip Bell";
            int nameLength = name.Length;
            for (int i = 0; i < nameLength; i += 2)
            {
                char temp1 = name[i];
                if (i < nameLength-1)
                {
                    char temp2 = name[i + 1];
                    Console.Write(temp1);
                    Console.WriteLine(temp2);
                }
                else
                {
                    Console.WriteLine(temp1);
                }

            }
        }
    }
}
