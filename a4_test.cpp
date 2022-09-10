// a4_test.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Michael Fischer
// St.# : 301310859
// Email: michael_fischer_2@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

//
// You can include any standard C++ files you like for testing purposes.
//
#include "a4.h"

using namespace std;

void converse(Chatbot* a, Chatbot* b, int max_turns);
void User_bot_test();
void Single_reply_bot_test();
void Moo_bot_test();
void Name_bot_test();
void Echo_bot_test();
void Random_reply_bot_test();
void Datetime_bot_test();
void Smart_bot_test();

int main() {
  User_bot_test();
  Single_reply_bot_test();
  Moo_bot_test();
  Name_bot_test();
  Echo_bot_test();
  Random_reply_bot_test();
  Datetime_bot_test();
  Smart_bot_test();
}

// converse is a helper function that you can use if you like. You are free to
// modify it in any way.
void converse(Chatbot* a, Chatbot* b, int max_turns = 6) {
  for(int turn = 1; turn <= max_turns; turn++) {
    string a_msg = a->get_msg(); 
    cout << "(" << turn << ") " << a->get_name() << ": " << a_msg << "\n";

    turn++;
    if (turn > max_turns) return;
    b->give_msg(a_msg);
    string b_msg = b->get_msg();
    cout << "(" << turn << ") " << b->get_name() << ": " << b_msg << "\n";
    a->give_msg(b_msg);
  } // for
}

void User_bot_test(){
  cout << "\nUser_bot testing...\n";
  User_bot user {"user_bot"};
  User_bot user2 {"user_bot_2"};
  assert(user.get_name().compare("user_bot") == 0);
  converse(&user, &user2, 4);

  cout << "User_bot_test()\t\t\tpassed\n";
}

void Single_reply_bot_test(){
  cout << "\nSingle_reply_bot testing...\n";
  User_bot user {"user_bot"};
  Single_reply_bot taco {"tacobot", "I Love tacos!"};
  assert(taco.get_name().compare("tacobot") == 0);
  converse(&user, &taco);

  cout << "Single_reply_bot_test()\t\tpassed\n";
}

void Moo_bot_test(){
  cout << "\nMoo_bot testing...\n";
  User_bot user {"user_bot"};
  Moo_bot moo {"moo_bot"};
  assert(moo.get_name().compare("moo_bot") == 0);
  converse(&user, &moo);

  cout << "Moo_bot_test()\t\t\tpassed\n";
}

void Name_bot_test(){
  cout << "\nName_bot testing...\n";
  User_bot user {"user_bot"};
  Name_bot megabot {"megabot"};
  assert(megabot.get_name().compare("megabot") == 0);
  converse(&user, &megabot);

  cout << "Name_bot_test()\t\t\tpassed\n";
}

void Echo_bot_test(){
  cout << "\nEcho_bot testing...\n";
  User_bot user {"user_bot"};
  Echo_bot echo {"repeato", "repeato is ready to go!"};
  assert(echo.get_name().compare("repeato") == 0);
  converse(&echo, &user);

  cout << "Echo_bot_test()\t\t\tpassed\n";
}

void Random_reply_bot_test(){
  cout << "\nRandom_reply_bot vector testing...\n";
  User_bot user {"user_bot"};
  Random_reply_bot cat {"Mittens", {"meow", "purrr", "meeeeow"}};
  assert(cat.get_name().compare("Mittens") == 0);
  converse(&user, &cat, 10);

  cout << "\nRandom_reply_bot file testing...\n";

  Random_reply_bot dog {"Fido", "dog_sounds.txt"};
  assert(dog.get_name().compare("Fido") == 0);
  converse(&user, &dog, 10);
  
  cout << "Random_reply_bot_test()\t\tpassed\n";
}

void Datetime_bot_test(){
  cout << "\nDatetime_bot() testing...\n";
  User_bot user {"user_bot"};
  Datetime_bot dt_bot {"deetee", {"Ask me about the date or time!", "I know the date and time!"}};
  assert(dt_bot.get_name().compare("deetee") == 0);
  converse(&user, &dt_bot, 10);

  cout << "Datetime_bot()\t\t\tpassed\n";
}

void Smart_bot_test(){
  cout << "\nSmart_bot() Topic: Music testing...\n";
  User_bot user {"user_bot"};
  Smart_bot smart_bot("Alan");
  assert(smart_bot.get_name().compare("Alan") == 0);
  converse(&user, &smart_bot, 20);

  cout << "Smart_bot_test()\t\tpassed\n";
}
