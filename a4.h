// a4.h

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

#include "cmpt_error.h"    // These are the only permitted includes
#include "Chatbot.h"       // for a4.h!
#include <iostream>        //
#include <fstream>         // Don't include anything else.
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <ctime>     
#include <cassert>

class User_bot: public Chatbot{
    string message_;
public:
    User_bot(const string& name2)
    : Chatbot(name2)
    { }
    
    void give_msg(const string& s){
        if (s.length() > 0) return; // output nothing and uses s so no error on makefile
    }
    
    string get_msg(){
        cout << "Enter a message: ";
        getline (cin, message_); 
        return message_;
    }
};

class Single_reply_bot : public Chatbot{
    string message_;
public:
    Single_reply_bot(const string& name, const string& message)
    : Chatbot(name), message_(message)
    { }

    void give_msg(const string& s){
        if (s.length() > 0) return; // output nothing and uses s so no error on makefile
    }

    string get_msg(){
        return message_;
    }
};

class Moo_bot : public Single_reply_bot{
public:
    Moo_bot(const string& name)
    : Single_reply_bot(name, "moo")
    { }
};

class Name_bot : public Single_reply_bot{
public:
    Name_bot(const string& name)
    : Single_reply_bot(name, "I am " + name + "!")
    { }
};

class Echo_bot : public Chatbot{
    string message_;
public:
    Echo_bot(const string& name, const string& message)
    : Chatbot(name), message_(message)
    { }
    
    void give_msg(const string& s){
        message_ = s;
    }

    string get_msg(){
        return message_;
    }

};

class Random_reply_bot : public Chatbot{
    vector<string> replies_v; 
    fstream file;
public:
    Random_reply_bot(const string& name, const vector<string> replies)
    : Chatbot(name), replies_v(replies)
    { 
        srand(time(NULL)); // random seed
        if (replies.size() == 0)
            cmpt::error("Vector passed into random reply bot is empty!");
    }

    Random_reply_bot(const string& name,const string& filename)
    : Chatbot(name), file(filename)
    { 
        srand(time(NULL)); // random seed
        if (file.fail()) cmpt::error("Error opening file!\n");
        string temp;
    
        while (getline(file, temp)){
            replies_v.push_back(temp);
        }

        if (replies_v.size() == 0) cmpt::error("File is empty!\n");
        file.close();
    }

    void give_msg(const string& s){
        if (s.length() > 0) return; // output nothing and uses s so no error on makefile
    }

    string get_msg(){
        return (replies_v[rand() % replies_v.size()]); // random string from replies_v
    }

};

class Datetime_bot : public Chatbot{
    vector<string> replies_v;
    string message_;
    string name_;
public:
    Datetime_bot (const string& name, const vector<string> replies)
    : Chatbot(name), replies_v(replies)
    {
        srand(time(NULL)); // random seed
        if (replies.size() == 0)
            cmpt::error("Vector passed into random reply bot is empty!");
    }
    
    void give_msg(const string& s){
        string str;
        message_.clear(); // resets output message
        
        for (char c: s){
            str.push_back(tolower(c)); // converts all characters to lowercase
        }

        size_t time_ = str.find("time");
        size_t date_ = str.find("date");

        if (time_ != string::npos || date_ != string::npos){
            time_t current_time = time(0); // time in seconds size 1970
            tm *local_time = localtime(&current_time); //struct which holds time since 1900

            if (time_ != string::npos){
                string am_pm = "am";

                int hour_ = local_time->tm_hour;

                if (hour_ >= 12){
                    hour_ %= 12;
                    am_pm = "pm";
                }

                string minute_ = to_string(local_time->tm_min);
                if (minute_.length() == 1) minute_ = "0" + minute_;
                
                message_ = to_string(hour_) + ":" + minute_+ am_pm;
            }

            if (date_ != string::npos) {
                int year_ = 1900 + local_time->tm_year; // tm-year is years since 1900
                int month_ = 1 + local_time->tm_mon; // tm_mon range 0 to 11
                int day_ = local_time->tm_mday; //tm_mday range 1 to 31

                if (message_.length() != 0) message_ += ", "; 
                // if message isn't empty then it has time in it. Add comma so date can prepend

                message_ += to_string(year_) + "-" + to_string(month_) + "-" + to_string(day_);
            }
        }
        // if date or time never found then choose a random message from replies_v
        if (message_.length() == 0) message_ = replies_v[rand() % replies_v.size()];
    }
    
    string get_msg(){
        return message_;
    }
};

