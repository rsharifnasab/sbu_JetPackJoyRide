

enum bg_steps {start,one,two};
enum bs_types {lab,volca,paral};
Texture background[3][3];

bool load_background_texture() // TODO
{
  background[lab][start] = SBDL::loadTexture( "./assets/pic/back/Lab Start.png" );
  background[lab][one] = SBDL::loadTexture( "./assets/pic/back/Lab1.png" );
  background[lab][two] = SBDL::loadTexture( "./assets/pic/back/Lab2.png" );

  background[volca][start] = SBDL::loadTexture( "./assets/pic/back/Volcano Start.png" );
  background[volca][one] = SBDL::loadTexture( "./assets/pic/back/Volcano1.png" );
  background[volca][two] = SBDL::loadTexture( "./assets/pic/back/Volcano2.png" );

  background[paral][start] = SBDL::loadTexture( "./assets/pic/back/warehouse Start.png" );
  background[paral][one] = SBDL::loadTexture( "./assets/pic/back/warehouse.png" );
  background[paral][two] = SBDL::loadTexture( "./assets/pic/back/warehouse.png" );

  return true;
}


bool show_background()
{

    return true;
}
