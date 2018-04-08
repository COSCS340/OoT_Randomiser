#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "custom_colors.h"

#define GAME_SIZE 67108864
#if 0

int main( int argc, char** argv) {
	unsigned char *game;
	unsigned char **game_ptr;
	game = ( unsigned char* ) malloc( GAME_SIZE );

	ifstream input;
    ofstream output;

	input.open( argv[1], ios::binary );
	input.read( reinterpret_cast<char*>(game), GAME_SIZE );
	input.close();

	game_ptr = &game;
    
	custom_colors( game_ptr );

    output.open( "newzoot.z64", ios::binary );
	output.write( reinterpret_cast<const char*>(game), GAME_SIZE );
    
	free(game);


	return 0;
}
#endif
