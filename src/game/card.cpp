#include "card.h"

#include "texturemanager.h"

Card::Card(CardDef definition)
{
  m_Definition = definition;
  UpdateTexture();

  transform.SetScale(glm::vec3(14.0f, 19.0f, 1.0f));
}

Card::Card(const Card* other) : Sprite(other)
{
  m_Definition = other->m_Definition;
  UpdateTexture();
}

void Card::SetSuit(Suit newSuit)
{
  m_Definition.suit = newSuit;
  UpdateTexture();
}

void Card::SetCard(CardType newCard)
{
  m_Definition.cardType = newCard;
  UpdateTexture();
}

void Card::Flip()
{
  if(IsFaceUp()) m_Definition.facing = CardFace::FaceDown;
  else m_Definition.facing = CardFace::FaceUp;
}

void Card::UpdateTexture()
{
  if(m_Definition.facing == CardFace::FaceDown)
  {
    SetAtlasTexture(gTextureManager->FindOrLoadTexture("playingCardBacks.png"), gTextureManager->GetTileCoords("playingCardBacks.csv", "cardBack_blue2"));
    return;
  }

  std::string tileID = "card";

  switch(m_Definition.suit)
  {
  case Suit::S_Clubs:
    tileID.append("Clubs");
    break;
  case Suit::S_Hearts:
    tileID.append("Hearts");
    break;
  case Suit::S_Spades:
    tileID.append("Spades");
    break;
  case Suit::S_Diamonds:
    tileID.append("Diamonds");
    break;
  case Suit::S_None:
    break;
  }

  switch(m_Definition.cardType)
  {
  case CardType::Joker:
    tileID.append("Joker");
    break;
  case CardType::C_None:
    tileID.append("None");
    break;
  case CardType::Ace:
    tileID.append("A");
    break;
  case CardType::Two:
    tileID.append("2");
    break;
  case CardType::Three:
    tileID.append("3");
    break;
  case CardType::Four:
    tileID.append("4");
    break;
  case CardType::Five:
    tileID.append("5");
    break;
  case CardType::Six:
    tileID.append("6");
    break;
  case CardType::Seven:
    tileID.append("7");
    break;
  case CardType::Eight:
    tileID.append("8");
    break;
  case CardType::Nine:
    tileID.append("9");
    break;
  case CardType::Ten:
    tileID.append("10");
    break;
  case CardType::Jack:
    tileID.append("J");
    break;
  case CardType::Queen:
    tileID.append("Q");
    break;
  case CardType::King:
    tileID.append("K");
    break;
  }

  SetAtlasTexture(gTextureManager->FindOrLoadTexture("playingCards.png"), gTextureManager->GetTileCoords("playingCards.csv", tileID));
}
