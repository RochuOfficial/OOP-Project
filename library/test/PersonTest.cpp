#include <boost/test/unit_test.hpp>
#include "model/Person.h"
#include "managers/PersonManager.h"
#include "typedefs.h"
#include <memory>
#include "storages/PersonFilesStorage.h"

struct TestSuitePersonFixture {
    std::string firstName = "Jan";
    std::string lastName = "Kowalski";
    int id = 1;
    int lessonId = 1;
};

BOOST_FIXTURE_TEST_SUITE(TestSuitePerson, TestSuitePersonFixture)

BOOST_AUTO_TEST_CASE(PersonConstuctorTest) {
    PersonPtr person;
    person = std::make_shared<Person>(firstName, lastName, id);
    BOOST_TEST(person != nullptr);
    BOOST_TEST(person->getFirstName() == firstName);
    BOOST_TEST(person->getLastName() == lastName);
    BOOST_TEST(person->getId() == id);
    BOOST_TEST(person->isDuringLesson() == false);
    BOOST_TEST(person->getLessonId() == -1);
}

BOOST_AUTO_TEST_CASE(PersonSettersTest) {
    PersonPtr person;
    person = std::make_shared<Person>(firstName, lastName, id);
    person->setLessonId(lessonId);
    person->setDuringLesson(true);
    BOOST_TEST(person->getLessonId() == lessonId);
    BOOST_TEST(person->isDuringLesson() == true);

    person->setLessonId(-2);
    BOOST_TEST(person->getLessonId() == lessonId);
}

BOOST_AUTO_TEST_CASE(PersonRepositoryMethodsTest) {
    PersonRepository personRepository;
    PersonPtr person = std::make_shared<Person>(firstName, lastName, id);
    personRepository.add(person);
    BOOST_TEST(personRepository.size() == 1);

    auto found = personRepository.findAll();
    BOOST_TEST(found.size() == 1);

    personRepository.remove(person);
    BOOST_TEST(personRepository.size() == 0);
}

BOOST_AUTO_TEST_CASE(PersonManagerMethodsTest) {
    PersonRepositoryPtr personRepository = std::make_shared<PersonRepository>();
    PersonFilesStoragePtr personFilesStorage = std::make_shared<PersonFilesStorage>();
    PersonManagerPtr personManager = std::make_shared<PersonManager>(personRepository, personFilesStorage);
    PersonPtr person = personManager->addPerson(firstName, lastName, id);
    BOOST_TEST(person != nullptr);
    BOOST_TEST(person->getFirstName() == firstName);
    auto all = personManager->findAllPersons();
    BOOST_TEST(all.size() == 1);

    PersonPtr person2 = personManager->addPerson(firstName, lastName, id);
    BOOST_TEST(person2 == person);

    PersonPtr found = personManager->getPerson(id);
    BOOST_TEST(found == person);
    BOOST_TEST(personManager->getPerson(0) == nullptr);

    auto found1 = personManager->findPersons([](const PersonPtr& p) {
        return p->getFirstName() == "Jan";
    });
    BOOST_TEST(found1.size() == 1);
    BOOST_TEST(found1.front()->getLastName() == "Kowalski");
}

BOOST_AUTO_TEST_SUITE_END()