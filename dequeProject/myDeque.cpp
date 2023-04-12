#include <iostream>
#include <vector>
#include <string>
#include "myDeque.hpp"
template <typename T>
MyDeque<T>::MyDeque() {}

template <typename T>
MyDeque<T>::MyDeque(int n) : frontVector(n / 2, T{}), backVector(n - n / 2, T{}) {}

template <typename T>
MyDeque<T>::MyDeque(std::initializer_list<T> vals) {
    int valsSize = vals.size();
    frontVector = std::vector<T>(valsSize / 2, T{});
    backVector = std::vector<T>(valsSize - valsSize / 2, T{});
    int i = 0;
    for (auto val : vals) {
        if (i < valsSize / 2) {
            frontVector[i++] = val;
        }
        else {
            backVector[i++ - valsSize / 2] = val;
        }
    }
}

template <typename T>
T& MyDeque<T>::back() {
    if (backVector.empty()) {
        return frontVector.back();
    }
    return backVector.back();
}

template <typename T>
const T& MyDeque<T>::back() const {
    if (backVector.empty()) {
        return frontVector.back();
    }
    return backVector.back();
}

template <typename T>
T& MyDeque<T>::front() {
    if (frontVector.empty()) {
        return backVector.front();
    }
    return frontVector.front();
}

template <typename T>
const T& MyDeque<T>::front() const {
    if (frontVector.empty()) {
        return backVector.front();
    }
    return frontVector.front();
}

template <typename T>
void MyDeque<T>::push_back(T value) {
    backVector.push_back(value);
    if (backVector.size() > frontVector.size() + 1) {
        frontVector.push_back(backVector.front());
        backVector.erase(backVector.begin());
    }
}

template <typename T>
void MyDeque<T>::pop_back() {
    if (backVector.empty()) {
        backVector.insert(backVector.begin(), frontVector.rbegin() + 1, frontVector.rend());
        frontVector.erase(frontVector.begin() + frontVector.size() / 2, frontVector.end());
    }
    backVector.pop_back();
}

template <typename T>
void MyDeque<T>::push_front(T value) {
    frontVector.push_back(value);
    if (frontVector.size() > backVector.size() + 1) {
        backVector.insert(backVector.begin(), frontVector.back());
        frontVector.pop_back();
    }
}

template <typename T>
void MyDeque<T>::pop_front() {
    if (frontVector.empty()) {
        frontVector.insert(frontVector.begin(), backVector.rbegin() + 1, backVector.rend());
        backVector.erase(backVector.begin() + backVector.size() / 2, backVector.end());
    }
    frontVector.pop_back();
}

template <typename T>
bool MyDeque<T>::empty() const {
    return frontVector.empty() && backVector.empty();
}

template <typename T>
int MyDeque<T>::size() const {
    return frontVector.size() + backVector.size();
}

template <typename T>
void MyDeque<T>::rebalance(bool frontEmpty) {
    if (frontEmpty) {
        // Move elements from back vector to front vector
        int mid = (backVector.size() + 1) / 2;
        std::move(backVector.begin(), backVector.begin() + mid,
            std::back_inserter(frontVector));
        backVector.erase(backVector.begin(), backVector.begin() + mid);
    }
    else {
        // Move elements from front vector to back vector
        int mid = (frontVector.size() + 1) / 2;
        std::move(frontVector.rbegin(), frontVector.rbegin() + mid,
            std::back_inserter(backVector));
        frontVector.erase(frontVector.end() - mid, frontVector.end());
    }
}

template <typename T>
T& MyDeque<T>::operator[](int i) {
    if (i < frontVector.size()) {
        return frontVector[i];
    }
    else {
        return backVector[i - frontVector.size()];
    }
}


template <typename T>
const T& MyDeque<T>::operator[](int i) const {
    if (i < frontVector.size()) {
        return frontVector[i];
    }
    else {
        return backVector[i - frontVector.size()];
    }
}

template <typename T>
bool MyDeque<T>::operator==(const MyDeque<T>& other) const {
    if (size() != other.size()) {
        return false;
    }
    for (int i = 0; i < size(); i++) {
        if ((*this)[i] != other[i]) {
            return false;
        }
    }
    return true;
}


// Do not modify these lines.
// They are needed for the marker.
template class MyDeque<int>;
template class MyDeque<double>;
template class MyDeque<char>;
template class MyDeque<std::string>;

