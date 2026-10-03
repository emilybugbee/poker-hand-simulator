// Copyright (c) 2024 Nathan Greenfield. All rights reserved
#include "cards.h"

// For the sort function
#include <algorithm>

// Function: Constructor
// Purpose: Draws 5 cards from the supplied deck, and sorts them
// by rank
// Input: Takes in a smcVector of cards for the deck
// Returns: Nothing
PokerHand::PokerHand(smcVector<Card>& deck)
{
	// Draws five cards
	for (int i = 0; i < 5; i++)
	{
		// Adds the top card on the deck to mHand
		mHand.push_back(deck.back());
		// Discards the top card
		deck.pop_back();
	}
	// Sorts the five cards in mHand
	sortHand();
}

// Function: getBestPokerHand
// Purpose: Returns a string describing the poker hand this PokerHand
// contains
// Input: None
// Returns: The name of the best poker hand
std::string PokerHand::getBestPokerHand() const
{
	// Empty string to hold text for the best poker hand
	std::string bestHand;
	// Hand has a straight flush if it has both a straight and a flush
	if (hasStraight() && hasFlush())
	{
		bestHand = "straight flush";
	}
	else if (hasStraight())
	{
		bestHand = "straight";
	}
	else if (hasFlush())
	{
		bestHand = "flush";
	}
	else if (hasFourOfAKind())
	{
		bestHand = "four of a kind";
	}
	else if (hasFullHouse())
	{
		bestHand = "full house";
	}
	else if (hasThreeOfAKind())
	{
		bestHand = "three of a kind";
	}
	else if (hasTwoPairs())
	{
		bestHand = "two pairs";
	}
	else if (hasPair())
	{
		bestHand = "pair";
	}
	else
	{
		bestHand = "high card";
	}
	return bestHand;
}

// Function: hasStraight
// Purpose: Determines if the hand has a straight
// Input: None
// Returns: true if there's a straight
bool PokerHand::hasStraight() const
{
	// Iterates through lowest four cards
	for (int i = 0; i < 4; i++)
	{
		// Checks if current card is the rank under the next card
		if (mHand[i].mRank == mHand[i + 1].mRank - 1)
		{
			continue;
		}
		// Returns false if cards are not in sequence
		else
		{
			return false;
		}
	}
	// True if all five cards are in sequential rank
	return true;
}

