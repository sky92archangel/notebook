# C# 多线程和异步

[TOC]

## 多线程

### 概念和示例

线程为最小单位，进程中有一个或多个线程；

用于批量重复任务同时进行，尤其是每个任务耗时较多；

不同任务希望同时进行互不干扰，又对个后台线程需要轮询操作；

线程池，一个预先创建的线程，异步编程默认使用线程池

线程安全，两个线程同时改变相同位置的数据时，需要排先后，需要加锁；



如下代码两段，加锁前后明显区别：多个线程争抢一个数据时会出现部分线程输入旧数据，就会出现奇怪不稳定的结果；

```c#
using System;
using System.Threading;

//------------------------------------ 
int total = 10_000;
int count = 0;

var thread1 = new Thread(TheadMethod);
var thread2 = new Thread(TheadMethod); 
thread1.Start();
thread2.Start(); 
thread1.Join();
thread2.Join();

Console.WriteLine($"Count:{count}");

void TheadMethod()
{
    for (int i = 0; i < total; i++)
    {
        count++;
    }
} 
//------------------------------------
/* 

sky92@LAPTOP-R2U8GJ9H MINGW64 /d/NOTE/linux-notebook/编程_专项笔记/dotnet/DotnetSyncDemo (master)
$ dotnet.exe build
MSBuild version 17.6.3+07e294721 for .NET
  正在确定要还原的项目…
  所有项目均是最新的，无法还原。
  MultithreadingTutorials.Basiscs -> D:\NOTE\linux-notebook\编程_专项笔记\dotnet
  \DotnetSyncDemo\MultithreadingTutorials.Basiscs\bin\Debug\net7.0\Multith 
  readingTutorials.Basiscs.dll

已成功生成。
    0 个警告
    0 个错误

已用时间 00:00:00.89

sky92@LAPTOP MINGW64 /d/NOTE/dotnet/DotnetSyncDemo (master)
$ ./MultithreadingTutorials.Basiscs/bin/Debug/net7.0/MultithreadingTutorials.Basiscs.exe 
Hello, World!
Count:13496

sky92@LAPTOP MINGW64 /d/NOTE/dotnet/DotnetSyncDemo (master)
$ ./MultithreadingTutorials.Basiscs/bin/Debug/net7.0/MultithreadingTutorials.Basiscs.exe
Hello, World!
Count:20000

sky92@LAPTOP MINGW64 /d/NOTE/dotnet/DotnetSyncDemo (master)
$ ./MultithreadingTutorials.Basiscs/bin/Debug/net7.0/MultithreadingTutorials.Basiscs.exe
Hello, World!
Count:18500 
*/ 

```

加锁后，当数据被当前线程完成操作后才可被其他线程操作，保证同步机制；

```C#


using System;
using System.Threading;
 
int total = 10_000;
int count = 0;
object lockObj = new object();//创建锁
 
var thread1 = new Thread(TheadMethod);
var thread2 = new Thread(TheadMethod); 
thread1.Start();
thread2.Start(); 
thread1.Join();
thread2.Join();

Console.WriteLine($"Count:{count}");

void TheadMethod()
{
    for (int i = 0; i < total; i++)
    {
        //启用锁
        lock (lockObj)
            count++;
    }
} 

/*
sky92@LAPTOP MINGW64 /d/NOTE/dotnet/DotnetSyncDemo (master)
$ ./MultithreadingTutorials.Basiscs/bin/Debug/net7.0/MultithreadingTutorials.Basiscs.exe 
Hello, World!
Count:20000

sky92@LAPTO MINGW64 /d/NOTE/dotnet/DotnetSyncDemo (master)
$ ./MultithreadingTutorials.Basiscs/bin/Debug/net7.0/MultithreadingTutorials.Basiscs.exe 
Hello, World!
Count:20000 
*/
```



为了线程安全，采用同步机制和原子操作;

同步机制，线程操作顺序和互斥访问，lock就是互斥锁；

原子操作，执行过程无法中断，要么完成操作，要么不操作；

如下为dotnet自带底层原子操作例子：

```C#
using System;
using System.Threading;
  
int total = 10_000;
int count = 0;  

var thread1 = new Thread(TheadMethod);
var thread2 = new Thread(TheadMethod); 
thread1.Start();
thread2.Start(); 
thread1.Join();
thread2.Join();

Console.WriteLine($"Count:{count}");

void TheadMethod()
{
    for (int i = 0; i < total; i++)
    {
       //库自带自增原子操作
       Interlocked.Increment(ref count);
    }
} 
```



dotnet带有很多多线程方法

Parallel    For ForEach Invoke  

