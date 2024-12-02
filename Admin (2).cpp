#include "header.hpp"

Admin::Admin(string _user_name, string _password)
{
    user_name = _user_name;
    password = _password;
    is_online = false;
}

bool Admin::is_admin_online()
{
    return is_online;
}

void Admin::do_resgister(string _username, string _password)
{
    if(user_name != _username || password != _password)
    {
        cout << "Bad Request\n";
        return;
    }
    cout << "OK\n";
    is_online = true;
}

void Admin::logout()
{
    is_online = false;
    cout << "OK\n";
}