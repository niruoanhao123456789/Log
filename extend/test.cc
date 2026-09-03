#include"../log/Log.hpp"

using namespace LogModule;

void test1()
{
    std::unique_ptr<LoggerBuilder> lbp(new LogModule::GobalLoggerBuilder);
    lbp->BuildLoggerName("TimeLogger");
    lbp->BUildLoggerLevel(LogModule::LogLevel::Level::DEBUG);
    lbp->BUildLoggerSink<LogModule::RollByTimeSink>("./logs/",TimeGap::GAP_DAY);
    lbp->BUildLoggerSink<LogModule::RollByTimeSink>("./logs/",TimeGap::GAP_HOUR);
    lbp->BUildLoggerSink<LogModule::RollByTimeSink>("./logs/",TimeGap::GAP_MINITUE);
    lbp->BUildLoggerSink<LogModule::RollByTimeSink>("./logs/",TimeGap::GAP_SECOND);
    lbp->BuildLoggerType(LogModule::LoggerType::LOGGER_ASYNC);
    lbp->Build();

    LOG_DEBUG(GetLogger("TimeLogger"),"%s","testing ...");
    LOG_INFOR(GetLogger("TimeLogger"),"%s","testing ...");
    LOG_WARNNING(GetLogger("TimeLogger"),"%s","testing ...");
}

int main()
{
    test1();

    return 0;
}