#include <QtWidgets/QApplication>
#include "AdminConsole.h"
#include "CartConsole.h"

#include "Domain.h"
#include "Repo.h"
#include "Cart.h"
#include "Console.h"
#include "TestDomain.h"	
#include "TestRepo.h"
#include "TestFileRepo.h"
#include "TestUtils.h"
#include "TestValidators.h"
#include "TestService.h"
#include "TestVector.h"
#include "TestCart.h"

void run_tests() {
	TestVector test_vector;
	test_vector.run_all_tests();

	run_all_tests_domain();

	TestRepo test_repo;
	test_repo.run_all_tests_repo();

	TestFileRepo test_file_repo;
	test_file_repo.run_all_tests_repo();

	run_all_tests_utils();

	TestValidators test_validator{};
	test_validator.run_all_tests_validators();

	TestService test_service;
	test_service.run_all_tests_service();

	TestCart test_cart;
	test_cart.run_all_tests_cart();

	qDebug() << "All tests passed! ";
}

int main(int argc, char *argv[]){
	run_tests();
	FileRepoMovies repo_movies{ "movies_file.csv" };
	ValidatorMovie validator_movies;
	CartMovies cart_movies;
	Service service{ repo_movies, cart_movies, validator_movies };

	QApplication a(argc, argv);

	AdminConsole console{service};
	console.show();


    return a.exec();
}