PLINQ   AsParallel 并行化  AsSquential顺序化     AsOrdered保证并行时顺序OK



```c#
using System.Diagnostics;
using System.Threading;
using System.Linq; 

var inputs = Enumerable.Range(1, 20).ToArray();
var outputs = new int[inputs.Length];
var sw = Stopwatch.StartNew();
 
for (int i = 0; i < inputs.Length; i++)
{
    outputs[i] = HeavyJob(inputs[i]);
}
Console.WriteLine($"Elapsed time:{sw.ElapsedMilliseconds}ms");
  
int HeavyJob(int input)
{
    Thread.Sleep(100);
    return input * input;
}  

/*
sky92@LAPTOP MINGW64 /d/NOTE/dotnet/DotnetSyncDemo (master)
$ ./MultithreadingTutorials.Basiscs/bin/Debug/net7.0/MultithreadingTutorials.Basiscs.exe 
Elapsed time:2178ms

sky92@LAPTOP MINGW64 /d/NOTE/dotnet/DotnetSyncDemo (master)
$ ./MultithreadingTutorials.Basiscs/bin/Debug/net7.0/MultithreadingTutorials.Basiscs.exe 
Elapsed time:2178ms 
*/
```

使用并行效果：

```C#
using System.Diagnostics;
using System.Threading;
using System.Linq; 

var inputs = Enumerable.Range(1, 20).ToArray();
var outputs = new int[inputs.Length];
var sw = Stopwatch.StartNew();

//Parallel并行方法
Parallel.For(0, inputs.Length, i => outputs[i] = HeavyJob(inputs[i]));
//PLINQ方法
//outputs = inputs.AsParallel().AsOrdered().Select(x=>HeavyJob(x)).ToArray(); 

Console.WriteLine($"Elapsed time:{sw.ElapsedMilliseconds}ms"); 

int HeavyJob(int input)
{
    Thread.Sleep(100);
    return input * input;
} 
/*
sky92@LAPTOP MINGW64 /d/NOTE/dotnet/DotnetSyncDemo (master)
$ ./MultithreadingTutorials.Basiscs/bin/Debug/net7.0/MultithreadingTutorials.Basiscs.exe 
Elapsed time:233ms 

sky92@LAPTOP MINGW64 /d/NOTE/dotnet/DotnetSyncDemo (master)
$ ./MultithreadingTutorials.Basiscs/bin/Debug/net7.0/MultithreadingTutorials.Basiscs.exe 
Elapsed time:226ms 
*/
```



### 线程

创建，传入ThreadStart委托，可配置线程，是否为后台线程；调用Thread.Start方法，可传参；

终止，JOIN方法，等待子线程运行时阻塞主线程，全部子线程完成后 继续JOIN后的主线程代码；

```C#
using System.Diagnostics;
using System.Threading;
using System.Linq; 

var th = new Thread(() =>
{
    for (int i = 0; i < 20; i++)
    {
        Thread.Sleep(200);
        Console.WriteLine("Thread is still running ...");
    }
    Console.WriteLine("Thread is finished!");
})
{ IsBackground = true, Priority = ThreadPriority.Normal };//可配置的线程
th.Start();
Console.WriteLine("in main thread , waiting for thread to finish ..");
th.Join();
Console.WriteLine("Done");
```

可使用打断，提前中断子线程；

要注意被打断的线程中不能够带有while(true)空轮询，若必须使用，则内部必须带有sleep(0)

```C#
using System.Diagnostics;
using System.Threading;
using System.Linq; 

var th = new Thread((obj) =>
{
    try
    {
        for (int i = 0; i < 20; i++)
        {
            Thread.Sleep(200);
            Console.WriteLine("Thread is still running ...");
        }
    }
    catch (ThreadInterruptedException)
    { }
    finally
    {
        Console.WriteLine("Thread is finished!");
    }
})
{ IsBackground = true, Priority = ThreadPriority.Normal };//可配置的线程
th.Start();
Console.WriteLine("in main thread , waiting for thread to finish ..");
th.Interrupt();
th.Join();
Console.WriteLine("Done");
```



挂起和恢复方法，采用锁和信号量

```
Mutex  互斥锁 进程间共享   禁止一个应用多开
lock&Monitor	lock底层为Monitor
Semaphore  旗语 线程同步
WaitHandle ManualResetEvent AutoResetEvent 信号量
ReaderWriteLock  并行读-顺序写 读写之间互斥
```



当需要限制并行线程的数量，降低CPU和网络压力可采用旗语

