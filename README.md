# Assignment 4: Chatbots

In this assignment your task is to implement and test a number of different
chatbots.

## Getting Started

Put all the code you write for this assignment into [a4.h](a4.h). There is a
helper function there called `converse` that you can use to help test your
chatbots. **You can change `converse` if you like**. 

Among other files, [a4.h](a4.h) includes [Chatbot.h](Chatbot.h), which has the
`Chatbot` base class your classes must inherit from. Your inheriting classes
should implement all the virtual methods in a sensible way. We want to see you
use good programming style and make good use of C++'s object-oriented
features.

Chatbots have a name, and so every chatbot constructor should accept a name
(as a `string`).

**Important**: For each chatbot, make sure to implement the constructors
*exactly* as given in the examples and description. Otherwise the testing
software might give you 0.

Make sure to test all your chatbots! Since the chatbots are interactive, your
testing does *not* need to be automatic. You can test the chatbots manually
using, for example, the `converse` function given in [a4.cpp](a4.cpp).

Here's a class diagram for all the classes in this assignment:

![chatbot class diagram](chatbotClassDiagram.png)


## Chatbot 1: The User

Implement a chatbot class (that inherits from `Chatbot`) called `User_bot`
that asks the user to enter a line of text (on `cin`) whenever `get_msg` is
called. `give_msg` should print the message to the screen. This lets the user
talk with other chatbots using a function like `converse` in [a4.cpp](a4.cpp).

For example:

```cpp
User_bot user{"Stan"};
```

When this is done, you can use it in the `converse` function of
[a4.cpp](a4.cpp).


## Chatbot 2: Single Reply

Implement a chatbot class (that inherits from `Chatbot`) called
`Single_reply_bot` that always replies with the same string (provided in the
constructor).

```cpp
Single_reply_bot bot{"tacobot", "I love tacos!"};
```

The first string passed to the constructor is the bots name, and the second
string is the one thing it says.

Sample transcript:

```
tacobot> I love tacos!
user> All kinds?
tacobot> I love tacos!
user> What about ice cream?
tacobot> I love tacos!
```

## Chatbot 3: A Cow

Implement a chatbot class (that inherits from `Single_reply_bot`) called
`Moo_bot` that always replies with "moo". `Moo_bot` is a kind of
`Single_reply_bot`, and we want to see you implement it in a very short and
simple way by inheriting from `Single_reply_bot`.

```cpp
Moo_bot bot{"moobot"};
```

Sample transcript:

```
moobot> moo
user> Are you a cow?
moobot> moo
user> Nice to meet you.
moobot> moo
user> What else do you say?
moobot> moo
```

## Chatbot 4: Says its Name

Implement a chatbot class (that inherits from `Single_reply_bot`) called
`Name_bot` that always replies with "I am **name**", where **name** is the
name of the bot. This is a kind of `Single_reply_bot`, and we want to see you
implement it in a very short and simple way by inheriting from
`Single_reply_bot`.

```cpp
Name_bot bot{"megabot"};
```

Sample transcript:

```
megabot> I am megabot!
user> Who are you?
megabot> I am megabot!
user> I mean really. Who *are* you?
megabot> I am megabot!
user> Seriously?
megabot> I am megabot!
```

## Chatbot 5: Echoed Replies

Implement a chatbot class (that inherits from `Chatbot`) called `Echo_bot`
that always replies with the last input it recevies. If it needs to speak
before being told anything, then its reply is a special "first reply" string
that is given in its constructor as shown.

For example:

```cpp
Echo_bot bot{"repeato", "repeato is ready to go!"};
```

The name of `bot` is `repeato`, and if it is asked to speak first, it will say
the second string passed to the constructor.

Sample transcript:

```
repeato> repeato is ready to go!
user> Nice to meet you?
repeato> Nice to meet you?
user> ok
repeato> ok
user> wubba lubba dub dub!
repeato> wubba lubba dub dub!
```


## Chatbot 6: Random Replies

