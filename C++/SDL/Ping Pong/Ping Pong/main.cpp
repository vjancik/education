#include "functions.h"
int main( int argc, char* args[] )
{
	if( init() == false ) return 1;
	if( load_files() == false ) return 1;
	if( initrender() == false ) return 1;
	cycle();
	clean_up();
	return 0;
}