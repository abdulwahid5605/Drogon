// #include "TestCtrl.h"
// #include "json.hpp"
// #include "inja.hpp"
// using namespace std;
// using json = nlohmann::json;
// using namespace inja;

// Ye Basic Program ha Jo Controller se sirif data bhej raha
// void MyController::greet(const HttpRequestPtr &req,std::function <void(const HttpResponsePtr &)>&&callback)
// {
//     auto resp=HttpResponse::newHttpResponse();
//     resp->setContentTypeCode(CT_TEXT_PLAIN);
//     resp->setBody("Hello from Abdul!");
//     callback(resp);
// }

// Ab ik aisa program banao jismay bhai name query se pass ho aur wo page pr as a response return ho
// void MyController::greet(const HttpRequestPtr &req,function <void(const HttpResponsePtr &)> &&callback)
// {
//     string name=req->getParameter("name");
//     if(name.empty()){
//         name="Guest";
//     }

//     auto resp=HttpResponse::newHttpResponse();
//     resp->setContentTypeCode(CT_TEXT_PLAIN);
//     resp->setBody("Hello " + name + "!");
//     callback(resp);
// }

// Ab Data Html ki heading me
// void MyController::greet(const HttpRequestPtr &req,function<void(const HttpResponsePtr &)> &&callback){
//     string name=req->getParameter("name");

//     auto resp = HttpResponse::newHttpResponse();
//     resp->setContentTypeCode(CT_TEXT_HTML);
//     resp->setBody("<h1>Hi "+ name +"</h1>");
//     callback(resp);
// }

// void MyController::greet(const HttpRequestPtr &req,function<void(const HttpResponsePtr &)> &&callback){
//     Json::Value json;
//     json["message"]="Hello Abdul Wahid!";
//     auto resp=HttpResponse::newHttpJsonResponse(json);
//     callback(resp);
// }

// void MyController::greet(const HttpRequestPtr &req,std::function<void(const HttpResponsePtr &)>&&callback)
// {
//     string query=req->getParameter("name");
//     // json data;
//     // data["name"]="Abdul Wahid";
//     // string body="Hello " + query;
//     auto resp=HttpResponse::newHttpResponse();
//     resp->setContentTypeCode(CT_TEXT_PLAIN);
//     resp->setBody("Hello " + query);
//     callback(resp);
// }

// request me ik json object lena ha, usmay check krna ha kay name ki key ha ya nahi, agr ha to name kay variable me usko override krwa do
// uskay baad json ka ik variable lo aur usmay name ko store krwa kr inja kay through text return krwa do.
// void MyController::greet(const HttpRequestPtr &req,std::function<void(const HttpResponsePtr &)>&&callback)
// {
//     auto req_json=req->getJsonObject();
//     string name="Guest";
//     if(req_json && req_json->isMember("name"))
//     {
//         name=(*req_json)["name"].asString();
//     }
//     json data;
//     data["name"]=name;
//     auto resp=HttpResponse::newHttpResponse();
//     resp->setContentTypeCode(CT_TEXT_PLAIN);
//     resp->setBody(render("Hello {{name}}, Mubarak ho aapko shadi ki",data));
//     callback(resp);
// }

// void MyController::greet(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
// {
//     auto req_json = req->getJsonObject();
//     string name = "Guest";
//     string city;
//     if (req_json){
//         if (req_json->isMember("name"))
//         {
//             name = (*req_json)["name"].asString();
//         }
//         if(req_json->isMember("city"))
//         {
//             city=(*req_json)["city"].asString();
//         }
//     }

//     json data;
//     data["name"]=name;
//     data["city"]=city;
//     auto resp=HttpResponse::newHttpResponse();
//     resp->setContentTypeCode(CT_TEXT_HTML);
//     resp->setBody(render("I am {{name}} from city {{city}}",data));
//     callback(resp);
// }

// Program jo count return kray
// void MyController::greet(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
// {
//     auto req_json=req->getJsonObject();
//     int count;
//     if(req_json && req_json->isMember("users"))
//     {
//         count=(*req_json)["users"].size();
//     }
//     json data;
//     data["count"]=count;
//     auto resp=HttpResponse::newHttpJsonResponse(count);
//     callback(resp);
// }

// void MyController::greet(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
// {
//     inja::Environment env{"views"};

//     json data;
//     data["name"]="Wahid";
//     data["city"]="Karachi";
//     string body=env.render_file("profile.html",data);

//     auto resp=HttpResponse::newHttpResponse();
//     resp->setContentTypeCode(CT_TEXT_HTML);
//     resp->setBody(body);
//     callback(resp);
// }

// -----------------------------------------------------------------------------
#include "TestCtrl.h"
#include <sqlite3.h>
#include <iostream>
#include "json.hpp"
#include "inja.hpp"
using namespace std;
using json = nlohmann::json;
using namespace inja;
extern sqlite3 *db;

void MyController::submit(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    string name = req->getParameter("name");
    string city = req->getParameter("city");

    const char *sql = "INSERT INTO users (name, city) VALUES (?,?)";

    sqlite3_stmt *stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, city.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_DONE)
        {
            auto resp = HttpResponse::newHttpResponse();
            resp->setBody("User Information Submitted Successfully");
            callback(resp);
        }
        else
        {
            auto resp = HttpResponse::newHttpResponse();
            resp->setBody("Failed to submit data");
            resp->setStatusCode(k500InternalServerError);
            callback(resp);
        }
        sqlite3_finalize(stmt);
    }
    else
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("SQL Error: Unable to prepare statement.");
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
    }
}

void MyController::index(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    inja::Environment env{"views"};

    json data;
    data["name"] = "Wahid";
    data["city"] = "Karachi";
    string body = env.render_file("form.html", data);

    auto resp = HttpResponse::newHttpResponse();
    resp->setContentTypeCode(CT_TEXT_HTML);
    resp->setBody(body);
    callback(resp);
}

void MyController::list(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    inja::Environment env{"views"};

    const char *query = "SELECT id, name, city FROM users";

    sqlite3_stmt *stmt = nullptr;

    json users = json::array();

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int id = sqlite3_column_int(stmt, 0);
            const char *name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            const char *city = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));

            json user;
            user["id"] = id;
            user["name"] = name;
            user["city"] = city;
            users.push_back(user);
        }
        sqlite3_finalize(stmt);
        json data;
        data["users"] = users;
        string html = env.render_file("list.html", data);
        auto resp = HttpResponse::newHttpResponse();
        resp->setContentTypeCode(CT_TEXT_HTML);
        resp->setBody(html);
        callback(resp);
    }
    else
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("Error");
        callback(resp);
    }
}

void MyController::remove(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, const std::string &id)
{
    int userId = stoi(id);
    const char *query = "DELETE FROM users WHERE id = ?";

    sqlite3_stmt *stmt = nullptr;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr)==SQLITE_OK)
    {
        sqlite3_bind_int(stmt, 1, userId);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        auto resp = HttpResponse::newRedirectionResponse("/list");
        callback(resp);
        return;
    }
    else
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("Error");
        callback(resp);
    }
}
