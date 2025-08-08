#ifndef SENECA_BILLABLE_H
#define SENECA_BILLABLE_H

#include <iostream>
#include <fstream>

namespace seneca {

    class Billable {
        char* n_i;
        double p_v;

    protected:
        void pr(double v);
        void nm(const char* c);

    public:
        Billable();
        Billable(const Billable& o);
        Billable& operator=(const Billable& o);
        virtual ~Billable();

        virtual double price() const;
        virtual std::ostream& print(std::ostream& os = std::cout) const = 0;
        virtual bool order() = 0;
        virtual bool ordered() const = 0;
        virtual std::ifstream& read(std::ifstream& f) = 0;

        operator const char*() const;
    };

    double operator+(double m, const Billable& B);
    double& operator+=(double& m, const Billable& B);

}

#endif // SENECA_BILLABLE_H