// Function: hasFlush
// Purpose: Determines if the hand has a flush
// Input: None
// Returns: true if there's a flush
bool PokerHand::hasFlush() const
{
	// Iterates through last four cards
	for (int i = 1; i < 5; i++)
	{
		// Checks if the last four cards have the same suit as the first card
		if (mHand[i].mSuit == mHand[0].mSuit)
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	// True if all five cards have the same suit
	return true;
}

// Function: hasFourOfAKind
// Purpose: Determines if the hand has a 4 of a kind
// Input: None
// Returns: true if there's a 4 of a kind
bool PokerHand::hasFourOfAKind() const
{
	// Compares lowest four card ranks
	for (int i = 1; i < 4; i++)
	{
		// Continues if card ranks are the same
		if (mHand[i].mRank == mHand[0].mRank)
		{
			continue;
		}
		else
		{
			// If xxxxy is false, checks for xyyyy
			// Compares highest four card ranks
			for (int i = 2; i < 5; i++)
			{
				if (mHand[i].mRank == mHand[1].mRank)
				{
					continue;
				}
				else
				{
					return false;
				};
			}
		}
	}
	// True if card ranks are xxxxy or xyyyy
	return true;
}

// Function: hasFullHouse
// Purpose: Determines if the hand has a full house
// Input: None
// Returns: true if there's a full house
bool PokerHand::hasFullHouse() const
{
	// Checks if card ranks are xxxyy
	if (mHand[0].mRank == mHand[1].mRank && mHand[0].mRank == mHand[2].mRank && mHand[3].mRank == mHand[4].mRank)
	{
		return true;
	}
	// Checks if card ranks are xxyyy
	else if (mHand[0].mRank == mHand[1].mRank && mHand[2].mRank == mHand[3].mRank && mHand[2].mRank == mHand[4].mRank)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Function: hasThreeOfAKind
// Purpose: Determines if the hand has a three of a kind
// Input: None
// Returns: true if there's a three of a kind
bool PokerHand::hasThreeOfAKind() const
{
	// Checks if card ranks are xxxyz
	if (mHand[0].mRank == mHand[1].mRank && mHand[0].mRank == mHand[2].mRank)
	{
		return true;
	}
	// Checks if card ranks are xyyyz
	else if (mHand[1].mRank == mHand[2].mRank && mHand[1].mRank == mHand[3].mRank)
	{
		return true;
	}
	// Checks if card ranks are xyzzz
	else if (mHand[2].mRank == mHand[3].mRank && mHand[2].mRank == mHand[4].mRank)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Function: hasTwoPairs
// Purpose: Determines if the hand has two pairs
// Input: None
// Returns: true if there's two pairs
bool PokerHand::hasTwoPairs() const
{
	// Checks if card ranks are xxyyz
	if (mHand[0].mRank == mHand[1].mRank && mHand[2].mRank == mHand[3].mRank)
	{
		return true;
	}
	// Checks if card ranks are xyyzz
	else if (mHand[1].mRank == mHand[2].mRank && mHand[3].mRank == mHand[4].mRank)
	{
		return true;
	}
	// Checks if card ranks are xxyzz
	else if (mHand[0].mRank == mHand[1].mRank && mHand[3].mRank == mHand[4].mRank)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Function: hasPair
// Purpose: Determines if there's a pair
// Input: None
// Returns: true if there's a pair
bool PokerHand::hasPair() const
{
	// Iterates through lowest four cards
	for (int i = 0; i < 4; i++)
	{
		// Checks if current card rank is the same as next card
		if (mHand[i].mRank == mHand[i + 1].mRank)
		{
			// True if pair is found
			return true;
		}
	}
	// Returns false if pair not found
	return false;
}

void PokerHand::sortHand()
{
	// Iterates through each card in hand
	for (int i = 0; i < 5; i++)
	{
		// Sets minCard to the current card
		Card minCard = mHand[i];
		// Sets minIndex to the current index
		int minIndex = i;
		// Iterates through every card following the current one
		for (int j = i + 1; j < 5; j++)
		{
			// If the current card is less than the current minimum
			if (mHand[j] < minCard)
			{
				// Change the minimum card to the current card
				minCard = mHand[j];
				// Change the minimum index to the current index
				minIndex = j;
			}
		}
		// Holds original card
		Card temp = mHand[i];
		// Replaces original card with minimum card
		mHand[i] = minCard;
		// Places the original card where minimum used to be
		mHand[minIndex] = temp;
	}
}

// Function: createDeck
// Purpose: Given an empty smcVector of Cards, inserts a
// standard 52 card deck and shuffles it
// Input: An smcVector of Cards (by reference)
// Returns: nothing
void createDeck(smcVector<Card>& deck, std::mt19937& g)
{
	// Iterates through each rank in a deck
	for (int i = 2; i < 15; i++)
	{
		deck.push_back(Card(i, CLUBS));
		deck.push_back(Card(i, DIAMONDS));
		deck.push_back(Card(i, HEARTS));
		deck.push_back(Card(i, SPADES));
	}
	// Shuffle the deck
	std::sort(&deck[0], &deck[0] + deck.size());
	std::shuffle(&deck[0], &deck[0] + deck.size(), g);
}

// Function: << operator for Card
// Purpose: Outputs the name and suit of the card
// Input: ostream and card
// Returns: ostream, with card data output to it
std::ostream& operator<<(std::ostream& os, const Card& card)
{
	// Outputs "Ace" if card rank is 14
	if (card.mRank == 14)
	{
		os << "Ace";
	}
	// Outputs "King" if card rank is 13
	else if (card.mRank == 13)
	{
		os << "King";
	}
	// Outputs "Queen" if card rank is 12
	else if (card.mRank == 12)
	{
		os << "Queen";
	}
	// Outputs "Jack" if card rank is 11
	else if (card.mRank == 11)
	{
		os << "Jack";
	}
	else
	{
		os << card.mRank;
	}
	os << " of ";
	if (card.mSuit == CLUBS)
	{
		os << "Clubs";
	}
	else if (card.mSuit == DIAMONDS)
	{
		os << "Diamonds";
	}
	else if (card.mSuit == HEARTS)
	{
		os << "Hearts";
	}
	else if (card.mSuit == SPADES)
	{
		os << "Spades";
	}
	return os;
}


// Function: < comparison operator for Card
// Purpose: Compares the value of the left and right card
// Input: Two cards to compare
// Returns: true if left < right
bool operator<(const Card& left, const Card& right)
{
	// Compares suits if ranks are equal
	if (left.mRank == right.mRank)
	{
		return left.mSuit < right.mSuit;
	}
	return left.mRank < right.mRank;
}

// Function: > comparison operator for Card
// Purpose: Compares the value of the left and right card
// Input: Two cards to compare
// Returns: true if left > right
bool operator>(const Card& left, const Card& right)
{
	// Compares suits if ranks are equal
	if (left.mRank == right.mRank)
	{
		return left.mSuit > right.mSuit;
	}
	return left.mRank > right.mRank;
}

// Function: << operator
// Purpose: Prints out the hand
std::ostream& operator<<(std::ostream& os, const PokerHand& hand)
{
	os << "{ ";
	// Prints first four cards
	for (int i = 0; i < 4; i++)
	{
		os << hand.mHand[i] << ", ";
	}
	// Prints last card
	os << hand.mHand[4] << " }";
	return os;
}
