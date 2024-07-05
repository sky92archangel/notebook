
// using System.Collections.Generic;
using System.Diagnostics;


namespace AsyncAwaitDemo
{
    class DownLoadHandler
    {
        public string text = string.Empty;

        private readonly IEnumerable<string> webSites = new string[]
        {
            "https://www.zhihu.com",
            "https://www.weibo.com",
            "https://docs.microsoft.com",
            "https://docs.microsoft.com/azure",
            "https://docs.microsoft.com/aspnet/core",
            "https://docs.microsoft.com/dotnet",
        };

        private readonly HttpClient httpClient = new HttpClient();


        //==================================================================
        //同步
        public void SyncDownLoad()
        {
            text = string.Empty;
            var stopwatch = Stopwatch.StartNew();
            DownloadWebsitesSync();
            text += $"Elapsed time:{stopwatch.Elapsed}{Environment.NewLine}";
        }

        private void DownloadWebsitesSync()
        {
            foreach (var site in webSites)
            {
                var result = DownloadWebsiteSync(site);
                ReportResult(result);
            }
        }
        //==================================================================
        //异步和并发   推荐非 IO bound 即CPU用于计算的程序使用
        public async void AsyncDownLoad()
        {
            text = string.Empty;
            var stopwatch = Stopwatch.StartNew();
            await DownloadWebsitesAsync();
            text += $"Elapsed time:{stopwatch.Elapsed}{Environment.NewLine}";
        }

        private async Task DownloadWebsitesAsync()
        {
            List<Task<string>> tasks = new List<Task<string>>();
            foreach (var site in webSites)
            {
                //每次循环增加一个线程开始跑 不等待当前线程继续下一个循环
                tasks.Add(Task.Run(() => DownloadWebsiteSync(site)));
            }
            // 阻塞 直到列表内所有任务完成执行该操作
            var results = await Task.WhenAll(tasks);
            ReportResult(string.Join('\n', results));

        }

        //==================================================================
        //io bound 系统自带多线程
        public async void IOBendDownLoad()
        {
            text = string.Empty;
            var stopwatch = Stopwatch.StartNew();
            await DownloadWebsitesIOAsync();
            text += $"Elapsed time:{stopwatch.Elapsed}{Environment.NewLine}";
        }
        private async Task DownloadWebsitesIOAsync()
        {
            List<Task<string>> tasks = new List<Task<string>>();
            foreach (var site in webSites)
            { 
                tasks.Add(DownloadWebsiteIOSync(site));
            }

            // 阻塞 直到列表内所有任务完成执行该操作  ConfigureAwait用于控制是否返回原有线程   UI类型的程序必须返回到原线程  如果是库的功能 建议fal se
            var results = await Task.WhenAll(tasks).ConfigureAwait(false);

            ReportResult(string.Join('\n', results));

        }


        //==================================================================
        //基础功能
        private string DownloadWebsiteSync(string url)
        {
            var response = httpClient.GetAsync(url).GetAwaiter().GetResult();
            var responsePayloadBytes = response.Content.ReadAsByteArrayAsync().GetAwaiter().GetResult();

            return $"Finish downloading data fram{url}. Total bytes returned  {responsePayloadBytes.Length}.{Environment.NewLine}";
        }

        private void ReportResult(string result)
        {
            text += result;
        }


        //
        private async Task<string> DownloadWebsiteIOSync(string url)
        {
            var response = await httpClient.GetAsync(url);
            var responsePayloadBytes = await response.Content.ReadAsByteArrayAsync();

            return $"Finish downloading data fram{url}. Total bytes returned  {responsePayloadBytes.Length}.{Environment.NewLine}";
        }


    }



}