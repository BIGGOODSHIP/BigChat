#pragma once
#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include<memory>
#include<iostream>
#include"Singleton.h"
#include<functional>
#include<map>
#include<unordered_map>
#include<json/json.h>
#include<json/json-forwards.h>
#include<boost/filesystem.hpp>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/ini_parser.hpp>
#include<queue>
#include<mutex>
#include<condition_variable>
#include<hiredis/hiredis.h>
#include<sw/redis++/redis++.h>



namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
 
enum ErrorCodes {
	Success=0,
	Error_Json=1001,	//json解析错误
	RPCFailed = 1002,	//rpc请求错误
	VarifyExpired=1003,	//验证码过期
	VarifyCodeErr=1004,	//验证码错误
	UserExist=1005,		//用户已存在
	PasswdErr=1006,		//密码错误
	EmailNotMatch=1007,	//邮箱不匹配
	PasswdUpFailed=1008,//更新密码失败
	PasswdInvalid=1009,	//密码更新失败
	TokenInvalid = 1010,	//token不合法
	UidInvalid = 1011,	//uid不合法
	CREATE_CHAT_FAILED = 1012,	//创建私聊失败
	LOAD_CHAT_FAILED = 1013,	//加载聊天记录失败



};

#define MAX_LENGTH  1024*2
//头部总长度
#define HEAD_TOTAL_LEN 4
//头部ID长度
#define HEAD_ID_LEN 2
//头部数据长度
#define HEAD_DATA_LEN 2
#define MAX_RECVQUE  10000
#define MAX_SENDQUE 1000

class Defer {
public:
	//接受一个函数对象
	Defer(std::function<void()> func) : func_(func) {}
	//析构时调用函数对象
	~Defer() {
		func_();
	}
private:
	std::function<void()> func_;
};

#define CODEPREFIX "code_"

#define USERIPPREFIX  "uip_"
#define USERTOKENPREFIX  "utoken_"
#define IPCOUNTPREFIX  "ipcount_"
#define USER_BASE_INFO "ubaseinfo_"
#define LOGIN_COUNT  "logincount"
#define NAME_INFO  "nameinfo_"
#define LOCK_PREFIX "lock_"
#define USER_SESSION_PREFIX "usession_"
#define LOCK_COUNT "lockcount"

#define LOCK_TIME_OUT 10
#define ACQUIRE_TIME_OUT 5

enum MSG_IDS {
	MSG_CHAT_LOGIN = 1005, //聊天登录请求
	MSG_CHAT_LOGIN_RSP = 1006, //聊天登录回包
	ID_SEARCH_USER_REQ = 1007, //搜索用户请求
	ID_SEARCH_USER_RSP = 1008, //搜索用户回包
	ID_ADD_FRIEND_REQ = 1009, //添加好友请求
	ID_ADD_FRIEND_RSP = 1010, //添加好友回包
	ID_NOTIFY_ADD_FRIEND_REQ = 1011,  //通知添加好友请求
	ID_AUTH_FRIEND_REQ = 1013,  //认证好友请求
	ID_AUTH_FRIEND_RSP = 1014,  //认证好友回包
	ID_NOTIFY_AUTH_FRIEND_REQ = 1015, //通知认证好友请求
	ID_TEXT_CHAT_MSG_REQ = 1017, //文本聊天消息请求
	ID_TEXT_CHAT_MSG_RSP = 1018, //文本聊天消息回包
	ID_NOTIFY_TEXT_CHAT_MSG_REQ = 1019, //通知文本聊天消息请求
	ID_NOTIFY_OFF_LINE_REQ = 1021, //通知下线请求
	ID_HEART_BEAT_REQ = 1023,      //心跳请求
	ID_HEARTBEAT_RSP = 1024,       //心跳回包
	ID_LOAD_CHAT_THREAD_REQ = 1025, //加载会话列表请求
	ID_LOAD_CHAT_THREAD_RSP = 1026, //加载会话列表回包
	ID_CREATE_PRIVATE_CHAT_REQ = 1027, //创建私聊请求
	ID_CREATE_PRIVATE_CHAT_RSP = 1028, //创建私聊回包

	ID_LOAD_CHAT_MSG_REQ = 1029, //加载聊天记录请求
	ID_LOAD_CHAT_MSG_RSP = 1030  //加载聊天记录回包
};