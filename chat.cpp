#include<bits/stdc++.h>
using namespace std;

#define typeof(x) __typeof__(x)
#define tr(container, it)\
for (typeof (container.begin()) it = container.begin(); it != container.end(); it++)



class user{
    int matchid=0;          //0-unmatched, 1-looking for match, 2-matched
    int priority;
    string friendname="";
    public:
        string email;
        string username;
        string password;
        user(string em, string uname, string pass){
            email=em;
            username=uname;
            password=pass;
        }
        string viewfriend(){
            return friendname;
        }
        void setfriend(string str){
            friendname=str;
        }
        int viewmatchid(){
            return matchid;
        }
        void setmatchid(int i){
            matchid=i;
        }
        void change_uname_pass();
        void view_inbox();
        void send_msg();
        void match();
        void unmatch();
        friend void matchup();
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
    if(newuname!=username && newuname!=""){
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

void mainmenu(user cur);
void matchup();

void user::view_inbox(){        //database

}

void user::send_msg(){      //database
    if(matchid!=2){
        cout << "Looks like you are not matched yet\nPlease try again later" << endl;
    }
    else{
        string msg;
        cout << "Enter your message: ";
        cin >> msg;
        //send to friendname
    }
}

void user::match(){
    if(matchid==2){
        cout << "You are already have a match\nIf you wish to find another one please unmatch first" << endl;
    }
    if(matchid==1){
        cout << "You are already looking for a match\nPlease wait till you find one" << endl;
    }
    if(matchid==0){
        matchid=1;
        cout << "You have started looking for a match" << endl;
        matchup();
    }
}

void user::unmatch(){
    if(matchid==2){
        matchid=0;
        //send msg to friend notifying about unmatch
        tr(users, it){
            if((*it).username==friendname){
                (*it).matchid=0;
                (*it).friendname="";
                break;
            }
        }
        friendname="";
        cout << "You are unmatched yourself\nIf you wish to find another match start looking for one" << endl;
    }
    if(matchid==1){
        matchid=0;
        cout << "You have stopped looking for your match" << endl;
    }
    if(matchid==0){
        cout << "You don't have a friend to unmatch" << endl;
    }
}

void matchup(){             //should run every now and then
    vector < string > unmatched;
    int a,b;
    srand(time(0));
    tr(users, it){
        if((*it).viewmatchid()==1){
            unmatched.push_back((*it).username);
        }
    }
    int total_unmatched=unmatched.size();
    if(total_unmatched>=2){
        a=rand()%total_unmatched;
        b=rand()%total_unmatched;
        while(b==a){
            b=rand()%total_unmatched;
        }
        tr(users, it){
            if((*it).username==unmatched[a]){
                (*it).setmatchid(2);
                (*it).setfriend(unmatched[b]);
                //send msg to unmatched[a]
            }
            else if((*it).username==unmatched[b]){
                (*it).setmatchid(2);
                (*it).setfriend(unmatched[a]);
                //send msg to unmatched[b]
            }
        }
    }
    //working on random algo
    return;
}

void sign_up(){
    string email1,uname,pass;
    cout << "Enter emailID: ";
    cin>>email1;
    cout << "Enter username: ";
    cin>>uname;
    cout << "Enter password: ";
    cin>>pass;
    if(uname!=""){
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
    }
    else{
        cout << "Username cannot be empty" << endl;
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
            mainmenu(*it);
            break;
        }
    }
    if(!flag){
        cout << "Username or password entered is incorrect" << endl;
    }
    return;
}

void start(){
    int choice,flag=0;
    while(true){
        cout << "\nPlease Enter your choice\n  1-Sign_up\n  2-Sign_in\n  3-Exit \n \n" << endl;
        cin>>choice;
        switch(choice){
            case 1:{
                sign_up();
                break;
            }
            case 2:{
                sign_in();
                break;          //endless loop?
            }
            case 3:{
                flag=1;
                break;
            }
            default:{
                cout << "Enter a valid number" << endl;
                break;
            }
        }
        if(flag){
            break;
        }
    }
}

void mainmenu(user cur){
    int choice,back=0;
    main_menu:
        back=0;
        cout << "\n1-View Inbox\n2-Send Message\n3-Match\n4-Unmatch\n5-Change Credentials\n6-Log Out\n" << endl;
        cin>>choice;
        switch(choice){
            case 1:{
                cur.view_inbox();
                cout << "Go back?";
                cin>>back;
                if(back){
                    goto main_menu;
                }
                break;
            }
            case 2:{
                cur.send_msg();
                cout << "Go back?";
                cin>>back;
                if(back){
                    goto main_menu;
                }
                break;
            }
            case 3:{
                cur.match();
                cout << "Go back?";
                cin>>back;
                if(back){
                    goto main_menu;
                }
                break;
            }
            case 4:{
                cur.unmatch();
                cout << "Go back?";
                cin>>back;
                if(back){
                    goto main_menu;
                }
                break;
            }
            case 5:{
                cur.change_uname_pass();
                cout << "Go back?";
                cin>>back;
                if(back){
                    goto main_menu;
                }
                break;
            }
            case 6:{
                system("cls");
                //start();
                break;
            }
            default:{
                cout << "Please enter a valid number" << endl;
                goto main_menu;
                break;
            }
        }
}

int main(){
    start();
    return 0;
}