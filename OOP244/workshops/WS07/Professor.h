#ifndef SENECA_PROFESSOR_H
#define SENECA_PROFESSOR_H
#include "Employee.h"

namespace seneca {
   class Professor : public Employee {
      char* m_subjectName{};
      int m_numSections{};

      double devPay() const;

   public:
      Professor();
      Professor(const char* name, const char* subjectName, int numSections, size_t empNo, double salary);
      ~Professor();

      Professor(const Professor&) = delete;
      Professor& operator=(const Professor&) = delete;

      std::istream& read(std::istream& istr = std::cin);
      std::ostream& write(std::ostream& ostr = std::cout) const;
      std::ostream& title(std::ostream& ostr = std::cout) const;
   };

   std::ostream& operator<<(std::ostream& ostr, const Professor& P);
   std::istream& operator>>(std::istream& istr, Professor& P);
}
#endif // SENECA_PROFESSOR_H