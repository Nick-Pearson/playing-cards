#ifndef SOLITAIREGAME_H
#define SOLITAIREGAME_H

#include "gamebase.h"

class CardStack;

class SolitaireGame : public GameBase
{
public:

  virtual ~SolitaireGame();

  virtual void SetupGame() override;

private:
  CardStack* cardstacks[7];
  CardStack* foundations[4];
  CardStack* deckstack;
};

#endif
