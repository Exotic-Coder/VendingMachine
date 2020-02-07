#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include "include/machine.h"
#include "include/items.h"
#include "include/person.h"

struct TestFixture
{
    Vending_machine m;

    TestFixture()
        : m()
    {}

    ~TestFixture() = default;
};

struct TestFixture1
{
    std::vector<Person> p;

    TestFixture1()
        : p()
    {}

    ~TestFixture1() = default;
};

BOOST_FIXTURE_TEST_SUITE(Machine_Test, TestFixture)

BOOST_AUTO_TEST_CASE(machine_name)
{
    m.setName("Distributor");
    BOOST_CHECK_EQUAL("Distributor", m.getName());
}

BOOST_AUTO_TEST_CASE(machine_Item_Sold)
{
    m.addItemSold(4);
    BOOST_CHECK_EQUAL(4, m.getQuantitySold());
}

BOOST_AUTO_TEST_CASE(machine_money_in)
{
    m.initMoney(2);
    m.setMoneyIn(6.55,0);
    m.setMoneyIn(1209.20, 1);
    BOOST_CHECK_EQUAL(6.55, m.getMoneyIn(0));
    BOOST_CHECK_EQUAL(1209.20, m.getMoneyIn(1));
}

BOOST_AUTO_TEST_CASE(machine_money_out)
{
    m.initMoney(2);
    m.setMoneyOut(645.515, 0);
    m.setMoneyOut(139.320, 1);
    BOOST_CHECK_EQUAL(645.515, m.getMoneyOut(0));
    BOOST_CHECK_EQUAL(139.320, m.getMoneyOut(1));
}

BOOST_AUTO_TEST_CASE(machine_distributor_not_active)
{
    m.deactivateDistributor();
    BOOST_CHECK_EQUAL(false, m.distributorStatus());
}

BOOST_AUTO_TEST_CASE(machine_distributor_active)
{
    m.activateDistributor();
    BOOST_CHECK_EQUAL(true, m.distributorStatus());
}

BOOST_AUTO_TEST_CASE(machine_reset)
{
    m.initMoney(2);
    m.setMoneyOut(645.515, 0);
    m.setMoneyOut(139.320, 1);
    m.deactivateDistributor();

    m.resetMachine();

    BOOST_CHECK_EQUAL(true, m.distributorStatus());
    BOOST_CHECK_EQUAL(0, m.getQuantitySold());
    for (int i = 0; i < 2; ++i) {
        BOOST_CHECK_EQUAL(0, m.getMoneyIn(i));
        BOOST_CHECK_EQUAL(0, m.getMoneyOut(i));
    }
}

BOOST_AUTO_TEST_CASE(machine_currency)
{
    std::string currency;
    currency = "CAD";
    m.setAcceptedCurrency(currency);
    BOOST_CHECK_EQUAL("CAD", m.getCurrentCurrency(0));
    currency = "USD";
    m.setAcceptedCurrency(currency);
    BOOST_CHECK_EQUAL("USD", m.getCurrentCurrency(1));
    BOOST_CHECK_EQUAL(2, m.getNbCurrency());
}

BOOST_AUTO_TEST_CASE(machine_inventory)
{
    std::string itemId;
    std::string description;
    double price;

    itemId = "P10";
    description = "Juice";
    price = 1.50;

    m.Items.resize(1);
    m.Items[0].push_back(Inventory(itemId, description, price));
    BOOST_CHECK_EQUAL(itemId, m.Items[0][0].getItemId());
    BOOST_CHECK_EQUAL(description, m.Items[0][0].getDescription());
    BOOST_CHECK_EQUAL(price, m.Items[0][0].getPrice());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(Person_Test, TestFixture1)

BOOST_AUTO_TEST_CASE(person)
{
    std::string NFC = "7SJNI3KLA8";
    p.push_back(Person(NFC, false));

    BOOST_CHECK_EQUAL(true, p[0].isAuth(NFC));
    
    BOOST_CHECK_EQUAL(true, p[0].getAuth());
}

BOOST_AUTO_TEST_SUITE_END()