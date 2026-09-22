#include<iostream>
#include<json/json.h>
#include<json/json-forwards.h>
#include"CServer.h"
#include"ConfigMgr.h"
#include"RedisMgr.h"

void TestRedisMgr() {
    assert(RedisMgr::GetInstance()->Set("blogwebsite", "llfc.club"));
    std::string value = "";
    assert(RedisMgr::GetInstance()->Get("blogwebsite", value));
    assert(RedisMgr::GetInstance()->Get("nonekey", value) == false);
    assert(RedisMgr::GetInstance()->HSet("bloginfo", "blogwebsite", "llfc.club"));
    assert(RedisMgr::GetInstance()->Set("blodsdasadadsdasde", "bhfffff"));
    assert(RedisMgr::GetInstance()->HGet("bloginfo", "blogwebsite") != "");
    assert(RedisMgr::GetInstance()->Set("blodsdasadadsdasde", "bhfffff"));
    assert(RedisMgr::GetInstance()->ExistsKey("bloginfo"));
    assert(RedisMgr::GetInstance()->Del("bloginfo"));
    assert(RedisMgr::GetInstance()->Del("bloginfo"));
    assert(RedisMgr::GetInstance()->ExistsKey("bloginfo") == false);
    assert(RedisMgr::GetInstance()->LPush("lpushkey1", "lpushvalue1"));
    assert(RedisMgr::GetInstance()->LPush("lpushkey1", "lpushvalue2"));
    assert(RedisMgr::GetInstance()->LPush("lpushkey1", "lpushvalue3"));
    assert(RedisMgr::GetInstance()->RPop("lpushkey1", value));
    assert(RedisMgr::GetInstance()->RPop("lpushkey1", value));
    assert(RedisMgr::GetInstance()->LPop("lpushkey1", value));
    assert(RedisMgr::GetInstance()->LPop("lpushkey2", value) == false);
}

using namespace sw::redis;

void TestRedis()
{
    try
    {
        // 连接串格式：tcp://ip:port?password=xxx
        Redis redis("tcp://127.0.0.1:6380?password=123456");
        std::cout << "Connect to redisServer Success\n";

        // 1. SET stest1 value1
        std::string command1 = "set stest1 value1";
        auto set_ret = redis.set("stest1", "value1");
        if (!set_ret)
        {
            std::cout << "Failed to execute command[" << command1 << "]\n";
            return;
        }
        std::cout << "Succeed to execute command[" << command1 << "]\n";

        // 2. strlen stest1
        std::string command2 = "strlen stest1";
        auto len_opt = redis.strlen("stest1");
        if (!len_opt)
        {
            std::cout << "Failed to execute command[" << command2 << "]\n";
            return;
        }
        long long length = len_opt;
        std::cout << "The length of 'stest1' is " << length << ".\n";
        std::cout << "Succeed to execute command[" << command2 << "]\n";

        // 3. get stest1
        std::string command3 = "get stest1";
        auto val_opt = redis.get("stest1");
        if (!val_opt)
        {
            std::cout << "Failed to execute command[" << command3 << "]\n";
            return;
        }
        std::string val = val_opt.value();
        std::cout << "The value of 'stest1' is " << val << "\n";
        std::cout << "Succeed to execute command[" << command3 << "]\n";

        // 4. get stest2（key不存在）
        std::string command4 = "get stest2";
        auto nil_opt = redis.get("stest2");
        if (nil_opt)
        {
            std::cout << "Failed to execute command[" << command4 << "]\n";
            return;
        }
        std::cout << "Succeed to execute command[" << command4 << "]\n";
    }
    catch (const Error& e)
    {
        // 捕获所有网络、认证、redis服务返回错误（等价hiredis的c->err / reply错误）
        std::cout << "Redis error: " << e.what() << "\n";
    }
}

int main()
{
    TestRedisMgr();
	//TestRedis();
	auto& gCfgMgr = ConfigMgr::GetInstance();
    std::string gate_port_str = gCfgMgr["GateServer"]["Port"];
    unsigned short gate_port = atoi(gate_port_str.c_str());

    try
    {
        unsigned short port = static_cast<unsigned short>(8080);
        net::io_context ioc{ 1 };
        boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
        signals.async_wait([&ioc](const boost::system::error_code& error, int signal_number) {

            if (error) {
                return;
            }
            ioc.stop();
            });
        std::make_shared<CServer>(ioc, port)->Start();
		std::cout << "Server is running on port " << port << std::endl;
        ioc.run();
    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}