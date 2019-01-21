

bool die()
{
  if(barry.suit==Sgravity)
  {
    barry.suit = barry.last_suit;
    barry.g_revers = false;
    return true;
  }
  if(barry.speed_token) {return true;}
  menu("die");

  return true;
}
