bool hide_it()
{
  enemy.x = -1000;
  enemy.type =Ecoin;
  return true;
}

bool die()
{
  if(barry.speed_token)
  { hide_it();
    return true;
  }
  if(enemy.type==Elaser && enemy.this_tex<2) return true;
  if(barry.suit==Sgravity)
  {
    barry.suit = barry.last_suit;
    barry.g_revers = false;
    hide_it();
    return true;
  }
  std::cout << "dying! enemy type : "<< enemy.type <<" this_tex : "<<enemy.this_tex<<"\n";
  menu("die");

  return true;
}
