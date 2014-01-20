#include <string>
#include "display.h"
#include "Card.h"
#include "Hand.h"
#include "Player.h"

using namespace std;

Player::Player(int displayPos, int initialMoney) :
	displayPosition(displayPos),
	money(initialMoney),
	moneyInPot(0),
	hasFolded(false)
	{
}

Player::~Player() {

}

Hand* Player::getHand() {
    return hand;
}

void Player::setHand(Hand *newHand) {
    hand = newHand;
}

int Player::getMoney() {
    return money;
}

int Player::getMoneyInPot() {
    return moneyInPot;
}

void Player::setMoneyInPot(int amount) {
    moneyInPot = amount;
}

int Player::giveMoney(int amount) {
    money += amount;
    return money;
}

void Player::setMoney(int amount) {
    money = amount;
}

void Player::setFrame(Frame* newFrame) {
    frame = newFrame;
}

Frame* Player::getFrame() {
    return frame;
}
bool Player::folded() {
    return hasFolded;
}

void Player::setFolded(bool fold) {
    hasFolded = fold;
}

void Player::setDisplayPosition(int position) {
    displayPosition = position;
}

int Player::getDisplayPosition() {
    return displayPosition;
}

int Player::ante(int anteAmount, display gameDisplay) {
    int ante = (money > anteAmount) ? anteAmount : money;
    money -= ante;
    moneyInPot += ante;
    return ante;
}
