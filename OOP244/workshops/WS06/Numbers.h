// Numbers.h
#ifndef SENECA_NUMBERS_H_
#define SENECA_NUMBERS_H_
#include <iostream>

namespace seneca {

    class Numbers {
        double* m_numbers;
        char*   m_filename;
        bool    m_isOriginal;
        int     m_numCount;

        bool    isEmpty()    const;
        void    setEmpty();
        void    setFilename(const char* filename);
        int     numberCount()const;
        bool    load();
        bool    save()       const;
        void    sort();

    public:
        Numbers();                         
        Numbers(const char* filename);     
        ~Numbers();                        

        Numbers(const Numbers&);          
        Numbers& operator=(const Numbers&);

        double  average() const;
        double  max()     const;
        double  min()     const;

        Numbers& operator+=(double value);
        std::ostream& display(std::ostream& ostr) const;

        friend std::ostream& operator<<(std::ostream& os, const Numbers& N);
        friend std::istream& operator>>(std::istream& is, Numbers& N);
    };

}

#endif // SENECA_NUMBERS_H_
