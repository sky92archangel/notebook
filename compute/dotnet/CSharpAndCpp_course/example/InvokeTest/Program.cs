



using System.Runtime.InteropServices;

namespace InvokeTest
{
	internal class Program
	{ 
		static void Main(string[] args)
		{
			InvokeTestC.Run();
			InvokeTestStruct.Run();
		}
	}
	 
}