Implement a chatbot class (that inherits from `Chatbot`) called
`Random_reply_bot` that chooses a reply at random from a list of given
replies. It should have constructors that allow lists of replies to be read in
in at least the two following ways.

### A vector<string> of Replies

`Random_reply_bot` has a constructor that takes a `vector<string>` as its
second parameter (the first parameter is the name of the chatbot). If the
passed-in vector is empty, call `cmpt::error` in the constructor with a
helpful message.

For example:

```cpp
Random_reply_bot cat{"Mittens", {"meow", "purrr", "meeeeow"}};
```

Calling `cat.get_msg()` returns `"meow"`, `"purrr"`, or `"meeeeow"` at
random.

Sample transcript:

```
Mittens> purrr
user> Hi
Mittens> purrr
user> nice kitty
Mittens> meow
user> Do you know calclus?
Mittens> meeeeow
```

### Replies from a Text File

`Random_reply_bot` should have a constructor that has a `string`, for the name
of a file, as its second parameter (the first parameter being the name of the
chatbot). Each non-empty line of the file contains one reply. If the file
can't be opened, or if it is empty, then call `cmpt::error` in the constructor
with a helpful message.

For example, suppose the text file `dog_sounds.txt` contains this:

```
woof
ruff
yap yap yap
bow wow  
```

Then we can construct a random reply bot like this:

```cpp
Random_reply_bot dog{"Fido", "dog_sounds.txt"};
```

Calling `dog.get_msg()` returns `"woof"`, `"ruff"`, `yap yap yap`, or `"bow
wow"` at random.

**Hint**: The `getline` function in `std` may help.

Sample transcript:

```
Fido> bow wow
user> What's your name?
Fido> yap yap yap
user> Are you a good doggy?
Fido> ruff
```

## Chatbot 7: Current Time and Date

Implement a chatbot class (that inherits from `Chatbot`) called `Datetime_bot`
that replies with the current date and time just when the last string given to
it contains either "date" or "time" (or both) as a substring. If neither
"date" nor "time" appears, then the reply is a default message chosen at
random from a `vector<string>` of messages supplied in the constructor.

When checking for "date" or "time", the case should **not matter**, e.g. if
the last string told to the bot was "what's the dAtE???", then that counts as
containing "date". If "date" or "time" is embedded in another string, then it
still counts, e.g. "Give me an update?" would cause the date to be printed.

