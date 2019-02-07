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

First Run: enter nothing

Second Run:
Line One: choice for last run question
Line Two: nothing

Third and above run:
Line One: choice for last run question
Line Two: code from last run
***************** ************ *****************

Description:
I was inspired by the Netflix tv show, Black Mirror.
They debuted a new episode that let you choose your
way through the scenes. It was also about a kid who
was making a choose-your-own-adventure game. This
is my attempt on the SoloLearn platform. Everything
is completely original, including the story, so I
can't promise it will be good.

This is a work in progress. Every new layer of choices
doubles in size from the previous layer, so story
making takes a lot time. Like and comment if you
so choose. I might be so inclined to make more
choices.
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
	virtual ~Choice() {};
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
class ChoiceA : public Choice {
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
class ChoiceB : public Choice {
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
	Question * ARoute;
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
	Question(string AChoice, string BChoice, bool modded);
	~Question();

	// functions
	void makeRoutes(Question* A, Question* B);
	void ask(string path);
	Question* goA();
	Question* goB();
	// give a question a story, which is prited before the question is asked and the choices are offered
	void giveStory(string story);
	// Write the modification to the story and the path needed that will make sense for the modification path = "aaba" e.g.
	void addStoryModifier(string storyMod, string path);
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
Question::Question(string AChoice, string BChoice, bool modded = false)
	: ARoute(nullptr)
	, BRoute(nullptr)
	, AChoice(AChoice)
	, BChoice(BChoice)
	, story("")
	, modPos(-1)
	, modded(modded)
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

/* -------------------------GAME-CLASS---------------------------- */
class Game {
private:
	string pathStr;
	Question* currentQuestion;

	Question elf;

	Question forest;
	Question soil;

	Question nectar;
	Question mushroom;
	Question butt;
	Question act;

	Question cleanoff;
	Question fountain;
	Question light;
	Question fire;
	Question food;
	Question bury;
	Question tree;
    