```C#

using System.Diagnostics;
using System.Threading;
using System.Linq; 

var inputs = Enumerable.Range(1, 20).ToArray();
var outputs = new int[inputs.Length];
var sw = Stopwatch.StartNew();
var semaphore = new Semaphore(3, 5);//起始3通道，最高5通道
outputs = inputs.AsParallel().Select(x => HeavyJob(x)).ToArray();
Console.WriteLine($"Elapsed time:{sw.ElapsedMilliseconds}ms");
PrintArray(outputs);
int HeavyJob(int input)
{
    semaphore.WaitOne();//等待
    Thread.Sleep(300);
    semaphore.Release();//释放
    return input * input;
}
void PrintArray<T>(T[] arr)
{
    for (int i = 0; i < arr.Length; i++)
    {
        Console.Write($"{arr[i]}\t");
    }
}
```

轻量级

```
ReaderWriteLockSlim
SemaphoreSlim
ManualResetEventSlim
```

默认提供的函数

```
Lazy
ConcurrentBag	线程安全的集合
ConcurrentStack
ConcurrentQueue
ConcurrentDictionary
BlockingCollection  生产消费模型
Channel		通道
Interlocked	原子操作
PeriodicTimer	
```



预制的线程安全的队列

```C#
using System.Collections.Concurrent;
using System.Diagnostics;
using System.Threading;
using System.Linq; 

var queue = new ConcurrentQueue<int>();
var producer = new Thread(AddNumbers);
var consumer1 = new Thread(ReadNumbers);
var consumer2 = new Thread(ReadNumbers);
producer.Start();
consumer1.Start();
consumer2.Start();
producer.Join();
consumer1.Interrupt();
consumer2.Interrupt();
consumer1.Join();
consumer2.Join();

void AddNumbers()
{
    for (int i = 0; i < 20; i++)
    {
        Thread.Sleep(20);
        queue.Enqueue(i);
    }
}
void ReadNumbers()
{
    try
    {
        while (true)
        {
            if (queue.TryDequeue(out var res))
            {
                Console.WriteLine(res);
            }
            Thread.Sleep(1);
        }
    }
    catch (System.Exception)
    {
        Console.WriteLine("Thread interrupted");
    }
}
```





## 异步编程

### 概念

异步不一定多线程  携程也可能异步，异步默认使用线程池，多线程常常阻塞 ，异步不要求阻塞；

多线程适用于CPU密集和长时间运行任务，线程的创建销毁开销大，提供底层控制，不利于传参和返回，多线程代码书写繁琐；

异步适合IO密集型操作，数量大短暂小任务，避免线程阻塞，提高系统相应；

### 异步任务TASK

包含异步任务状态，异步任务开启后不会阻塞，其借助线程池在其他线程运行，得到结果后返回先前状态；

```C#

using System.Diagnostics;
using System.Threading;
using System.Linq; 

var task = new Task<string>(() =>
{
    Thread.Sleep(1500);
    return "done";
});

Console.WriteLine(task.Status.ToString() );
task.Start();
// task.Status.ToString();
Console.WriteLine(task.Status.ToString() );
Thread.Sleep(1000);
// task.Status.ToString();
Console.WriteLine(task.Status.ToString() );
Thread.Sleep(2000);
// task.Status.ToString();
Console.WriteLine(task.Status.ToString() );
task.Result.ToString();
Console.WriteLine(task.Result.ToString() );

/*
sky92@LAPTOP MINGW64 /d/NOTE/dotnet/DotnetSyncDemo (master)
$ ./MultithreadingTutorials.Basiscs/bin/Debug/net7.0/MultithreadingTutorials.Basiscs.exe 
Created
WaitingToRun
Running
RanToCompletion
done
*/
```



### Async和Task

被await的函数未必一定是async标记的，只要其返回的是task即可；

具有async标记的函数体内部可以使用await关键字调用其他函数；

await会等待异步任务；

```C#
public async void Async()
{
    Helper.PrintThreadId("Before","Async-Before");
    await FooAsync();
    Helper.PrintThreadId("After","Async-After");
}
public async Task FooAsync()
{
    Helper.PrintThreadId("Before","FooAsync-Before");
    await Task.Delay(10);
    Helper.PrintThreadId("After","FooAsync-After");
}
public class Helper
{
    private static int index = 1;
    public static void PrintThreadId(string? message = null, string? name = null)
    {
        var title = $"{index}:{name}";
        if (!string.IsNullOrEmpty(message))
        { title += $"@{message}"; }
        Console.WriteLine(title+"\t"+Environment.CurrentManagedThreadId.ToString());
        Interlocked.Increment(ref index);
    }
}
```

等待任务返回的并非原来线程，而是另一个线程开始接班

















