To be clear, if the last string contains *just* "date" as a substring, then
just the date should be the reply. If the last string contains *just* "time",
then just the time should be the reply. If *both* "date" and "time" appear,
then the reply should include both the date and time (the order in which you
to print the date and time in this case doesn't matter).

The **time string** should be in regular am/pm format, e.g. "8:12pm",
"7:00am", "12:02pm", or "0:05am" (5 minutes after midnight). **Careful**:
*Don't* use 24-hour format, and make sure there's a leading 0 when the minutes
value is less than 10.

The **date string** should be in the format "year-month-day". For example,
"2021-12-25" is December 25th 2021, and "1955-4-3" is April 3rd 1955.

For example:

```cpp
Datetime_bot dt_bot{"deetee", {"Ask me about the date or time!", 
                               "I know the date and time!"}};
```

Here, the first input is the bot's name, and the second is the
`vector<string>` of messages from where random replies will be chosen when
neither "date" nor "time" was in the last string told to the chatbot.

Sample transcript:

```
deetee> 8:31pm, 2021-7-9
user> What time is it?
deetee> 8:32pm
user> Don't tell me the date
deetee> 2021-7-9
user> One time I ate a date
deetee> 8:35pm, 2021-7-9
user> what thyme is it? 
deetee> I know the date and time!
```


## Chatbot 8: Turing Bot

[The Turing Test](https://en.wikipedia.org/wiki/Turing_test>) is a famous
thought experiment that some computer scientists believe can be used to
determine if a program has human-level intelligence. The test works by having
a program (that we are testing for intelligence) and an ordinary adult person
have a text-only conversation using a chatbot-like interface. If the program
can fool the human into thinking it's a real person, then, some say, the
program has human-level intelligence.

Implement an **original** and interesting chatbot class called `Smart_bot`
that tries to pass the Turing test. Make it is as smart and feature-rich as
you can. To simplify things a bit, it's okay if your chatbot is restricted to
one particular topic, as long as it is interesting and tries to be intelligent
in some way. You can expand upon ideas from the previous bots, or try
something new.

Please make something original and interesting, something that you would be
proud to show off to others. **Do a little bit of research on the web to get
ideas for other kinds of chatbots**. Low-effort chatbots won't get full marks.

In the source code comments for this chatbot, please include some description
of the techniques your chatbot uses, and provide links for any research you
did or help you received.

Your `Smart_bot` should be constructed like this:

```cpp
Smart_bot smart_bot("Alan");
```


## Submit Your Work

Please put all your code for the chatbots into [a4.h](a4.h), and put all your
testing code into [a4_test.cpp](a4_test.cpp). Only [a4_test.cpp](a4_test.cpp)
should have a `main()`. The marker will test your code by `#include`-ing your
[a4.h](a4.h) into their own testing file. They will use this
[makefile](makefile) to compile your program.

Compress your [a4.h](a4.h) and [a4_test.cpp](a4_test.cpp) files into a zip
file named `a4_submit.zip`, e.g. using this command in Linux:

```
$ zip a4_submit.zip a4.h a4_test.cpp
```

Include in the `a4_submit.zip` any files needed to compile and run your
`a4_test.cpp`. **Don't** include [cmpt_error.h](cmpt_error.h), `Chatbot.h`, or
`dog_sounds.txt`: the marker will put copies of those files into the same
folder as your code when they test your program.

When it's ready, submit your `a4_submit.zip` on Canvas.


## Basic Requirements

Before we give your program any marks, it must meet the following basic
requirements:

- Your test program, and the markers test program, must compile on Ubuntu
  Linux using the standard course [makefile](makefile), e.g.:
  
  ```
  $ make a4_test
  g++  -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g   a4_test.cpp   -o a4_test
  ```
  
  If a program fails to compile, your mark for this assignment will be 0.

- It must have no memory leaks or memory errors, according to `valgrind`,
  e.g.:

  ```
  $ valgrind ./a4_test
    
  // ... lots of output ... 
  ```

  A program is considered to have no memory error if:

  - In the `LEAK SUMMARY`, `definitely lost`, `indirectly lost`, and `possibly
    lost` must all be 0.

  - The `ERROR SUMMARY` reports 0 errors.

  - It is usually okay if **still reachable** reports a non- zero number of
    bytes.

- **You must include the large comment section with student info and the
  statement of originality**. If your submitted file does not have this, then
  we will assume your work is not original and it will not be marked.
  
If your program meets all these basic requirements, then it will graded using
the marking scheme below.


## Marking Scheme

### Source Code Readability (6 marks)

- All names of variables, functions, structs, classes, etc. are sensible,
  self-descriptive, and consistent.

- Indentation and spacing is perfectly consistent and matches the structure of
  the program. All blank lines and indents should have a reason.

- All lines are 100 characters in length, or less.

- Comments are used when appropriate, e.g to describe code that is tricky or
  very important. There are no unnecessary comments, and no commented-out
  code.

- Appropriate features of C++ are used in an appropriate way. For example, do
  **not** use a feature of C (like C-style strings) when there is a better C++
  feature (e.g. the standard `string` class). Don't use any features you don't
  understand.

- Overall, the source code is easy to read and understand.

### Chatbots 1 to 7 (14 marks)

**2 marks** for each complete and correct chatbot that works as intended.

Make sure that each chatbot has a *exactly* the constructor given in the
description/example. Each missing or incorrect constructor will result in a
penalty of at least -0.5 marks.


### Chatbot 8 (5 marks)

**4 marks** for an interesting and original chatbot. This chatbot should have
as many features as possible (e.g. at the very least as many features as
chatbot 2 and 4 combined). Obviously low-effort chatbots will not get full
marks.

**1 mark** for describing techniques the chatbot uses, and links to research.