typedef struct{
    string song_name;
    string band_name;
    vector<string> artist; 
    vector<string> genre;
    vector<string> instrument;
} Music;

vector<Music> create_song_list(){
    vector<Music> songs;

    Music a {
        "Someone You Loved",
        "None",
        {"Lewis Capaldi"},
        {"Alternative", "Indie"},
        {"Guitar"}
    };
    songs.push_back(a);

    Music b {
        "Memories",
        "Maroon 5",
        {"Adam Levine", "James Valentine", "Jesse Carmichael"},
        {"Pop", "Reggae fusion"},
        {"Piano"}
    };
    songs.push_back(b);

    Music c{
        "Highway To Hell",
        "AC/DC",
        {"Angus Young", "Brian Johnson", "Phil Rudd"},
        {"Rock"},
        {"Drums", "Guitar"}

    };
    songs.push_back(c);
    
    return songs;
}

bool find_hello(string str){
    if (str.find("hello") != string::npos) return true;
    if (str.find("hi") != string::npos) return true;
    if (str.find("hey") != string::npos) return true;
    if (str.find("whats up") != string::npos) return true;
    return false;
}

bool find_weather(string str){
    if (str.find("weather") != string::npos) return true;
    return false;
}

bool find_name(string str){
    if (str.find("name") != string::npos) return true;
    return false;
}

bool find_age(string str){
    if (str.find("age") != string::npos) return true;
    if (str.find("old") != string::npos) return true;
    return false;
}

bool find_mood(string str){
    if (str.find("it going") != string::npos) return true;
    if (str.find("terrific") != string::npos) return true;
    if (str.find("how are you") != string::npos) return true;
    if (str.find("feeling") != string::npos) return true;
    if (str.find("great") != string::npos) return true;
    if (str.find("good") != string::npos) return true;
    if (str.find("bad") != string::npos) return true;
    if (str.find("okay") != string::npos) return true;
    if (str.find("meh") != string::npos) return true;
    if (str.find("so so") != string::npos) return true;
    if (str.find("sad") != string::npos) return true;
    return false;
}

bool find_genre(string str){
    if (str.find("genre") != string::npos) return true;
    if (str.find("type of music") != string::npos) return true;
    return false;
}

bool find_agreement(string str){
    if (str.find("yeah") != string::npos) return true;
    if (str.find("yes") != string::npos) return true;
    if (str.find("alright") != string::npos) return true;
    if (str.find("totally") != string::npos) return true;
    if (str.find("agree") != string::npos) return true;
    return false;
}

bool find_band(string str){
    if (str.find("band") != string::npos) return true;
    return false;
}

bool find_artist(string str){
    if (str.find("artist") != string::npos) return true;
    return false;
}

bool find_song(string str){
    if (str.find("song") != string::npos) return true;
    return false;
}

bool find_long(string str){
    if (str.find("long") != string::npos) return true;
    return false;
}

bool find_instrument(string str){
    if (str.find("instrument") != string::npos) return true;
    if (str.find("play") != string::npos) return true;
    return false;
}

bool find_music(string str){
    if (str.find("music") != string::npos) return true;
    if (str.find("interest") != string::npos) return true;
    if (str.find("hobby") != string::npos) return true;
    if (str.find("free time") != string::npos) return true;
    if (str.find("freetime") != string::npos) return true;
    if (str.find("do for fun") != string::npos) return true;
    return false;
}

bool find_my(string str){
    if (str.find("my") != string::npos) return true;
    if (str.find("i") != string::npos) return true;
    return false;
}

string find_user_instrument(string str){
    if (str.find("piano") != string::npos) return "piano";
    if (str.find("guitar") != string::npos) return "guitar";
    if (str.find("drums") != string::npos) return "drums";
    if (str.find("violine") != string::npos) return "violine";
    return "";
}

bool unknown_input(string message){
    if (message.length() == 0) return true;
    return false;
}

string string_to_lower(string s){
    string str;
    for (char c: s){
        str.push_back(tolower(c)); // converts all characters to lowercase
    }
    return str;
}

class Smart_bot : public Chatbot{
    vector<Music> songs = create_song_list();
    vector<string> replies_v;
    vector<string> hello_v = {"Hello, it's nice to meet you", "Hi!", "Hey, whats up?"};
    vector<string> unknown_v = {"I'm sorry I didn't understand what you meant.",
        "What do you mean by that?", "I didn't get that.", "huh?"};

    vector<string> mood_v = {"I'm doing good!", "pretty good", "terrific!", "I'm alright."};

