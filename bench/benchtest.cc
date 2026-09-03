#include"Bench.hpp"

using namespace LogModule;

void sync_bench_thread_log(size_t thread_count, size_t msg_count, size_t msglen)
{
    static int num = 1;
    std::string logger_name = "sync_bench_logger" + std::to_string(num++);
    LOGI("************************************************");
    LOGI("同步日志测试: %d threads, %d messages", thread_count, msg_count);

    std::shared_ptr<LoggerBuilder> lbp(new GobalLoggerBuilder);
    lbp->BuildLoggerName(logger_name);
    lbp->BuildLoggerFormatter("%m");
    lbp->BUildLoggerSink<FileSink>("./logs/sync.log");
    lbp->BuildLoggerType(LoggerType::LOGGER_SYNC);
    lbp->Build(); 
    bench(logger_name, thread_count, msglen, msg_count);
    LOGI("************************************************");
}

void async_bench_thread_log(size_t thread_count, size_t msg_count, size_t msglen)
{
    static int num = 1;
    std::string logger_name = "async_bench_logger" + std::to_string(num++);
    LOGI("************************************************");
    LOGI("异步日志测试: %d threads, %d messages", thread_count, msg_count);

    std::shared_ptr<LoggerBuilder> lbp(new GobalLoggerBuilder);
    lbp->BuildLoggerName(logger_name);
    lbp->BuildLoggerFormatter("%m");
    lbp->BUildLoggerSink<FileSink>("./logs/async.log");
    lbp->BuildLoggerType(LoggerType::LOGGER_ASYNC);
    lbp->Build(); 
    bench(logger_name, thread_count, msglen, msg_count);
    LOGI("************************************************");
}

void bench_test() {
    /*异步日志输出*/
    async_bench_thread_log(1, 1000000, 100);
    async_bench_thread_log(5, 1000000, 100);
    // 同步写日志
    sync_bench_thread_log(1, 1000000, 100);
    sync_bench_thread_log(5, 1000000, 100);
}

int main()
{
    bench_test();

    return 0;
}