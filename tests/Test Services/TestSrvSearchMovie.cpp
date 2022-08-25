#include "TestService.h"


void TestService::test_check_for_movie() {
	std::ofstream fout("test_movie_file.csv");
	fout.close();
	srv.srv_add_movie("No time to die", "Action", "2021", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action", "2015", "D. Craig");

	assert(srv.search_movie("No time to die", "Action", "2021", "Daniel Craig") == true);
	assert(srv.search_movie("No time to die", "Action", "2021", "D. Craig") == false);
	assert(srv.search_movie("Spectre", "Action", "2015", "D. Craig") == true);

	srv.srv_delete_movie("No time to die", "Action", "2021", "Daniel Craig");
	srv.srv_delete_movie("Spectre", "Action", "2015", "D. Craig");
}