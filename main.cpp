//  main.cpp
//  Choose Your Own Story Game
//
//  Created by Ezekiel Williams on 1/9/19.
//  Copyright © 2019 Ezekiel Williams. All rights reserved.
/*
    ***************** INSTRUCTIONS *****************
    ENTER NOTHING FOR YOUR FIRST TIME PLAYING. The
        question will be displayed, and then you can
        enter 'a' or 'b' (without quote ticks) to
        begin making your decisions.
 
    AFTER YOUR FIRST DECISION: There will be a code
    That you then enter with your a or b input. This
    will continue your game where you left off.
    ***************** ************ *****************
 
 Description:
    I was inspired by the Netflix tv show, Black Mirror.
    They debuted a new episode that let you choose your
    way through the scenes. It was also about a kid who
    was making a choose-your-own-adventure game. This
    is my attempt on the SoloLearn platform. Everything
    is completely original, including the story, so I
    can't promise it will be good.
*/

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <map>

using std::cout;
using std::cin;
using std::endl;
using std::string;

/* -------------------------CHOICE-CLASS---------------------------- */
class Choice {
protected:
    string text;
    char route;
    
public:
    virtual ~Choice(){};
    Choice();
    Choice(string text, char route);
    string getText();
};
Choice::Choice()
: text("")
, route('x')
{
    
}
Choice::Choice(string text, char route)
: text(text)
, route(route)
{
    
}
string Choice::getText() {
    return text;
}

/* -------------------------CHOICEA-CLASS---------------------------- */
class ChoiceA: public Choice {
public:
    ChoiceA();
    ChoiceA(string text);
};
ChoiceA::ChoiceA()
: Choice()
{
    
}
ChoiceA::ChoiceA(string text)
: Choice(text, 'a')
{
    
}

/* -------------------------CHOICEB-CLASS---------------------------- */
class ChoiceB: public Choice {
public:
    ChoiceB();
    ChoiceB(string text);
};
ChoiceB::ChoiceB()
: Choice()
{
    
}
ChoiceB::ChoiceB(string text)
: Choice(text, 'b')
{
    
}

/* -------------------------QUESTION-CLASS---------------------------- */
class Question {
private:
    Question* ARoute;
    Question* BRoute;
    ChoiceA AChoice;
    ChoiceB BChoice;
    string story;
    std::map<string, string> pathUniqueModifiers;
    int modPos;
    bool modded;
    
private:
    void modifyStory(string path);
    
public:
    Question();
    Question(string AChoice, string BChoice);
    Question(bool modded);
    ~Question();
    
