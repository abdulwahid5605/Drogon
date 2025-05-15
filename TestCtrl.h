#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
using Callback = std::function<void(const HttpResponsePtr &)>;

// class MyController:public HttpController<MyController>
// {
//   public:
//   METHOD_LIST_BEGIN
//   ADD_METHOD_TO(MyController::greet,"/greet",Get);
//   METHOD_LIST_END
//   void greet(const HttpRequestPtr &req,std::function<void(const HttpResponsePtr &)>&& callback);
// };

// class MyController:public HttpController<MyController>
// {
//   public:
//   METHOD_LIST_BEGIN
//   ADD_METHOD_TO(MyController::greet,"/greet",Post);
//   METHOD_LIST_END
//   void greet(const HttpRequestPtr &req,std::function<void(const HttpResponsePtr &)>&& callback);
// };

// ------------------------------------------------------------------------

class MyController : public drogon::HttpController<MyController>
{
public:
  // Declare methods
  METHOD_LIST_BEGIN
  ADD_METHOD_TO(MyController::index, "/", Get);
  ADD_METHOD_TO(MyController::submit, "/submit", Post);
  ADD_METHOD_TO(MyController::list ,"/list",Get);
  ADD_METHOD_TO(MyController::remove ,"/delete/{id}",Post);
  METHOD_LIST_END

  // Method for handling POST request
  void index(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void submit(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void list(const HttpRequestPtr &req,std::function <void(const HttpResponsePtr &)>&&callback);
  void remove(const HttpRequestPtr &req,std::function <void(const HttpResponsePtr &)>&&callback,const std::string &id);

};