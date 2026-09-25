#ifndef  CONTAINER_EXCEPTION_HPP
# define CONTAINER_EXCEPTION_HPP

# include <exception>

namespace Container
{
namespace Exception
{
class InvalidIndex : public std::exception { const char * what() const noexcept { return "Index invalid."; } };
};
};

#endif