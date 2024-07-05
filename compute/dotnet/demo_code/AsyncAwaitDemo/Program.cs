


using System;

namespace AsyncAwaitDemo
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            // See https://aka.ms/new-console-template for more information
            Console.WriteLine("Hello, World!");

            DownLoadHandler handler = new DownLoadHandler();
            handler.IOBendDownLoad();

            Console.WriteLine("log0: "+handler.text);
            Thread.Sleep(10000);
            Console.WriteLine("log1: "+handler.text);


        }
    }

}
