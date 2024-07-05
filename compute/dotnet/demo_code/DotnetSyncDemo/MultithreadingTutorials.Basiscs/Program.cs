

using System.Diagnostics;
using System.Threading;
using System.Linq;
using System.Collections.Concurrent;


{
    demoawait demoawait = new demoawait();
    demoawait.Async();
}


void demopp()
{
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
}


void demoparallel1()
{
    var inputs = Enumerable.Range(1, 20).ToArray();
    var outputs = new int[inputs.Length];
    var sw = Stopwatch.StartNew();

    for (int i = 0; i < inputs.Length; i++)
    {
        outputs[i] = HeavyJob(inputs[i]);
    }
    Console.WriteLine($"Elapsed time:{sw.ElapsedMilliseconds}ms");
    PrintArray(outputs);

    int HeavyJob(int input)
    {
        Thread.Sleep(100);
        return input * input;
    }

    void PrintArray<T>(T[] arr)
    {
        for (int i = 0; i < arr.Length; i++)
        {
            Console.Write($"{arr[i]}\t");
        }
    }
}

void demoparallel2()
{
    var inputs = Enumerable.Range(1, 20).ToArray();
    var outputs = new int[inputs.Length];
    var sw = Stopwatch.StartNew();

    Parallel.For(0, inputs.Length, i => outputs[i] = HeavyJob(inputs[i]));
    outputs = inputs.AsParallel().Select(x => HeavyJob(x)).ToArray();

    Console.WriteLine($"Elapsed time:{sw.ElapsedMilliseconds}ms");
    PrintArray(outputs);

    int HeavyJob(int input)
    {
        Thread.Sleep(100);
        return input * input;
    }

    void PrintArray<T>(T[] arr)
    {
        for (int i = 0; i < arr.Length; i++)
        {
            Console.Write($"{arr[i]}\t");
        }
    }
}


void demojoin()
{
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

}

void demointerrupt()
{
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

}


void demosemaphore()
{
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
}


void demoqueue()

{

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
}



void demotask()
{
    var task = new Task<string>(() =>
    {
        Thread.Sleep(1500);
        return "done";
    });

    Console.WriteLine(task.Status.ToString());
    task.Start();
    // task.Status.ToString();
    Console.WriteLine(task.Status.ToString());
    Thread.Sleep(1000);
    // task.Status.ToString();
    Console.WriteLine(task.Status.ToString());
    Thread.Sleep(2000);
    // task.Status.ToString();
    Console.WriteLine(task.Status.ToString());
    task.Result.ToString();
    Console.WriteLine(task.Result.ToString());


}


class demoawait
{
    public async void Async()
    {
        Helper.PrintThreadId("Before", "Async-Before");
        await FooAsync();
        Helper.PrintThreadId("After", "Async-After");
        Console.ReadKey();
    }

    public async Task FooAsync()
    {
        Helper.PrintThreadId("Before", "FooAsync-Before");
        await Task.Delay(1000);
        Helper.PrintThreadId("After", "FooAsync-After");
        Console.ReadKey();
    }

    public class Helper
    {
        private static int index = 1;
        public static void PrintThreadId(string? message = null, string? name = null)
        {
            var title = $"{index}:{name}";
            if (!string.IsNullOrEmpty(message))
            { title += $"@{message}"; }
            Console.WriteLine(title + "\t" + Environment.CurrentManagedThreadId.ToString());
            Interlocked.Increment(ref index);
        }
    }

}

