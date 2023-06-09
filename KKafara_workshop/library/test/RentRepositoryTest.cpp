//
// Created by student on 11.04.2022.
//

#include <boost/test/unit_test.hpp>

#include "model/Rent.h"
#include "model/Client.h"
#include "model/Vehicle.h"
#include "model/Rent.h"
#include "model/Bicycle.h"
#include "repositories/StorageContainer.h"

using std::make_shared;

bool test(rentPtr rent) {
    return rent->getId() == 1;
}

BOOST_AUTO_TEST_SUITE(TestSuiteRentRepository)

    BOOST_AUTO_TEST_CASE(RentRepositoryAddTest) {
        StorageContainer storage;
        BOOST_TEST_REQUIRE(storage.getRentRepo().size() == 1);
        clientPtr client = make_shared<Client>("Kacper", "Kafara", "242412", nullptr, nullptr);
        bicyclePtr vehicle = make_shared<Bicycle>("WLS", 123);
        rentPtr rent = make_shared<Rent>(2, client, vehicle, boost::date_time::not_a_date_time);
        storage.getRentRepo().add(rent);
        BOOST_TEST(storage.getRentRepo().size() == 2);
    }

    BOOST_AUTO_TEST_CASE(RentRepositoryRemoveTest) {
        StorageContainer storage;
        clientPtr client = make_shared<Client>("Kacper", "Kafara", "242412", nullptr, nullptr);
        bicyclePtr vehicle = make_shared<Bicycle>("WLS", 123);
        rentPtr rent = make_shared<Rent>(2, client, vehicle, boost::date_time::not_a_date_time);
        storage.getRentRepo().add(rent);
        storage.getRentRepo().remove(rent);
        BOOST_TEST(storage.getRentRepo().size() == 1);
    }

    BOOST_AUTO_TEST_CASE(RentRepositoryFindAllTest) {
        StorageContainer storage;
        clientPtr client = make_shared<Client>("Kacper", "Kafara", "242412", nullptr, nullptr);
        bicyclePtr vehicle = make_shared<Bicycle>("WLS", 123);
        rentPtr rent = make_shared<Rent>(2, client, vehicle, boost::date_time::not_a_date_time);
        storage.getRentRepo().add(rent);
        BOOST_TEST(storage.getRentRepo().findAll().size() == 2);
    }

    BOOST_AUTO_TEST_CASE(RentRepositoryFindByTest) {
        StorageContainer storage;
        clientPtr client = make_shared<Client>("Kacper", "Kafara", "242412", nullptr, nullptr);
        bicyclePtr vehicle = make_shared<Bicycle>("WLS", 123);
        rentPtr rent = make_shared<Rent>(2, client, vehicle, boost::date_time::not_a_date_time);
        storage.getRentRepo().add(rent);
        BOOST_TEST(storage.getRentRepo().findBy(test).at(0)->getId() == 1);
    }


BOOST_AUTO_TEST_SUITE_END()