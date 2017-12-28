#include "card.h"

#include "texturemanager.h"

Card::Card(CardType card, Suit suit, CardFace facing /*= CardFace::FaceUp*/)
{
  m_Card = card;
  m_Suit = suit;
  m_Facing = facing;
  UpdateTexture();
}

void Card::SetSuit(Suit newSuit)
{
  m_Suit = newSuit;
  UpdateTexture();
}

void Card::SetCard(CardType newCard)
{
  m_Card = newCard;
  UpdateTexture();
}

void Card::Flip()
{
  if(IsFaceUp()) m_Facing = CardFace::FaceDown;
  else m_Facing = CardFace::FaceUp;
}

void Card::UpdateTexture()
{
  if(m_Facing == CardFace::FaceDown)
  {
    SetAtlasTexture(gTextureManager->FindOrLoadTexture("playingCardBacks.png"), gTextureManager->GetTileCoords("playingCardBacks.csv", "cardBack_blue2"));
    return;
  }

  std::string tileID = "card";

  if(m_Card != CardType::Joker)
  {
    switch(m_Suit)
    {
    case Suit::Clubs:
      tileID.append("Clubs");
      break;
    case Suit::Hearts:
      tileID.append("Hearts");
      break;
    case Suit::Spades:
      tileID.append("Spades");
      break;
    case Suit::Diamonds:
      tileID.append("Diamonds");
      break;
    }
  }

  switch(m_Card)
  {
  case CardType::Joker:
    tileID.append("Joker");
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
