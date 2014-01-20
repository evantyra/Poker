/* Title: Project 1 ECE373 Example driver artifact for Display class
 * Author: John Shield
 * Description: Demonstrates Unix Signal capturing and the Display class
 *		functionality.
 *
 * NOTES:
 *      * Requires the terminal (Putty) to be set to UTF-8.
 *      * Does not function when running a screen session.
 */
#include "display.h"
#include <signal.h>
#include <ncurses.h>
#include <cstdlib>
#include <sstream>

using namespace std;

/* No Header file for this example driver artifact
 * function declaration here instead.
 */
// Signal Subroutine for Window Resize
static void detectResize (int sig);
// stub artifact for what the game does when the screen resizes
void stub_PrintResize(void);

// The gameDisplay object is global, because the static signal handler object
// needs to access the dynamic object.
display gameDisplay;

/*
 * This is the main function that starts the driver artifact.
 * This function demonstrates some of the abilities of the Display class
 */
int main(int argc, char* argv[])
{
	// using a stringstream rather than a string to make making the banner easier
	stringstream messageString;

	// enable a interrupt triggered on a window resize
	signal(SIGWINCH, detectResize); // enable the window resize signal

/* You can uncomment and change the colors for various cards here*/
//    init_pair(1, COLOR_CYAN, COLOR_BLACK); // for card outline
//    init_pair(2, COLOR_BLUE, COLOR_BLACK); // for spades and clubs
//    init_pair(3, COLOR_RED, COLOR_BLACK);  // for hearts and diamonds
//    init_pair(4, COLOR_GREEN, COLOR_BLACK); // for turned over card
//    init_pair(5, COLOR_GREEN, COLOR_BLACK); // for box drawing
//    init_pair(6, COLOR_GREEN, COLOR_BLACK); // for banner display

	int currentBid = 0;
	int input;
	stringstream bannerText;
	bannerText << "f:fold;  c:call/check;  a:all in;  current bid: " + currentBid;
	gameDisplay.bannerBottom(bannerText.str());

	gameDisplay.displayCard(1, 1, 2, 5, 0);

	while (1) {
		input = gameDisplay.captureInput();

		switch (input) {
		case '0': case '1': case '2':
		case '3': case '4': case '5':
		case '6': case '7': case '8':
		case '9':
			currentBid = (currentBid) * 10 + (input - '0');
			bannerText.str("");
			bannerText << "f:fold; c:call/check; a:all in; current bid: " << currentBid;
			gameDisplay.bannerBottom(bannerText.str());
			break;

		case 'f': case 'F':
			return -1;

		case 'c': case 'C':
			return -1;

		case 'a': case 'A':
			return -2;

		case '\r': case 'b': case 'B':
			return currentBid;
		}
	}

	return 0;
}

/*
 * This is the interrupt service routine called when the resize screen
 * signal is captured.
 */
void detectResize(int sig) {
	// update the display class information with the new window size
    gameDisplay.handleResize(sig);
	// re-enable the interrupt for a window resize
    signal(SIGWINCH, detectResize);
	/*INSERT YOUR OWN SCREEN UPDATE CODE instead of stub_PrintResize*/
	stub_PrintResize();
}

/*
 * This is a simple stub that should be replaced with what the game does
 * when the screen resizes.
 */
void stub_PrintResize(void) {
	// gets the new screen size
	int cols = gameDisplay.getCols();
	int lines = gameDisplay.getLines();
	// setups a message stream
	stringstream messageString;
	messageString << "Terminal is " << cols << "x" << lines;
	// prints out the information of the new screen size in a top banner
	gameDisplay.bannerTop(messageString.str());
}

