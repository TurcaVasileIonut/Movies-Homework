#include "TestDomain.h"


void test_gets() {
	Movie m{ "No time to die", "Action", 2021, "Daniel Craig" };
	assert(m.get_title() == "No time to die");
	assert(m.get_gen() == "Action");
	assert(m.get_year() == 2021);
	assert(m.get_actor() == "Daniel Craig");
}

void test_set_features() {
	Movie m{ "No time to die", "Action", 2021, "Daniel Craig" };
	assert(m.get_title() == "No time to die");
	assert(m.get_gen() == "Action");
	assert(m.get_year() == 2021);
	assert(m.get_actor() == "Daniel Craig");

	m.set_title("Spectre");
	assert(m.get_title() == "Spectre");
	assert(m.get_gen() == "Action");
	assert(m.get_year() == 2021);
	assert(m.get_actor() == "Daniel Craig");

	m.set_gen("Spy");
	assert(m.get_title() == "Spectre");
	assert(m.get_gen() == "Spy");
	assert(m.get_year() == 2021);
	assert(m.get_actor() == "Daniel Craig");

	m.set_year(2015);
	assert(m.get_title() == "Spectre");
	assert(m.get_gen() == "Spy");
	assert(m.get_year() == 2015);
	assert(m.get_actor() == "Daniel Craig");

	m.set_actor("D. Craig");
	assert(m.get_title() == "Spectre");
	assert(m.get_gen() == "Spy");
	assert(m.get_year() == 2015);
	assert(m.get_actor() == "D. Craig");
}

void test_movie_string() {
	Movie m{ "No time to die", "Action", 2021, "Daniel Craig" };
	assert(m.string_movie() == "No time to die Action 2021 Daniel Craig");

	Movie m1{ "Spectre", "Action2", 2015, "D. Craig" };
	assert(m1.string_movie() == "Spectre Action2 2015 D. Craig");
}

void test_equal_operator_on_movies() {
	Movie m{ "No time to die", "Action", 2021, "Daniel Craig" };
	Movie m1{ "Spectre", "Action2", 2015, "D. Craig" };

	assert(!(m == m1));

	Movie m2{ "No time to die", "Action", 2021, "Daniel Craig" };
	assert(m == m2);
}

void test_assignment_operator() {
	Movie m{ "No time to die", "Action", 2021, "Daniel Craig" };
	Movie m1{ "Spectre", "Action2", 2015, "D. Craig" };

	assert(!(m == m1));

	m1 = m;
	assert(m == m1);

}

void run_all_tests_domain() {
	test_gets();
	test_set_features();
	test_movie_string();
	test_equal_operator_on_movies();
	test_assignment_operator();
}