    // functions
    void makeRoutes(Question* A, Question* B);
    void ask(string path);
    Question* goA();
    Question* goB();
    void printOptions();
    // give a question a story, which is prited before the question is asked and the choices are offered
    void giveStory(string story);
    // Write the modification to the story and the path needed that will make sense for the modification path = "aaba" e.g.
    void addStoryModifier(string storyMod, string path);
    // this should only be used for modded questions
    void giveQuestions(string aChoice, string bChoice);
};
Question::Question()
: ARoute(nullptr)
, BRoute(nullptr)
, AChoice("")
, BChoice("")
, story("")
, modPos(-1)
, modded(false)
{
    // modPos is -1 to start because the lowest a mod position can be is zero, so checking for -1 will mean no mod was added
}
Question::Question(bool modded)
: ARoute(nullptr)
, BRoute(nullptr)
, AChoice("")
, BChoice("")
, story("")
, modPos(-1)
, modded(true)
{
    // modPos is -1 to start because the lowest a mod position can be is zero, so checking for -1 will mean no mod was added
}
Question::Question(string AChoice, string BChoice)
: ARoute(nullptr)
, BRoute(nullptr)
, AChoice(AChoice)
, BChoice(BChoice)
, story("")
, modPos(-1)
, modded(false)
{
    
}
Question::~Question() {
    ARoute = nullptr;
    BRoute = nullptr;
}
void Question::makeRoutes(Question* A, Question* B) {
    this->ARoute = A;
    this->BRoute = B;
}
void Question::ask(string path) {
    if (modded) {
        modifyStory(path);
    }
    cout << story << endl << endl;
    cout << AChoice.getText() << "(a) or " << BChoice.getText() << "(b)?" << endl;
}
Question* Question::goA() {
    cout << "Chosen was: " << AChoice.getText() << ".\n" << endl;
    if (ARoute == nullptr) {
        cout << "There is no other choice beyond this." << endl;
    }
    return ARoute;
}
Question* Question::goB() {
    cout << "Chosen was: " << BChoice.getText() << ".\n" << endl;
    if (BRoute == nullptr) {
        cout << "There is no other choice beyond this." << endl;
    }
    return BRoute;
}
void Question::giveStory(string story) {
    // when typing in a modded story, add necessary spaces for the modification string when it's inserted
    this->story = story;
    // now check for a mod position if modded
    if (modded) {
        int i, len = story.length();
        for (i = 0; i < len; ++i) {
            if (story.at(i) == '^') {
                modPos = i;
            }
        }
    }
}
void Question::addStoryModifier(string storyMod, string path) {
    if (modPos >= 0) {
        pathUniqueModifiers[path] = storyMod;
    }
}
void Question::modifyStory(string path) {
    if (modPos == story.length() - 1) {
        story.append(pathUniqueModifiers[path]);
        // erase the '^' symbol at the end of the string
        story.erase(story.end() - 1);
    }
    else {
        story.insert(modPos, pathUniqueModifiers[path]);
        // after the mod is inserted, the '^' symbol will get moved to where it was (modPos) + the length of string that was just inserted
        story.erase(modPos + pathUniqueModifiers[path].length(), 1);
    }
}
void Question::giveQuestions(string aChoice, string bChoice) {
    this->AChoice = ChoiceA(aChoice);
    this->BChoice = ChoiceB(bChoice);
}

/* -------------------------GAME-CLASS---------------------------- */
class Game {
private:
    string pathStr;
    Question* currentQuestion;
    
    Question elf;
    
    Question forest;
    Question shit;
    
    Question nectar;
    Question mushroom;
    Question butt;
    Question act;
    
    Question fountain;
    
    Question filler;
    
    void linkQuestions();
    
public:
    Game();
    
    // functions
    void travelTo(char pathChoice);
    void gameLoop();
    void printOptions();
    bool receiveInput(string& userInput);
};
Game::Game()
: pathStr("")
, currentQuestion(nullptr)
, elf("Keep walking", "Shit your pants")
, forest("Eat the mushroom", "Drink the nectar")
, shit("Wipe your butt", "Act like it didn't happen")
, nectar("Walk to the light", "Follow your father")
, mushroom("Make a fire", "Find food")
, butt("Bury poop leaf", "Stick to tree")
, act("Wash crusties", "Keep walking")
, fountain(true)
, filler("TESTING", "TESTING")
{
    linkQuestions();
    /******** when typing in a modded story, add necessary spaces for the modification string when it's inserted ******/
    elf.giveStory("You encounter an elf who's sitting on a tree stump. You approach them cautiously. "
                  "As you get within arms reach, you notice their eyes have popped out of their head. You could keep walking, or...");
    
    // elf a choice path "a"
    forest.giveStory("As you walk the forest, trying to forget the sight of that dead, eyeless elf, you notice a strange light ahead. "
                     "It's a strange ray of sunlight, shining through the canopy. On the ground where the sun ray stops, there are two bowls. "
                     "In one bowl, a greenly tinted mushroom - the other bowl, a yellowish nectar-like fluid.");
    // elf b choice path "b"
    shit.giveStory("The sight of that elf causes your body to involuntarily shit itself - right on the spot.");
    
    // forest a choice path "aa"
    mushroom.giveStory("You pick the mushroom up out of the bowl. It's not so large, so you place the whole thing in your mouth at once and begin to chew. "
                       "For some reason, you expected it to have a psychodelic affect. After wasting that time, you decide it's time to make camp.");
    // forest b choice path "ab"
    nectar.giveStory("You pick up the bowl of nectar, touching the rim of the bowl to your lips, and slowly tip your head back. You pour the sweet fluid "
                     "down your throat and enjoy its somehow-nostalgic taste. Your vision immediately starts to change. The forest in front of you "
                     "parts into two paths. One path is crossed infinitely by rays of light - you see a glimpse of your father walking down the other.");
    
    // shit a choice path "ba"
    butt.giveStory("After taking care of your hygenic duties, you decide what to do with the poor leaf you chose to sacrifice for the task. You glance "
                   "at the ground, which is very loose and damp. You also see a nearby tree with a lot of moss growing on it.");
    // shit b choice path "bb"
    act.giveStory("Bold move deciding to act like something like that never happened. After walking away, you find a nearby creek, which could offer "
                  "some much needed cleaning. You have also just seen a horific scene and think getting out of here might be the best choice.");
    
    // act b choice path "bbb" and nectar b choice path "abb"
    fountain.giveStory("After walking for a ways you see a break in the trees up ahead. A few more steps brings you to the clearing. In the clearing, you"
                       " spot something quite dumbfounding. Right in the center of this clearing sits a beautifully hand-carved stone fountain. ^"
                       " You walk quickly to the fountain. You stare deeply at your reflection in the bottom pool. You almost can't look away...");
    fountain.addStoryModifier("Some fresh, clean water would be perfect for the accident that happened in your pants earlier."
                              , "bbb");
    fountain.addStoryModifier("It looks just like the one your father had made for the front garden of your family home."
                              , "abb");
    fountain.giveQuestions("Keep staring at your reflection.", "Swipe at the water and ruin your reflection.");
}

