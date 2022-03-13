#include<bits/stdc++.h>
using namespace std;

#define typeof(x) __typeof__(x)
#define tr(container, it)\
for (typeof (container.begin()) it = container.begin(); it != container.end(); it++)


map <string,string> userpass;

class user{
    int uid;
    int priority;
    int friendid=-1;
    public:
        string email;
        string username;
        string password;
        user(string em, string uname, string pass){
            email=em;
            username=uname;
            password=pass;
        }
        void change_uname_pass();
        void send_msg();
        friend void match(int uid);
        friend void unmatch(int uid);
};

vector <user> users;

void user::change_uname_pass(){
    string newuname, oldpass, newpass1, newpass2;
    cout << "Enter new username: ";
    cin>>newuname;
    cout << "Enter old password: ";
    cin>>oldpass;
    cout << "Enter new password: ";
    cin>>newpass1;
    cout << "Confirm new password: ";
    cin>>newpass2;
    if(newuname!=username){
        tr(users, it){
            if((*it).username==newuname){
                cout << "This username is already taken." << endl;
                return;
            }
        }
    }
    if(password!=oldpass){
        cout << "Password entered is in correct" << endl;
        return;
    }
    if(newpass1!=newpass2){
        cout << "The new passwords entered do not match" << endl;
    }
    if(password==oldpass && newpass1==newpass2){
        username=newuname;
        password=newpass1;
        cout << "Credentials changed successfully." << endl;
        return;
    }
}

void sign_up(){
    string email1,uname,pass;
    cout << "Enter emailID: ";
    cin>>email1;
    cout << "Enter username: ";
    cin>>uname;
    cout << "Enter password: ";
    cin>>pass;
    if(users.empty()){
        user newuser(email1,uname,pass);
        users.push_back(newuser);
        cout << "Account created successfully" << endl;
    }
    else{
        tr(users,it){
            if((*it).username==uname){
                cout << "This username is already taken." << endl;
                return;
            }
        }
        user newuser(email1,uname,pass);
        users.push_back(newuser);
        cout << "Account created successfully" << endl;
    }
    return;
}

void sign_in(){
    int flag=0;
    string uname,pass;
    cout << "Enter username: ";
    cin>>uname;
    cout << "Enter password: ";
    cin>>pass;
    tr(users, it){
        if((*it).username==uname && (*it).password==pass){
            flag=1;
            cout << "You have successfully logged in, "+uname << endl;
            // mainmenu(uname);
            break;
        }
    }
    if(!flag){
        cout << "Username or password entered is incorrect" << endl;
    }
    return;
}