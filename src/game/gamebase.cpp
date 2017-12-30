#include "gamebase.h"

#include <cstdlib>
#include <time.h>

void GameBase::Initialise()
{
  InitGameSeed();

  SetupGame();
}

void GameBase::GetShuffledDeck(std::vector<CardDef>& outDeck, int numJokers /*= 0*/)
{
  outDeck.reserve(52 + numJokers);

  for(int i = 0; i < 52; ++i)
  {
    Suit suit = (Suit)((int)Suit::S_Clubs + (i % 4));
    CardType card = (CardType)((int)CardType::Ace + (i % 13));
    outDeck.push_back(CardDef(suit, card));
  }

  for(int i = 0; i < numJokers; ++i)
  {
    outDeck.push_back(CardDef(Suit::S_None, CardType::Joker));
  }

  Shuffle(outDeck);
}

void GameBase::Shuffle(std::vector<CardDef>& deck)
{
  for(int i = deck.size() - 1; i >= 1; --i)
  {
    int j = rand() % (i + 1); //inclusive range

    CardDef tmp = deck[i];
    deck[i] = deck[j];
    deck[j] = tmp;
  }
}

void GameBase::InitGameSeed()
{
  if(GameSeed == 0)
  {
    time_t t;
    GameSeed = (unsigned) time(&t);
  }

  srand(GameSeed);
}
