#include <utility>

//
// Created by korna on 04.05.2021.
//

#ifndef LABA3_PERSON_H
#define LABA3_PERSON_H
struct PersonID { //0982 123243
    const unsigned short series;
    const unsigned int number;
};

class Person {
public:
    const PersonID id;
    const string firstName;
    const string middleName;
    const string lastName;
    const time_t birthDate;
    const bool isTeacher;

    Person(const PersonID &id, string firstName, string middleName, string lastName,
           const time_t &birthDate, const bool &isTeacher) :
            id(id),
            firstName(std::move(firstName)),
            middleName(std::move(middleName)),
            lastName(std::move(lastName)),
            birthDate(birthDate),
            isTeacher(isTeacher) {}

    string GetFullName() { return firstName + " " + middleName + " " + lastName; }
};

#endif //LABA3_PERSON_H
