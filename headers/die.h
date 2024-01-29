bool hide_it()  //remove cause of death
{
    enemy.x = -1000;
    enemy.type =Ecoin;
    return true;
}

bool die()
{
    if (enemy.type==Elaser && enemy.this_tex<2) {
        return true;    //laser inactive
    }

    hide_it();

    if (barry.speed_token) {
        return true;
    }

    if (barry.suit==Sgravity) {
        barry.suit = barry.last_suit;
        play_sound (static_cast<sound_type> (2+barry.g_revers));
        barry.g_revers = false;
        return true;
    }

    std::cout << "dying! enemy type : "<< enemy.type <<" this_tex : "<<enemy.this_tex<<"\n";
    menu("lose");
    return true;
}
