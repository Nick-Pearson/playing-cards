#ifndef DECKSTACK_H
#define DECKSTACK_H

#include "cardstack.h"

class DeckStack : public CardStack
{
public:
  DeckStack(const std::vector<CardDef>& inDeck, unsigned int startIndex = 0, unsigned int count = 0);
  virtual ~DeckStack();

  virtual void SetRootLocation(const glm::vec3& newPosition) override;

  virtual void OnClicked(double mouseX, double mouseY, int button, int action, int mods) override;
  
  int DrawCount = 3;
private:
  CardStack* offsetStack;
  CardStack* pileStack;
};

#endif
