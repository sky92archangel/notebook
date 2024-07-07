 
using System;
using System.Runtime.InteropServices;

namespace  InvokeTest ;

class InvokeTestC()
{
	[DllImport("libtest", CallingConvention = CallingConvention.Cdecl)]
	static extern int HelloC();
	[DllImport("libtest", CallingConvention = CallingConvention.Cdecl)]
	static extern int SumC(int a, int b);

	public static void Run()
	{
		Console.WriteLine("Hello, World!\n");
		HelloC();
		Console.WriteLine("\n");
		int res = SumC(47, 87);
		Console.WriteLine("\n" + res + "\n");
	}
}