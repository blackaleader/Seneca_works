#include "Billable.h"
#include "Utils.h"
#include <cstring>
#include <iomanip>

namespace seneca {

    void Billable::pr(double v) {
        p_v = v;
    }

    void Billable::nm(const char* c) {
        delete[] n_i;
        n_i = seneca::strCpyAndAloc(c);
    }

    Billable::Billable() {
        n_i = nullptr;
        p_v = 0.0;
    }

    Billable::Billable(const Billable& o) {
        n_i = nullptr;
        p_v = 0.0;
        *this = o;
    }

    Billable& Billable::operator=(const Billable& o) {
        if (this != &o) {
            delete[] n_i;
            n_i = seneca::strCpyAndAloc(o.n_i);
            p_v = o.p_v;
        }
        return *this;
    }

    Billable::~Billable() {
        delete[] n_i;
    }

    double Billable::price() const {
        return p_v;
    }

    Billable::operator const char*() const {
        return n_i;
    }

    double operator+(double m, const Billable& B) {
        return m + B.price();
    }

    double& operator+=(double& m, const Billable& B) {
        m += B.price();
        return m;
    }

}