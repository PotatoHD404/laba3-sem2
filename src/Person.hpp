#include <utility>

//
// Created by korna on 04.05.2021.
//

#ifndef LABA3_PERSON_H
#define LABA3_PERSON_H

struct PersonID { //0982 123243
    unsigned short series;
    unsigned int number;

    PersonID() : series(), number() {}

    PersonID(unsigned short series, unsigned int number) : series(series), number(number) {}

//    PersonID(const PersonID &x) : series(x.series), number(x.number) {};

//    PersonID &operator=(const PersonID &x) {
//
//    }

    bool operator==(PersonID const &list) const { return series == list.series && number == list.number; };
};

class Person {
public:
    PersonID id;
    string firstName;
    string middleName;
    string lastName;
    string birthDate;
    bool isTeacher;

    Person() : Person(PersonID(), "", "", "", "", false) {}

    Person(const Person &x) : Person(x.id, x.firstName, x.middleName, x.lastName, x.birthDate, x.isTeacher) {}

    Person(const PersonID &id, string firstName, string middleName, string lastName,
           string birthDate, const bool &isTeacher) :
            id(id),
            firstName(std::move(firstName)),
            middleName(std::move(middleName)),
            lastName(std::move(lastName)),
            birthDate(std::move(birthDate)),
            isTeacher(isTeacher) {}

    [[nodiscard]] string GetFullName() const { return firstName + " " + middleName + " " + lastName; }

    friend ostream &operator<<(ostream &out, Person &x) {
        out << x.GetFullName();
        return out;
    }

    friend istream &operator>>(istream &in, Person &x) {
        unsigned short series;
        unsigned int number;
        cout << "Input person like this:\n";
        cout << "series number firstName middleName lastName birthDate isTeacher\n";
        cout << "0982 123243 Алексей Щербаков Владимирович 11.13.20 0\n";
        if (!(in >> series) || !(in >> number) || !(in >> x.firstName) || !(in >> x.middleName) ||
            !(in >> x.lastName) || !(in >> x.birthDate) || !(in >> x.isTeacher))
            throw runtime_error("Wrong input");
        x.id = PersonID(series, number);
        return in;
    }

    bool operator>(Person &list) const {
        return GetFullName() > list.GetFullName();
    }

    bool operator<(Person &list) const {
        return GetFullName() < list.GetFullName();
    }

    bool operator==(Person const &list) const {
        return id == list.id &&
               firstName == list.firstName &&
               middleName == list.middleName &&
               lastName == list.lastName &&
               birthDate == list.birthDate &&
               isTeacher == list.isTeacher;
    }

    bool operator!=(Person const &list) const { return !(*this == list); }

    Person &operator=(const Person &) = default;

    Person &operator=(Person &&) = default;


};

#endif //LABA3_PERSON_H
