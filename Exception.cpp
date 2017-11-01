#include "Exception.h"
#include <stdio.h>
#include <cstdlib>
#include <string.h>

namespace DTLib {

void Exception::Exception::init(const char *message, const char *file, int line)
{
   m_message = message ? strdup(message) : NULL;

   if (NULL != file) {
       char strLine[16] = {0};
       itoa(line, strLine, 10);

       m_location = (char*)malloc(strlen(file) + strlen(strLine) + 2);

       if (m_location != NULL) {
           strcpy(m_location, file);
           strcat(m_location, ":");
           strcat(m_location, strLine);
       }
   }
   else {
       m_location = NULL;
   }
}

Exception::Exception(const char* message) {
    init(message, NULL, NULL);
}

Exception::Exception(const char* file, int line) {
    init(NULL, file, line);
}

Exception::Exception(const char* message, const char* file, int line) {
    init(message, file, line);
}

Exception::Exception(const Exception& e) {
    m_message = strdup(e.message());
    m_location = strdup(e.location());
}

Exception& Exception::operator=(const Exception& e) {
    if (this != &e) {
        free(m_message);
        free(m_location);

        m_message = strdup(e.message());
        m_location = strdup(e.location());
    }
    return *this;
}

const char* Exception::message() const {
    return m_message;
}
const char* Exception::location() const {
    return m_location;
}

Exception::~Exception() {
    free(m_message);
    free(m_location);
}

}



