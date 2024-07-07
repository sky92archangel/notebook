 
using System;
using System.Runtime.InteropServices;

namespace InvokeTest;
 
class InvokeTestStruct
{ 
	// 定义结构体
	[StructLayout(LayoutKind.Sequential)]
	public struct PointC
	{
		public int x;
		public int y;
	}
	 

	public static void Run()
	{ 
		unsafe
		{

			[DllImport("libpoint.dll ",EntryPoint = "create_point", CallingConvention = CallingConvention.Cdecl)]
			static extern PointC* CreatePoint(int x, int y); 
			[DllImport("libpoint.dll ", EntryPoint = "print_point", CallingConvention = CallingConvention.Cdecl)]
			static extern void PrintPoint(ref PointC p);


			// 创建Point结构体实例
			PointC* pointPtr = CreatePoint(10, 20);
			try
			{

				// 定义一个managed结构体变量来保存数据
				PointC managedPoint;
				// 从指针复制数据到managed结构体 需要计算结构体内变量的数据指针位置
				managedPoint.x = Marshal.ReadInt32((nint)pointPtr, 0);
				managedPoint.y = Marshal.ReadInt32((nint)pointPtr, Marshal.SizeOf(typeof(int)));

				// 打印managed结构体数据
				Console.WriteLine($"Point coordinates: ({managedPoint.x}, {managedPoint.y})");

				// 也可以直接使用PrintPoint函数，如果它打印的是指针指向的数据
				PrintPoint(ref managedPoint); 
			}
			finally
			{
				// 由于这里使用了静态分配（静态Point变量），需要确保不会引发内存泄漏
				// 实际上，应该使用动态分配（malloc）并适当释放内存（free）

			}

		}
	}
}