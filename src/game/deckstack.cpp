#include "deckstack.h"

DeckStack::DeckStack(const std::vector<CardDef>& inDeck, unsigned int startIndex /*= 0*/, unsigned int count /*= 0*/) :
  CardStack(inDeck, startIndex, count)
{
  StackSpacing = glm::vec3(-0.1f, -0.05f, 0.0f);
  emptycard_def = CardDef(Suit::S_None, CardType::EndOfDeck, CardFace::FaceUp);

  offsetStack = new CardStack();
  offsetStack->StackSpacing = glm::vec3(-8.0f, 0.0f, 0.0f);
  offsetStack->SetEmptyCardVisible(false);

  pileStack = new CardStack();
  pileStack->StackSpacing = glm::vec3(0.0f, 0.0f, 0.0f);
  pileStack->SetEmptyCardVisible(false);

  SetRootLocation(m_Location);
}

DeckStack::~DeckStack()
{
  delete offsetStack;
  delete pileStack;
}

void DeckStack::SetRootLocation(const glm::vec3& newPosition)
{
  CardStack::SetRootLocation(newPosition);

  offsetStack->SetRootLocation(m_Location + glm::vec3(48.0f, 0.0f, 0.0f));
  pileStack->SetRootLocation(m_Location + glm::vec3(40.0f, 0.0f, 0.0f));
}

void DeckStack::OnClicked(double mouseX, double mouseY, int button, int action, int mods)
{
  if(action != 0)
    return;


  //pop all from the offset stack onto the deck stack
  std::vector<CardDef> cards;
  offsetStack->PopCards(offsetStack->Size(), cards);
  for(int i = cards.size() - 1; i >= 0; --i)
    pileStack->PushCard(cards[i]);


  if(Size() == 0)
  {
    //reset the deck
    std::vector<CardDef> deckCards;
    pileStack->PopCards(pileStack->Size(), deckCards);

    for(unsigned int i = 0; i < deckCards.size(); i++)
    {
      deckCards[i].facing = CardFace::FaceDown;
    }
    PushCards(deckCards);
  }
  else
  {
    std::vector<CardDef> deckCards;
    PopCards(DrawCount, deckCards);

    for(unsigned int i = 0; i < deckCards.size(); ++i)
    {
      deckCards[i].facing = CardFace::FaceUp;

      if(i == 0)
        pileStack->PushCard(deckCards[i]);
      else
        offsetStack->PushCard(deckCards[i]);
    }
  }
}
