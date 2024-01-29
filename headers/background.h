enum bg_steps {start, one, two};
enum bs_types {lab, volca, paral};
Texture background[3][3];
/*
enum paral_type {back,front};
Texture parals[2][2];

bool load_paral()
{
  parals[front][0]= SBDL::loadTexture( "./assets/pic/parallex/First P.png" );
  parals[front][1]= SBDL::loadTexture( "./assets/pic/parallex/First P2.png" );

  parals[back][1]= SBDL::loadTexture( "./assets/pic/parallex/Second P2.png" );
  parals[back][1]= SBDL::loadTexture( "./assets/pic/parallex/Second P2.png" );

  return true;
}
*/
bool load_background_texture()
{
    background[lab][start] = SBDL::loadTexture ("./assets/pic/back/Lab Start.png");
    background[lab][one] = SBDL::loadTexture ("./assets/pic/back/Lab1.png");
    background[lab][two] = SBDL::loadTexture ("./assets/pic/back/Lab2.png");
    background[volca][start] = SBDL::loadTexture ("./assets/pic/back/Volcano Start.png");
    background[volca][one] = SBDL::loadTexture ("./assets/pic/back/Volcano1.png");
    background[volca][two] = SBDL::loadTexture ("./assets/pic/back/Volcano2.png");
    background[paral][start] = SBDL::loadTexture ("./assets/pic/back/warehouse Start.png");
    background[paral][one] = SBDL::loadTexture ("./assets/pic/back/warehouse.png");
    background[paral][two] = SBDL::loadTexture ("./assets/pic/back/warehouse.png");
    //load_paral();
    return true;
}

bool show_background (bool restart =false)
{
    static long int first_x = 0;

    if (restart) {
        first_x=0;
    }

    first_x+=game_vx;
    long int came_x = 0;
    SBDL::showTexture (background[lab][start], first_x+came_x, 0);
    came_x+=background[lab][start].width;
    SBDL::showTexture (background[lab][one], first_x+came_x, 0);
    came_x+=background[lab][one].width;
    SBDL::showTexture (background[lab][two], first_x+came_x, 0);
    came_x+=background[lab][two].width;
    SBDL::showTexture (background[volca][start], first_x+came_x, 0);
    came_x+=background[volca][start].width;
    SBDL::showTexture (background[volca][one], first_x+came_x, 0);
    came_x+=background[volca][one].width;
    SBDL::showTexture (background[volca][two], first_x+came_x, 0);
    came_x+=background[volca][two].width;
    SBDL::showTexture (background[paral][start], first_x+came_x, 0);
    came_x+=background[paral][start].width;
    SBDL::showTexture (background[paral][one], first_x+came_x, 0);
    came_x+=background[paral][one].width;
    SBDL::showTexture (background[paral][two], first_x+came_x, 0);
    came_x+=background[paral][two].width;
    SBDL::showTexture (background[lab][start], first_x+came_x, 0);
    first_x %= came_x;
    return true;
}
