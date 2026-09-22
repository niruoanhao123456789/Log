#include"../log/Log.hpp"

using namespace LogModule;

void test1()
{
    std::unique_ptr<LoggerBuilder> builder = std::make_unique<LocalLoggerBuilder>();
    builder->BuildLoggerName("Async_Logger");
    builder->BUildLoggerLevel(LogLevel::Level::WARNING);
    builder->BUildLoggerSink<StdOutSink>();
    builder->BUildLoggerSink<FileSink>("./logfile/test.log");
    builder->BUildLoggerSink<RollBySizeSink>("./logfile/test.log",1024*1024);
    builder->BuildLoggerType(LoggerType::LOGGER_ASYNC);

    Logger::ptr logger = builder->Build();

    logger->debug(__FILE__,__LINE__,"%s","testing...");
    logger->error(__FILE__,__LINE__,"%s","testing...");
    logger->fatal(__FILE__,__LINE__,"%s","testing...");
    logger->infor(__FILE__,__LINE__,"%s","testing...");
    logger->warnning(__FILE__,__LINE__,"%s","testing...");
    size_t i = 0;
    while(i<1024*1024)
    {
        std::string s = "testing...";
        logger->fatal(__FILE__,__LINE__,"%s","testing...");
        i+=s.size();
    }
}

void test2()
{
    Logger::ptr logger = LoggerManager::getInstance().GetLogger("Async_Logger");
    logger->debug(__FILE__,__LINE__,"%s","testing...");
    logger->error(__FILE__,__LINE__,"%s","testing...");
    logger->fatal(__FILE__,__LINE__,"%s","testing...");
    logger->infor(__FILE__,__LINE__,"%s","testing...");
    logger->warnning(__FILE__,__LINE__,"%s","testing...");

    size_t i = 0;
    while(i<1024*1024)
    {
        std::string s = "testing...";
        logger->fatal(__FILE__,__LINE__,"%s","testing...");
        i+=s.size();
    }
}

void test3()
{
    Logger::ptr logger = LoggerManager::getInstance().GetLogger("Async_Logger");
    logger->debug("%s","testing...");
    logger->error("%s","testing...");
    logger->fatal("%s","testing...");
    logger->infor("%s","testing...");
    logger->warnning("%s","testing...");

    size_t i = 0;
    while(i<1024*1024)
    {
        std::string s = "testing...";
        logger->fatal("%s","testing...");
        i+=s.size();
    }
}

void loggerTest(const std::string &logger_name) 
{
    LogModule::Logger::ptr lp = LogModule::GetLogger(logger_name);
    assert(lp.get());
    LOGF("------------example--------------------");
    lp->debug("%s", "logger->debug");
    lp->infor("%s", "logger->info");
    lp->warnning("%s", "logger->warn");
    lp->error("%s", "logger->error");
    lp->fatal("%s", "logger->fatal");
    LOG_DEBUG(lp, "%s", "LOG_DEBUG");
    LOG_INFOR(lp, "%s", "LOG_INFO");
    LOG_WARNNING(lp, "%s", "LOG_WARN");
    LOG_ERROR(lp, "%s", "LOG_ERROR");
    LOG_FATAL(lp, "%s", "LOG_FATAL");
    LOGF("---------------------------------------");
    
    std::string log_msg = "hello world ";
    size_t count = 0;
    while(count < 1000000) {
        std::string msg = log_msg + std::to_string(count++);
        lp->error("%s", msg.c_str());
    }
}

void stream_test()
{
    std::unique_ptr<LoggerBuilder> lbp(new LogModule::GobalLoggerBuilder);
    lbp->BuildLoggerName("stream_logger");
    lbp->BUildLoggerLevel(LogModule::LogLevel::Level::DEBUG);
    lbp->BUildLoggerSink<LogModule::StdOutSink>();
    lbp->BuildLoggerType(LogModule::LoggerType::LOGGER_SYNC);
    lbp->Build();

    LOGD_STREAM() << "============= 流式输出示范(默认根日志器) =============";
    LOGD_STREAM() << "LOGD_STREAM : " << "字符串" << " " << 42 << " " << 3.14;
    LOGI_STREAM() << "LOGI_STREAM : bool=" << true << " char=" << 'x' << " ptr=" << (void*)0x1a2b3c;
    LOGW_STREAM() << "LOGW_STREAM : " << std::string("world");
    LOGE_STREAM() << "LOGE_STREAM : dec=" << 255 << " hex=" << std::hex << 255;
    LOGF_STREAM() << "LOGF_STREAM : " << 0xDEADBEEF;

    LOGD_STREAM() << "============= 流式输出示范(指定日志器stream_logger) =============";
    Logger::ptr logger = GetLogger("stream_logger");
    LOG_DEBUG_STREAM(logger) << "LOG_DEBUG_STREAM : value=" << 100;
    LOG_INFOR_STREAM(logger) << "LOG_INFOR_STREAM : " << __FILE__;
    LOG_WARNNING_STREAM(logger) << "LOG_WARNNING_STREAM : 多行测试" << std::endl << "这是第二行";
    LOG_ERROR_STREAM(logger) << "LOG_ERROR_STREAM : line=" << __LINE__;
    LOG_FATAL_STREAM(logger) << "LOG_FATAL_STREAM : end";
}

void functional_test() 
{
    std::unique_ptr<LoggerBuilder> lbp(new LogModule::GobalLoggerBuilder);
    lbp->BuildLoggerName("all_sink_logger");
    lbp->BuildLoggerFormatter("[%d][%c][%f:%l][%p] %m%n");
    lbp->BUildLoggerLevel(LogModule::LogLevel::Level::DEBUG);
    lbp->BUildLoggerSink<LogModule::StdOutSink>();
    lbp->BUildLoggerSink<LogModule::FileSink>("./logs/sync.log");
    lbp->BUildLoggerSink<LogModule::RollBySizeSink>("./logs/roll-", 10 * 1024 * 1024);
    lbp->BuildLoggerType(LogModule::LoggerType::LOGGER_ASYNC);
    lbp->Build();
    loggerTest("all_sink_logger");
}

int main()
{
    stream_test();
    // functional_test();

    return 0;
}
