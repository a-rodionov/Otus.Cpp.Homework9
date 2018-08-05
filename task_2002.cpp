//http://acm.timus.ru/problem.aspx?space=1&num=2002

#include <iostream>
#include <map>
#include <set>
 
int main()
{  
  std::map<std::string, std::string> users;
  std::set<std::string> sessions;
  size_t count;
  std::string cmd, username, password;

  std::ios::sync_with_stdio(false);

  std::cin >> count;
  for(auto i{0}; i < count; ++i) {
    std::cin >> cmd;
    if("register" == cmd) {
      std::cin >> username;
      std::cin >> password;
      if(users.cend() == users.find(username)) {
        users[username] = password;
        std::cout << "success: new user added\n";
      }
      else
        std::cout << "fail: user already exists\n";
    }
    else if("login" == cmd) {
      std::cin >> username;
      std::cin >> password;
      auto user = users.find(username);
      if(users.cend() == user) {
        std::cout << "fail: no such user\n";
      }
      else if(password != user->second) {
        std::cout << "fail: incorrect password\n";
      }
      else if(sessions.cend() == sessions.find(username)) {
        sessions.insert(username);
        std::cout << "success: user logged in\n";
      }
      else
        std::cout << "fail: already logged in\n";
    }
    else {
      std::cin >> username;
      if(users.cend() == users.find(username)) {
        std::cout << "fail: no such user\n";
      }
      else if(sessions.cend() == sessions.find(username)) {
        std::cout << "fail: already logged out\n";
      }
      else {
        sessions.erase(username);
        std::cout << "success: user logged out\n";
      }
    }
  }
}
