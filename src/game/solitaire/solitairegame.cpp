#include "solitairegame.h"

#include "renderer.h"
#include "card.h"
#include "cardstack.h"

#include <memory>

SolitaireGame::~SolitaireGame()
{
  for(int i = 0; i < 7; ++i)
    delete cardstacks[i];

  for(int i = 0; i < 7; ++i)
    delete foundations[i];

  delete deckstack;
}

void SolitaireGame::SetupGame()
{
  gRenderer->SetGameAreaSize(247.0f, 247.0f);

  // FOUNDATIONS
  for(int i = 0; i < 4; ++i)
  {
    foundations[i] = new CardStack();
    foundations[i]->SetRootLocation(glm::vec3(122.0f + (i * 34.0f), 247.0f - 25.0f, 0.0f));
    foundations[i]->StackSpacing = glm::vec3(0.0f, 0.0f, 0.0f);
  }

  std::vector<CardDef> deck;
  GetShuffledDeck(deck);

  // PLAY AREA
  for(int i = 0; i < 7; ++i)
  {
    std::vector<CardDef> stackCards;

    for(int j = 0; j < i + 1; ++j)
    {
      CardDef card = deck.back();
      card.facing = (j == i) ? CardFace::FaceUp : CardFace::FaceDown;

      stackCards.push_back(card);
      deck.pop_back();
    }

    cardstacks[i] = new CardStack(stackCards);
    cardstacks[i]->SetRootLocation(glm::vec3(20.0f + (i * 34.0f), 247.0f - 69.0f, 0.0f));
  }

  // REST OF DECK
  deckstack = new CardStack(deck);
  deckstack->StackSpacing = glm::vec3(-0.1f, -0.05f, 0.0f);
  deckstack->SetRootLocation(glm::vec3(20.0f, 247.0f - 25.0f, 0.0f));
}
