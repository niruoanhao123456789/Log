#include"../log/Log.hpp"
#include<string>
#include<vector>

using namespace LogModule;

// 日志器性能测试
void bench(const std::string& loger_name, size_t thread_num, size_t msglen, size_t msg_count)
{
    // 1、获取日志器
    Logger::ptr logger = GetLogger(loger_name);
    if(logger == nullptr)
    {
        return;
    }
    std::cout<<"日志测试："<<msg_count<<"条，总大小："<< (msglen*msg_count)/1024<<" KB"<<std::endl;

    // 组织定长日志消息
    std::string msg(msglen-1,'a');  // 最后一个位置留给 \n

    // 创建指定数量的线程
    std::vector<std::thread> threads;
    std::vector<double> cost_time(thread_num);
    size_t msg_count_per_thread = msg_count / thread_num;

    std::cout << "输入线程数量: " << thread_num << std::endl;
    std::cout << "输出日志数量: " << msg_count << std::endl;
    std::cout << "输出日志大小: " << msglen * msg_count / 1024  << "KB" << std::endl;

    for(size_t i=0;i<thread_num;i++)
    {
        threads.emplace_back([&,i](){
            // 线程函数内部开始计时
            auto start = std::chrono::high_resolution_clock::now();
            // 开始循环写日志
            for(size_t j=0;j<msg_count_per_thread;j++)
            {
                logger->fatal("%s",msg.c_str());
            }
            // 线程函数内部结束计时
            auto end = std::chrono::high_resolution_clock::now();
            auto cost = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
            cost_time[i] = cost.count();
            auto avg = msg_count_per_thread / cost_time[i];
            std::cout << "线程" << i << "耗时: " << cost.count() << "s" << " 平均：" << (size_t)avg << "/s"<<std::endl;
        });
    }

    for(auto &thread : threads) 
    {
        thread.join();
    }

    // 计算总耗时
    double max_cost = 0;
    for (auto& cost : cost_time) 
    {
        max_cost = max_cost < cost ? cost : max_cost;
    }

    std::cout << "总消耗时间: " << max_cost << std::endl;
    std::cout << "平均每秒输出: " << (size_t)(msg_count / max_cost) << "条日志" << std::endl;
    std::cout << "平均每秒输出: " << (size_t)(msglen * msg_count / max_cost / 1024 / 1024) << "MB" << std::endl;
}