    Question fishing;
    Question hunting;
    Question shrugoff;
    Question investigate;
    Question leavePath;
    Question continueOn;
    Question keepLooking;
    Question swipeWater;
    Question footsteps;
    Question whosThere;
    Question dontJudge;
    Question followInstructions;
    Question tearNote;

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
	, elf("Keep walking", "Soil yourself")
	, forest("Eat the mushroom", "Drink the nectar")// tier 2
	, soil("Clean yourself", "Act like it didn't happen")
	, nectar("Walk to the light", "Follow your father")// tier 3
	, mushroom("Make a fire", "Find food")
	, butt("Bury poop leaf", "Stick to tree")
	, act("Wash off", "Keep walking")
	, fountain("Keep staring at reflection", "Swipe at the water", true)// tier 4
	, filler("TESTING", "TESTING")
	, light("Find a way out", "Continue walking")
	, fire("It was probably an animal", "Investigate the sound")
	, food("Go fishing", "Go hunting")
	, bury("Follow the instructions", "Tear up the note")
	, tree("Apologize to the tree", "Shrug your shoulders")
	, cleanoff("Go fishing", "Follow the footsteps")
{
    // linkQuestions is required to set the path of the story
	linkQuestions();
	filler.giveStory("Just a filler story");
	/******** when typing in a modded story, add necessary spaces for the modification string when it's inserted ******/
	elf.giveStory("You encounter an elf who's sitting on a tree stump. You approach them cautiously. "
		"As you get within arms reach, you notice their eyes have popped out of their head. You could keep walking, or...");

	// ---------------------------------------TIER 2------------------------------------------ //
	// elf a choice path "a"
	forest.giveStory("As you walk the forest, trying to forget the sight of that dead, eyeless elf, you notice a strange light ahead. "
		"It's a strange ray of sunlight, shining through the canopy. On the ground where the sun ray stops, there are two bowls. "
		"In one bowl, a greenly tinted mushroom - the other bowl, a yellowish nectar-like fluid.");
	// elf b choice path "b"
	soil.giveStory("The sight of that elf causes your body to involuntarily soil itself - right on the spot.");
	// ---------------------------------------TIER 2------------------------------------------ //

	// ---------------------------------------TIER 3------------------------------------------ //
	// forest a choice path "aa"
	mushroom.giveStory("You pick the mushroom up out of the bowl. It's not so large, so you place the whole thing in your mouth at once and begin to chew. "
		"For some reason, you expected it to have a psychodelic affect. After wasting that time, you decide it's time to make camp.");
	// forest b choice path "ab"
	nectar.giveStory("You pick up the bowl of nectar, touching the rim of the bowl to your lips, and slowly tip your head back. You pour the sweet fluid "
		"down your throat and enjoy its somehow-nostalgic taste. Your vision immediately starts to change. The forest in front of you "
		"parts into two paths. One path is crossed infinitely by rays of light - you see a glimpse of your father walking down the other.");
	// soil a choice path "ba"
	butt.giveStory("After taking care of your hygenic duties, you decide what to do with the poor leaf you chose to sacrifice for the task. You glance "
		"at the ground, which is very loose and damp. You also see a nearby tree with a lot of moss growing on it.");
	// soil b choice path "bb"
	act.giveStory("Bold move deciding to act like something like that never happened. After walking away, you find a nearby creek, which could offer "
		"some much needed cleaning. You have also just seen a horific scene and think getting out of here might be the best choice.");
	// ---------------------------------------TIER 3------------------------------------------ //

	// ---------------------------------------TIER 4------------------------------------------ //
	// nectar b choice path "abb"
	// act b choice path "bbb"
	fountain.giveStory("After walking for a ways you see a break in the trees up ahead. A few more steps brings you to the clearing. In the clearing, you"
		" spot something quite dumbfounding. Right in the center of this clearing sits a beautifully hand-carved stone fountain. ^"
		" You walk quickly to the fountain. You stare deeply at your reflection in the bottom pool. You almost can't look away...");
	fountain.addStoryModifier("Some fresh, clean water would be perfect for the accident that happened in your pants earlier."
		, "bbb");
	fountain.addStoryModifier("It looks just like the one your father had made for the front garden of your family home."
		, "abb");
	// mushroom a choice path "aaa"
	fire.giveStory("There are probably no more than two to three hours of sunlight left, so starting a fire might be the best plan now. As you gather kindling "
		"you think you hear some foot steps and cracking twigs not that far from where you are. Is it an animal or could it possibly be another person?");
	// mushroom b choice path "aab"
	food.giveStory("You feel more hungry after eating that mushroom and think some more food after that appetizer might be a nice ending to this strange "
		"day. You vaguely remember hearing a stream a while ago, but you've also seen plenty of small game animals scurrying about.");
	// butt a choice path "baa"
	bury.giveStory("Burrying the evidence is cleanliest choice and saves you from any evidence of that embarrassing scene. Digging through the soil is easy "
		"as the first few scoops are mostly loose peat. As if anything more exciting than what's already happened today could happen, your fingers "
		"brush over something hard during your last scoop of soil. Leaving the dirty leaves alone, you dig until you uncover the object. It's a small "
		"wooden box. You open the box to find a folded piece of paper inside. You unfold it and read it. It has instructions on it.");
	// butt b choice path "bab"
	tree.giveStory("The tree can't cry for help. The tree can't express its disdain for the action you've just taken upon it. Someone must, because "
		"that was truly disgusting, so I, the narrator, will. Gross, you dirty homeless person. Shame on you.");
	// act a choice path "bba"
	cleanoff.giveStory("You descend the banks of the creek until you reach the water. A dip of your finger reveals a chilly surprise; this is not going "
		"to be fun to wash off with. As you clean off you catch movement beneath the water in the corner of your eye. There are some sizeable "
		"fish in this creek. Slightly above your focus, on the opposite bank of the creek, you see footsteps as well.");
	// nectar a choice path "aba"
	light.giveStory("The sun-ray-lit forest path entices you forward as you take a step into your future. A colored haze cascades from the canopy after "
		"walking for what seemed only to be a few seconds. Either your eyes are tricking you or the mysterious fog is morphing into shapes and figures."
		" Every instinct in your body is teling you to leave the forest path, but your curiosity is persuading you to continue.");
	// ---------------------------------------TIER 4------------------------------------------ //
    
    // ---------------------------------------TIER 5------------------------------------------ //
    // food a choice "aaba"
    // cleanoff a choice "bbaa"
    fishing.giveStory("The glint of the sun off the shiny scales of the fish below the surface is somehow making you very hungry. Without a spear or "
                      "sharp stick, you prepare your mind for the swift motion you are going to have to perform with your hands. Wading into the middle "
                      "of the creek carefully, the fish seem unphased by you. You stand rock still, staring and waiting for your moment. Suddenly, a "
                      "big fish swims right under your hands. This fish was different though; its scales were so colorful...");
    // food b choice "aabb"
    hunting.giveStory("You've seen the survival shows on TV. All you'll need for small game is some cord and some sticks and the perfect spot to place "
                      "the trap. You make the cord out of your shoelaces and start watching the rabbits scurry about in a small clearing near by."
                      " You observe a popular trail and start setting the trap. As you set the cord, you hear a lot of noise close by; it sounds "
                      "like a struggle - something big. Walking towards the noise, you find a deer with its antlers stuck in some wires. You could "
                      " kill it and have the best meal you've had in days, or set it free.");
    // fountain a choice "abba" and "bbba"
    keepLooking.giveStory("You keep staring at yourself in the deep blue fountain water. Nothing happens. I don't know what you were expecting.");
    // fountain b choice "abbb" and "bbbb"
    swipeWater.giveStory("You swipe at the water and it ripples throughout the pool. Suddenly the top of the fountain starts gurgling, as if it's "
                         "trying to pump water again. After a few seconds, water starts cascading down the three tiers of the fountain. It takes "
                         "some time at each pool to refill what has evaporated over time, but eventually it reaches the bottom pool.");
    // fire a choice "aaaa"
    shrugoff.giveStory("It's probably just small animals. You continue gathering fuel for you fire and carry it back to camp. As the sun sets and "
                       "your fire crackles, your mind wanders. You start to feel your eyelids get heavier and heavier with the warmth of the fire "
                       "soaking deeper into your body.");
    // fire b choice "aaab"
    investigate.giveStory("You don't want to find out that you aren't alone in these forests right before a relazxing night by the fire, so you"
                          " move towards the sounds you heard. You make your way around some thick bushes, and once you've made it around, you "
                          "look around. Sure enough, some rabbits and birds scatter when you pop your head around. You could have sworn it sounded "
                          "like something else though...");
    // bury a choice "baaa"
    followInstructions.giveStory("Against your better judgement, you decide to follow the instructions on the note; it's like someone or something "
                                 "else is compelling you to do it. You get up, find a river, and drown yourself.");
    // bury b choice "baab"
    tearNote.giveStory("You tear it up, but not without hesitation. Suddenly, a flying object appears over your head and pulls you up into it using "
                       "some kind of gravity beam technology.");
    // tree a choice "baba"
    whosThere.giveStory("You ask me, \"Who's there?\", but I already knew you were going to ask me that. It's me, God. Are you having fun on this adventure "
                        "yet?");
    // tree b choice "babb"
    dontJudge.giveStory("You say, \"Don't judge me! Who are you to look down at me?\". You really don't want to know who I am. The answer would terrify you "
                        "and your tiny human brain.");
    // cleanoff b choice "bbab" // a choice is above for the fishing object
    footsteps.giveStory("You wade across the creek to the footsteps. They are definitely not animal, but there is no indication of footwear - no patterns or "
                        "shoe shape - just an ellipse-like shape that comes to a dull point at one end. You follow them for a few minutes only to be "
                        "completely terrified by where it led you. You stand, once again, in front of the dead elf.");
    // light a choice "abaa"
    leavePath.giveStory("You hate having your mind play tricks on you so you leave the path. As soon as you step foot off the path, your chest is pierced by "
                        "an arrow. You slowly bleed out, as your vision goes black...");
    // light b choice "abab"
    continueOn.giveStory("You know your mind is stronger than this, so you push on. The hallucinations only get worse though, but your attitude toward them is "
                         "shifting; you embrace the visions.");
    // ---------------------------------------TIER 4------------------------------------------ //
}

void Game::linkQuestions() {
	elf.makeRoutes(&forest, &soil);
	// the current question should be set to the first question
	currentQuestion = &elf;

	forest.makeRoutes(&mushroom, &nectar);
	soil.makeRoutes(&butt, &act);

	mushroom.makeRoutes(&fire, &food);
	butt.makeRoutes(&bury, &tree);
	act.makeRoutes(&cleanoff, &fountain);
	nectar.makeRoutes(&light, &fountain);
    
    fire.makeRoutes(&shrugoff, &investigate);
    food.makeRoutes(&fishing, &hunting);
    bury.makeRoutes(&followInstructions, &tearNote);
    tree.makeRoutes(&whosThere, &dontJudge);
    cleanoff.makeRoutes(&fishing, &footsteps);
    fountain.makeRoutes(&keepLooking, &swipeWater);
    light.makeRoutes(&leavePath, &continueOn);
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

	string userInput = "", path = "";


	/*getline(cin, userInput);

	getline(cin, path);

	if (path == "" && userInput == "") {
	printOptions();
	//travelTo(userInput[0]);
	}
	else if (path == "" && userInput != "") {
	if (userInput[0] != 'a' && userInput[0] != 'b') {
	cout << "Enter 'a' or 'b' for your choice." << endl;
	}
	else {
	travelTo(userInput[0]);
	printOptions();
	}
	}
	else {
	for (int i = 0; i < path.length(); ++i) {
	if (path[i] != 'a' && path[i] != 'b') {
	cout << "A non 'a' or 'b' character found in the path." << endl;
	currentQuestion = nullptr;
	break;
	}
	else {
	travelTo(path[i]);
	if (currentQuestion == nullptr) {
	break;
	}
	}
	}

	if (currentQuestion != nullptr && (userInput[0] == 'a' || userInput[0] == 'b')) {
	travelTo(userInput[0]);
	if (currentQuestion != nullptr) {
	printOptions();
	}
	}
	else {
	cout << "Reached end of path or choice wasn't 'a' or 'b'." << endl;
	}
	}
	if (this->pathStr != "") {
	cout << "\n!!!Run again with the following:\nLine 1, your choice for this question.\nLine 2, input this code: " << this->pathStr << endl;
	}*/


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