void Game::linkQuestions() {
    elf.makeRoutes(&forest, &shit);
    // the current question should be set to the first question
    currentQuestion = &elf;
    
    forest.makeRoutes(&mushroom, &nectar);
    shit.makeRoutes(&butt, &act);
    
    act.makeRoutes(&filler, &fountain);
    nectar.makeRoutes(&filler, &fountain);
}

void Game::travelTo(char pathChoice) {
    if (pathChoice == 'a') {
        currentQuestion = currentQuestion->goA();
        pathStr.append("a");
    }
    else if (pathChoice == 'b') {
        currentQuestion = currentQuestion->goB();
        pathStr.append("b");
    }
    else {
        cout << "Somehow the path choice wasn't a or b." << endl;
    }
}

void Game::printOptions() {
    currentQuestion->ask(pathStr);
}

bool Game::receiveInput(string& userInput) {
    
    bool badInput = true;
    do {
        cout << "(quit, a or b)>> ";
        getline(cin, userInput);
        // since this is BanderSnatch, you have only two choices; a or b, so this logic checks for
        int len = (int)(userInput.length());
        
        // convert to all lower case
        if (len > 1) {
            for (int i = 0; i < len; ++i) {
                if (isupper(userInput[i])) {
                    userInput[i] = tolower(userInput[i]);
                }
            }
        }
        
        char choiceChar = userInput[0];
        if (userInput == "quit") {
            return true;
        }
        else if (len == 0 || len > 1) {
            cout << "Enter one character, a or b." << endl;
        }
        else if (choiceChar != 'a' && choiceChar != 'b') {
            cout << "Enter either character, a or b." << endl;
        }
        else {
            badInput = false;
        }
        
    } while (badInput);
    
    
    return false;
}

void Game::gameLoop() {
    
    string userInput = "";
    
    while (true) {
        // print story
        // print options
        printOptions();
        // take input
        if (receiveInput(userInput)) {
            break;//quit was chosen
        }
        // go to the option in the input
        travelTo(userInput[0]);
        
        // TODO refine the 'end' of a path
        if (currentQuestion == nullptr) {
            break;
        }
    }
    
}

/* ---------------------------MAIN------------------------------ */
int main(int argc, const char * argv[]) {
    srand(static_cast<unsigned int>(time(nullptr)));
    
    Game game;
    game.gameLoop();
    
    return 0;
}
