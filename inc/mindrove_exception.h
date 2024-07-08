#ifndef MINDROVE_EXCEPTION
#define MINDROVE_EXCEPTION

#include <exception>
#include <string>

/// MindRoveException class to notify about errors
class MindRoveException : public std::exception
{

public:
    /// exit code returned from low level API
    int exit_code;

    explicit MindRoveException (const char *msg, int exit_code) : std::exception ()
    {
        msg_ = std::string (msg) + std::to_string (exit_code);
        this->exit_code = exit_code;
    }

    virtual ~MindRoveException () throw ()
    {
    }

    virtual const char *what () const throw ()
    {
        return msg_.c_str ();
    }

protected:
    std::string msg_;
};

#endif
