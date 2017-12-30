#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "cardtypes.h"

#include <vector>

class GameBase
{
public:
  GameBase() {}
  virtual ~GameBase() {}

  void Initialise();

  unsigned int GameSeed = 0;

protected:

  virtual void SetupGame() = 0;

public:
// game herlpers
  static void GetShuffledDeck(std::vector<CardDef>& outDeck, int numJokers = 0);

  static void Shuffle(std::vector<CardDef>& deck);

private:

  void InitGameSeed();

};

#endif