    string message_ = hello_v[rand() % hello_v.size()]; // talk first -> random hello message
    string users_instrument_;

public:
    Smart_bot(const string& name)
    : Chatbot(name)
    { 
        srand(time(NULL)); // random seed
    }

    void give_msg(const string& s){
        string str = string_to_lower(s);
        message_.clear();
        
        if (find_hello(str)) message_ = hello_v[rand() % hello_v.size()]; // random greeting
        if (find_name(str)) message_ = "Hi, my name is " + get_name() + "!"; // overrides hello
        if (find_agreement(str)) message_ = "Yeah I totally agree";
        if (find_weather(str)) message_ = "Yeah the weathers great!";
        if (find_age(str)) message_ = "I'm " + to_string(rand() % 21 + 20) + " years old.";
        if (find_mood(str)) message_ = mood_v[rand() % mood_v.size()]; // random mood

        if (find_music(str)) {
            message_ = "Ohh I love music. There's so many different kinds";
            message_ += " and they all make me feel so alive!";
        }

        if (find_instrument(str))
            message_ = "I play the " + songs[rand() % songs.size()].instrument[0] + ".";

        if (find_my(str)){ // store user_ instruemnt information if my + instrument keyword
            string found_instrument = find_user_instrument(str);

            if (find_instrument(str) && users_instrument_.empty() == false){
                message_ = "You play the " + users_instrument_;
                message_ += ", we should play together sometime!";
            }
            if (found_instrument.empty() == false && users_instrument_.empty())
                users_instrument_ = found_instrument; // user instrument information stored
        }

        if (find_long(str))
            message_ = "I've been playing for " + to_string(rand() % 10) + " years!";

        if (find_genre(str)) // random genre
            message_ = "I like " + songs[rand() % songs.size()].genre[0] + " music.";

        if (find_band(str)) {
            message_ = "I like " + songs[1].band_name + "."; // always same band and song name
            message_ += " Their song " + songs[1].song_name + " is one of my favourite!";
        }

        if (find_artist(str)) 
            message_ = "I like " + songs[rand() % songs.size()].artist[0] + "."; // random artist

        if (find_song(str)){
            message_ = "One of my favourite songs is ";
            message_ += songs[rand() % songs.size()].song_name + " I really like its beat.";
        }

        // catch all unknown inputs and respond with a random unknown reply
        if (unknown_input(message_)) message_ = unknown_v[rand() % unknown_v.size()];
    }

    string get_msg(){
        return message_;
    }

    /*
    Smart bot Techniques, Implementation and Research Links
    Topic: Music

    Techniques: I made a Rule based retrieval chat bot that has its responses made 
    based off keywords of the users input. I also prioritize the chat bots output message
    from bottom to top re-writting the message if any of the below if statements are true.
    Lastly I stored some of the users data if they used i or me in their sentence as well as
    other key words like an instrument.

    The above message prioritization can be seen with this example: 
    "What is the name of a song you like?" 
    Which has both the song and name keyword. Since find_song() is below find_name() 
    the bot will choose the song response.

    Stored information can be seen in this example: 
    user >> "I love to play the guitar!" 
    bot >> "I play the drums."
    Which has both the I and guitar keyword. This make the bot store the guitar string in
    a variable called user_instrument and print it out the next time the user asks which
    instrument they play
    user >> "What instrument do I play?"
    bot >> "You play the guitar, we should play together sometime!"

    The bot was made with the idea that it would be having a conversation with someone around 
    the topic of music. Therefore the responses it is best at formulating are general greetings
    and music related conversations.

    https://www.kdnuggets.com/2019/12/build-intelligent-chatbot.html
    https://builtin.com/design-ux/chatbot-turing-test-mitsuku-pandorabots
    https://www.mygreatlearning.com/blog/basics-of-building-an-artificial-intelligence-chatbot/

    */

};

/* References
    Chat bot techniques and research references above at the end of Smart_bot class

    getline documentation to get users line input
    https://www.cplusplus.com/reference/string/string/getline/

    getline to be used with a file instead of cin
    https://stackoverflow.com/questions/20739453/using-getline-with-file-input-in-c

    random seed
    https://www.cplusplus.com/reference/cstdlib/rand/

    referenced how to check if a file failed to open
    https://www.cplusplus.com/reference/fstream/ifstream/
    https://www.cplusplus.com/reference/ios/ios/fail/

    string find documentation
    https://www.cplusplus.com/reference/string/string/find/

    current time and date reference
    https://www.softwaretestinghelp.com/date-and-time-in-cpp/
    https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
*/


