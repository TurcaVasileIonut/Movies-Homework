#include "TestService.h"


void TestService::run_all_tests_service() {
	test_add_movie_feature();
	test_delete_movie_feature();
	test_change_movie_feature();
	test_check_for_movie();
	test_filter_by_title();
	test_filter_by_year();
	test_sorting();
	test_cart();
	test_undo(); 
}