#include <iostream>
#include <iomanip>
#include "Professor.h"
#include "Utils.h"

namespace seneca {


   Professor::Professor() : m_subjectName(nullptr), m_numSections(0) {}

   Professor::Professor(const char* name, const char* subjectName, int numSections, size_t empNo, double salary)
      : Employee(name, empNo, salary) {
      if (m_subjectName) {
         delete[] m_subjectName;
         m_subjectName = nullptr;
      }
      m_subjectName = ut.alocpy(subjectName);
      m_numSections = numSections;
   }

   Professor::~Professor() {
      delete[] m_subjectName;
      m_subjectName = nullptr;
   }

   double Professor::devPay() const {
      return salary() * 0.01 * m_numSections;
   }

   std::istream& Professor::read(std::istream& istr) {
      Employee::read(istr);

      char buffer[1024];
      istr.ignore(); 
      istr.getline(buffer, 1024, ',');
      
      delete[] m_subjectName;
      m_subjectName = ut.alocpy(buffer);

      istr >> m_numSections;

      return istr;
   }

   std::ostream& Professor::write(std::ostream& ostr) const {
      Employee::write(ostr);

      char subject2print[21]{};
      if (m_subjectName) {
         ut.strcpy(subject2print, m_subjectName, 20);
      }

      ostr << " ";
      ostr.width(20);
      ostr.setf(std::ios::left);
      ostr << subject2print;
      ostr.unsetf(std::ios::left);
      ostr << " | ";

      ostr.width(5);
      ostr.setf(std::ios::right);
      ostr << m_numSections;
      ostr.unsetf(std::ios::right);
      ostr << " | ";

      ostr.width(8);
      ostr.precision(2);
      ostr.setf(std::ios::right | std::ios::fixed);
      ostr << devPay();
      ostr.unsetf(std::ios::right | std::ios::fixed);
      ostr << " |";

      return ostr;
   }

   std::ostream& Professor::title(std::ostream& ostr) const {
      Employee::title(ostr);
      return ostr << " Teaching Subject     | Sec # | $Dev Pay |";
   }

   std::ostream& operator<<(std::ostream& ostr, const Professor& P) {
      return P.write(ostr);
   }

   std::istream& operator>>(std::istream& istr, Professor& P) {
      return P.read(istr);
   }
}